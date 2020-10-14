#include "stop.h"

Stop::Stop()
{

}

int Stop::_isTransition(Data *data)
{
	switch(data->cmd.mode){
	case Mode::Forward:
	case Mode::Backward:
	case Mode::Remote::Go:
	case Mode::Remote::Back:
		data->mode = data->cmd.mode;
		return State::Starting;	//->Transision to Starting state
	case Mode::ManualControl:
		data->mode = data->cmd.mode;
		return State::ManualControl;
	}

	data->mode = data->cmd.mode;
	return State::Stop;	//->Stay Stop state
}

int Stop::_Enter(Data *data)
{
	data->hardware.steering.In.pos = 0.0;
	data->hardware.rearBrake.In.pos = MotorPos::Max;
	data->hardware.frontBrake.In.pos = MotorPos::Max;
	data->hardware.accel.In.pos = MotorPos::Min;
	return 0;
}

int Stop::_Process(Data *data)
{
	data->hardware.steering.In.pos = 0.0;
	data->hardware.rearBrake.In.pos = MotorPos::Max;
	data->hardware.frontBrake.In.pos = MotorPos::Max;
	data->hardware.accel.In.pos = MotorPos::Min;
	return 0;
}

void Stop::_Exit(Data *data)
{
	return;
}
