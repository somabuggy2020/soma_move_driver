#include "manualcontrol.h"

ManualControl::ManualControl()
{

}

int ManualControl::_isTransition(Data *data)
{
	if(data->cmd.mode == Mode::Stop) return State::Stop;
	return State::ManualControl;
}

int ManualControl::_Enter(Data *data)
{
	data->hardware.steering.In.pos = 0.0;
	data->hardware.rearBrake.In.pos = 0.0;
	data->hardware.frontBrake.In.pos = 0.0;
	data->hardware.accel.In.pos = 0.0;

	data->hardware.steering.In.minmax = false;
	data->hardware.rearBrake.In.minmax = false;
	data->hardware.frontBrake.In.minmax = false;
	data->hardware.accel.In.minmax = false;

	return 0;
}

int ManualControl::_Process(Data *data)
{
	return 0;
}

void ManualControl::_Exit(Data *data)
{
	data->hardware.steering.In.minmax = true;
	data->hardware.rearBrake.In.minmax = true;
	data->hardware.frontBrake.In.minmax = true;
	data->hardware.accel.In.minmax = true;
	return;
}
