#ifndef MANUALCONTROL_H
#define MANUALCONTROL_H

#include <QString>
#include <QDebug>

#include "../statebase.h"

class ManualControl : public StateBase
{
public:
	ManualControl();

	// StateBase interface
protected:
	int _isTransition(Data *data);
	int _Enter(Data *data);
	int _Process(Data *data);
	void _Exit(Data *data);
};

#endif // MANUALCONTROL_H
