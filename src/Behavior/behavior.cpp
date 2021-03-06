#include "behavior.h"

Behavior::Behavior()
{
}

int Behavior::init()
{
  qInfo() << "Init. Behavior";

  stop = new Stop();
  starting = new Starting();
  traveling = new Traveling();
  stopping = new Stopping();
  //	stacking = new Stacking();

	manualControl = new ManualControl();

	stop->init();
	starting->init();
	traveling->init();
	stopping->init();
  //	stacking->initialize();

	manualControl->init();

  state[State::Stop] = stop;
  state[State::Starting] = starting;
  state[State::Traveling] = traveling;
  state[State::Stopping] = stopping;
  //	state[State::Stacking] = stacking;

	state[State::ManualControl] = manualControl;
  return 0;
}

int Behavior::setThread(QThread *th)
{
  traveling->setThread(th);
  return 0;
}

void Behavior::main(Data *data)
{
  if(data->state == State::Init){
    //		data->hardware.clutch.In = ClutchInfo::Free;
    data->cmd.mode = Mode::Stop;
    data->cmd.steer = 0.0;
    data->cmd.v = 0.0;
    //		data->cmd.isRotReset = true;
    //		data->cmd.isWeeding = false;

    data->hardware.steering.In.pos		= MotorPos::Home;
    data->hardware.rearBrake.In.pos		= MotorPos::Max;
    data->hardware.frontBrake.In.pos	= MotorPos::Max;
    data->hardware.accel.In.pos				= MotorPos::Min;

    data->state = State::Stop;
    return;
  }

  if(!state.contains(data->state)){
    qCritical() << "Not Contain State" << data->state;
    exit(1);
  }

  int new_state = state[data->state]->isTransition(data);

  if(new_state != data->state){
    state[data->state]->Exit(data);
    data->state = new_state;
    state[data->state]->Enter(data);
    return;
  }

  state[data->state]->Process(data);
  return;
}

