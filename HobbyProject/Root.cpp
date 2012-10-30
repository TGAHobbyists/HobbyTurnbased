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
StateController* Root::GetStateController()
{
	return myStateController;
}

