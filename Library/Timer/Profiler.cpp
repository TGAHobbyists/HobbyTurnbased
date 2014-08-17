#include "profiler.h"
#include "stringtoint.h"

Profiler* Profiler::ourInstance = NULL;

Profiler::Profiler()
{
	myStartTime = 0;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&myStartTime));

	myFrequency = 0;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&myFrequency));
	

	m_pTimerStack.Init(32, 16);

	m_pTimerNames.Init(32,16);
	myCurrentFrame = 0;
}
Profiler::~Profiler()
{}
void Profiler::Create()
{
	ourInstance = new Profiler();
}
void Profiler::Destroy()
{

}
Profiler* Profiler::GetInstance()
{
	return ourInstance;
}

__int64 Profiler::GetFrequency() const
{
	return myFrequency;
}
void Profiler::AddData( std::string aDataName, float aSelfTime, std::string aParentTimer )
{
	bool addname = true;
	for(int index = 0; index < 3; ++index)
	{
		if( myData[index].Get( S2I( aDataName.c_str() ) ).myTimesCalled > 0 )
		{
			addname = false;
		}
	}
	if(addname == true)
	{
		m_pTimerNames.Add( aDataName );
	}

	ProfilingData temp = myData[myCurrentFrame].Get( S2I( aDataName.c_str() ) );
	if( temp.myTimesCalled == -1 )
	{
		temp.mySelfTime = aSelfTime;
		temp.myTotalTime = aSelfTime;
		temp.myTimesCalled = 1;
		temp.parentNode = aParentTimer;
		myData[myCurrentFrame].Add( aDataName, temp );
	}
	else
	{
		myData[myCurrentFrame].Remove( S2I( aDataName.c_str() ) );
		if( aParentTimer != aDataName )
		{
			temp.mySelfTime += aSelfTime;
			temp.myTotalTime += aSelfTime;
		}
		else
		{
			temp.mySelfTime = aSelfTime;
			temp.myTotalTime = aSelfTime;
		}
		temp.myTimesCalled++;
		temp.parentNode = aParentTimer;
		myData[myCurrentFrame].Add( aDataName, temp);
	}

	if( aParentTimer.length() > 0 && aParentTimer != aDataName)
	{
		ProfilingData parent = myData[myCurrentFrame].Get( S2I( aParentTimer.c_str() ) );
		parent.mySelfTime -= aSelfTime;
		parent.myTimesCalled = 0;
		myData[myCurrentFrame].Remove( S2I( aParentTimer.c_str() ) );
		myData[myCurrentFrame].Add( aParentTimer, parent);
	}

}

void Profiler::AddTimer( ProfilingTimer* aTimer )
{
	if( m_pTimerStack.Top() != NULL )
	{
		aTimer->SetParentTimer( m_pTimerStack.Top()->GetName() );
	}
	m_pTimerStack.Push(aTimer);
}
void Profiler::RemoveTimer()
{
	m_pTimerStack.Pop();
}

//void Profiler::TemporaryDraw(hgeFont* aFont)
//{
	//for(int index = 0; index < m_pTimerNames.Count(); index++)
	//{
	//	float totalTime = 0;
	//	float selfTime = 0;
	//	int calls = 0;
	//	std::string parent = myData[myCurrentFrame].Get( S2I(m_pTimerNames[index].c_str()) ).parentNode;
	//	for( int frameIndex = 0; frameIndex < 3; ++frameIndex)
	//	{
	//		totalTime += myData[myCurrentFrame].Get( S2I(m_pTimerNames[index].c_str()) ).myTotalTime;
	//		calls += myData[myCurrentFrame].Get( S2I(m_pTimerNames[index].c_str()) ).myTimesCalled;
	//		selfTime += myData[myCurrentFrame].Get( S2I(m_pTimerNames[index].c_str()) ).mySelfTime;
	//	}
	//	totalTime /= 3;
	//	calls /= 3;
	//	selfTime /= 3;

	//	if( parent.length() > 0)
	//	{
	//		aFont->printf(100, 840 + static_cast<float>(index) * 40.f, HGETEXT_LEFT, "Name: %s TotalTime: %f SelfTime: %f TimesCalled: %i Parent: %s",m_pTimerNames[index].c_str(), totalTime,selfTime , calls, parent.c_str() );
	//	}
	//	else
	//	{
	//		aFont->printf(100, 840 + static_cast<float>(index) * 40.f, HGETEXT_LEFT, "Name: %s TotalTime: %f SelfTime: %f TimesCalled: %i ",m_pTimerNames[index].c_str(), totalTime,selfTime , calls  );
	//	}
	//}
//}

void Profiler::NewFrame()
{
	myCurrentFrame++;
	if( myCurrentFrame > 2 )
	{
		myCurrentFrame = 0;
	}
	myData[myCurrentFrame].RemoveAll();
}

