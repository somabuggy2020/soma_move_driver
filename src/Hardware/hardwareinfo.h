#ifndef HARDWAREINFO_H
#define HARDWAREINFO_H

#include "Motor/motorinfo.h"

namespace HardwareInfo {
	struct Data_t{
		MotorInfo::Data_t steering;
		MotorInfo::Data_t rearBrake;
		MotorInfo::Data_t frontBrake;
		MotorInfo::Data_t accel;
	};
}

#endif // HARDWAREINFO_H
