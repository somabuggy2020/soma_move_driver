#ifndef HARDWAREINFO_H
#define HARDWAREINFO_H

#include "Motor/motorinfo.h"
#include "Clutch/clutchinfo.h"

namespace HardwareInfo {
	struct Data_t{
		MotorInfo::Data_t steering;
		MotorInfo::Data_t rearBrake;
		MotorInfo::Data_t frontBrake;
		MotorInfo::Data_t accel;

		ClutchInfo::Data_t clutch;
	};
}

#endif // HARDWAREINFO_H
