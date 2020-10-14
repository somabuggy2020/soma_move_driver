#ifndef HARDWAREINFO_H
#define HARDWAREINFO_H

#include "Motor/motorinfo.h"
#include "Clutch/clutchinfo.h"
#include "Rotary/rotaryinfo.h"

namespace HardwareInfo {
	struct Data_t{
		MotorInfo::Data_t steering;
		MotorInfo::Data_t rearBrake;
		MotorInfo::Data_t frontBrake;
		MotorInfo::Data_t accel;

		ClutchInfo::Data_t clutch;
		RotaryInfo::Data_t rotary;
	};

	namespace AccelProfile
	{
		const double Regular = 7.5;
		const double Push = 10.0;
		const double PushTime = 1.0; //[sec]
	}
}

#endif // HARDWAREINFO_H
