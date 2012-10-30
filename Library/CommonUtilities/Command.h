#ifndef _COMMAND_H_
#define _COMMAND_H_


class Command
{
public:
	Command(void);
	virtual ~Command(void);

	virtual void Execute() = 0;
};

#endif//_COMMAND_H_

