#include "stdafx.h"
#include "statestack.h"

#include "state.h"

StateStack::StateStack()
{

}
StateStack::~StateStack()
{

}

void StateStack::Init()
{
	myStack.Init(5,2);
}
void StateStack::Update( float aDeltaTime )
{
	for( int index = myStack.Count() - 1; index >= 0; --index )
	{
		if( myStack[index]->Update( aDeltaTime ) == false )
		{
			break;
		}
	}
}
void StateStack::Render()
{
	for( int index = myStack.Count() - 1; index >= 0; --index )
	{
		if( myStack[index]->Render() == false )
		{
			break;
		}
	}
}
void StateStack::Push( State* aState )
{
	myStack.Add( aState );
}
