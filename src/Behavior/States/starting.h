#ifndef STARTING_H
#define STARTING_H

#include "../statebase.h"

class Starting : public StateBase
{
public:
	Starting();
	virtual ~Starting() {}

	int _isTransition(Data *data);
	int _Enter(Data *data);
	int _Process(Data *data);
	void _Exit(Data *data);

private:
	double T;
};

#endif // STARTING_H
