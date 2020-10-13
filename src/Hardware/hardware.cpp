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
}

int Hardware::init()
{
	if(steering->init() == -1) return -1;
	if(rearBrake->init() == -1) return -1;
	if(frontBrake->init() == -1) return -1;
	if(accel->init() == -1) return -1;

	return 0;
}

void Hardware::finalize()
{
	steering->finalize();
	rearBrake->finalize();
	frontBrake->finalize();
	accel->finalize();
}

int Hardware::recv(Data *data)
{
	steering->recv(data->hardware.steering);
	rearBrake->recv(data->hardware.rearBrake);
	frontBrake->recv(data->hardware.frontBrake);
	accel->recv(data->hardware.accel);
}
