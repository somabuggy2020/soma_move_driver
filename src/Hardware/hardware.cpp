#include "hardware.h"

Hardware::Hardware(QObject *parent) : QObject(parent)
{
	steering = new Motor(MotorInfo::Names::Steering,
											 MotorInfo::Roles::Drive);
	rearBrake = new Motor(MotorInfo::Names::RearBrake,
												MotorInfo::Roles::Drive);
	frontBrake = new Motor(MotorInfo::Names::FrontBrake,
												 MotorInfo::Roles::Drive);
	accel = new Motor(MotorInfo::Names::Accel,
										MotorInfo::Roles::Drive);
	clutch = new Clutch();
	rotary = new Rotary();
}

int Hardware::init()
{
	if(steering->init() == -1) return -1;
	if(rearBrake->init() == -1) return -1;
	if(frontBrake->init() == -1) return -1;
	if(accel->init() == -1) return -1;
	if(clutch->init() == -1) return -1;
	if(rotary->init() == -1) return -1;

	steering->open();
	rearBrake->open();
	frontBrake->open();
	accel->open();
	clutch->open();
	rotary->open();

	return 0;
}

void Hardware::setThread(QThread *th)
{
	steering->moveToThread(th);
	rearBrake->moveToThread(th);
	frontBrake->moveToThread(th);
	accel->moveToThread(th);
	clutch->setThread(th);
	rotary->setThread(th);
	this->moveToThread(th);
}

void Hardware::finalize()
{
	steering->moveto(0);
	rearBrake->moveto(0);
	frontBrake->moveto(0);
	accel->moveto(0);

	steering->finalize();
	rearBrake->finalize();
	frontBrake->finalize();
	accel->finalize();
	clutch->finalize();
	rotary->finalize();

	return;
}

int Hardware::recv(Data *data)
{
	steering->recv(data->hardware.steering);
	rearBrake->recv(data->hardware.rearBrake);
	frontBrake->recv(data->hardware.frontBrake);
	accel->recv(data->hardware.accel);

	rotary->recv(data->hardware.rotary);


}

int Hardware::send(Data *data)
{
	steering->setMaxRPM(data->hardware.steering.In.rpm);
	rearBrake->setMaxRPM(data->hardware.rearBrake.In.rpm);
	frontBrake->setMaxRPM(data->hardware.frontBrake.In.rpm);
	accel->setMaxRPM(data->hardware.accel.In.rpm);

	steering->moveto(data->hardware.steering.In.pos, data->hardware.steering.In.minmax);
	rearBrake->moveto(data->hardware.rearBrake.In.pos, data->hardware.rearBrake.In.minmax);
	frontBrake->moveto(data->hardware.frontBrake.In.pos, data->hardware.frontBrake.In.minmax);
	accel->moveto(data->hardware.accel.In.pos, data->hardware.accel.In.minmax);

	clutch->set(data->hardware.clutch);
}
