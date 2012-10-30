#ifndef _NO_ARGUMENT_COMMAND_H_
#define _NO_ARGUMENT_COMMAND_H_


template <class Type>
class NoArgumentCommand
{
public:
	typedef void (Type::* Action)();
	inline NoArgumentCommand(Type* anObject, Action anAction);
	inline ~NoArgumentCommand(void);


	inline void Execute();
	
private:
	Action myAction;
	Type* myReciever;
};

template <class Type>
NoArgumentCommand<Type>::NoArgumentCommand( Type* anObject, Action anAction )
:myReciever(anObject)
,myAction(anAction)
{

}

template <class Type>
NoArgumentCommand<Type>::~NoArgumentCommand( void )
{
	
}

template <class Type>
void NoArgumentCommand<Type>::Execute()
{
	(myReciever->*myAction)();
}


#endif//_NO_ARGUMENT_COMMAND_H_
