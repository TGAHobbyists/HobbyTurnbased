#include "stdafx.h"
#include "root.h"

Root* Root::ourInstance = NULL;

Root::Root()
{
	myStateController = NULL;
}
Root::~Root()
{

}
void Root::Create()
{
	if( ourInstance == NULL )
	{
		ourInstance = new Root();
	}
}
void Root::Destroy()
{
	SAFE_DELETE( ourInstance );
}
Root* Root::GetInstance()
{
	return ourInstance;
}

void Root::AttachStateController( StateController* aStateController )
{
	myStateController = aStateController;
}
StateController* Root::GetStateController() const
{
	return myStateController;
}

void Root::AttachInputWrapper( Input::InputWrapper* anInputWrapper )
{
	myInputWrapper = anInputWrapper;
}
Input::InputWrapper* Root::GetInputWrapper() const
{
	return myInputWrapper;
}

void Root::AttachMutexManager( MutexManager* aMutexManager )
{
	myMutexManager = aMutexManager;
}
MutexManager* Root::GetMutexManager() const
{
	return myMutexManager;
}

void Root::setResolution( const float fWidth, const float fHeight )
{
	m_vResolution = Vector2f( fWidth, fHeight );
	m_vHalfRes = m_vResolution * 0.5f;
}
const Vector2f& Root::getResolution()
{
	return m_vResolution;
}
const Vector2f& Root::getHalfRes()
{
	return m_vHalfRes;
}