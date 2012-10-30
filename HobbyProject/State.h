#ifndef _STATE_H_
#define _STATE_H_

class State
{
public:
	State()
	{}
	virtual ~State()
	{}

	virtual bool Update() = 0;

	virtual bool Render() = 0;

protected:

};


#endif//_STATE_H_
