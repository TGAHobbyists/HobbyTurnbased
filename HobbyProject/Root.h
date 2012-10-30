#ifndef _ROOT_SINGLETON_H_
#define _ROOT_SINGLETON_H_


class StateController;

class Root
{
public:
	~Root();
	static void Create();
	static void Destroy();
	static Root* GetInstance();

	void AttachStateController( StateController* aStateController );
	StateController* GetStateController();

private:
	Root();
	static Root* ourInstance;

	StateController* myStateController;
};

#endif//_ROOT_SINGLETON_H_

