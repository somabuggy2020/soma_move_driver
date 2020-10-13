#include "data.h"

Data::Data(QObject *parent)
	: QObject(parent)
{
	//Timestamp
	st = QDateTime::currentDateTime();
	ct = QDateTime::currentDateTime();

	state = last_state = State::Init;
	mode = Mode::Stop;

	v[0] = v[1] = v[2] = 0.0;
	ev[0] = ev[1] = ev[2] = 0.0;

	isRemote = false;
	isCommClient = false;
//	isLog = false;

	//Hardware profiles
	//	hardware.accelProfs.PosOffset		= 0.0;
	//	hardware.accelProfs.PosRegular	= 6.0;
	//	hardware.accelProfs.PosPush			= 12.0;
	//	hardware.accelProfs.PushTime		= 2.0;

	VeloController = VeloControlMode::FIX;
	//  P = cfg->getDouble("VELOCITY_CONTROL", "P");
	//  D = cfg->getDouble("VELOCITY_CONTROL", "D");

	V_err = 0.0;
	Pout = 0.0;
	Dout = 0.0;
}

Data::~Data()
{
}


void Data::restoreConfig()
{
}

