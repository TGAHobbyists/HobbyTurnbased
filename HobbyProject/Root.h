#ifndef _ROOT_SINGLETON_H_
#define _ROOT_SINGLETON_H_


class StateController;
namespace Input
{
	class InputWrapper;
};

class Root
{
public:
	~Root();
	static void Create();
	static void Destroy();
	static Root* GetInstance();

	void AttachStateController( StateController* aStateController );
	StateController* GetStateController() const;

	void AttachInputWrapper( Input::InputWrapper* anInputWrapper );
	Input::InputWrapper* GetInputWrapper() const;

	float myResolutionWidth;
	float myResolutionHeight;

private:
	Root();
	static Root* ourInstance;



	StateController* myStateController;
	Input::InputWrapper* myInputWrapper;
};

#endif//_ROOT_SINGLETON_H_

