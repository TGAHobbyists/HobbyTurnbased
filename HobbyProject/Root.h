#ifndef _ROOT_SINGLETON_H_
#define _ROOT_SINGLETON_H_

#include "Vector.h"

class StateController;
namespace Input
{
	class InputWrapper;
};
class MutexManager;

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

	void AttachMutexManager( MutexManager* aMutexManager );
	MutexManager* GetMutexManager() const;


	void setResolution( const float fWidth, const float fHeight );
	const Vector2f& getResolution();
	const Vector2f& getHalfRes();

private:
	Root();
	static Root* ourInstance;

	Vector2f m_vResolution;
	Vector2f m_vHalfRes;

	StateController* myStateController;
	Input::InputWrapper* myInputWrapper;
	MutexManager* myMutexManager;
};

#endif//_ROOT_SINGLETON_H_

