#pragma once

#include <QDebug>
#include <QString>
#include <QFile>
#include <QMap>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtMath>
#include <QRectF>
#include <QSettings>

#include "../Common/configfilepath.h"
//#include "../Common/statevector.h"
#include "../Common/definitions.h"
#include "../Hardware/hardwareinfo.h"

namespace VeloControlMode
{
	const int FIX = 0;
	const int PID = 1;
	const int RL = 2;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
struct Command_t
{
	int mode;       //namespace Mode variable
	double steer;   //steering angle[deg]
	double v;       //velocity[m/s]

	Command_t(): mode(Mode::Stop), steer(0.0), v(0.0) {}
};


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
class Data : public QObject
{
	Q_OBJECT
public:
	explicit Data(QObject *parent = nullptr);
	~Data();

	//State Vector update
	//	void updateState();

	//Config managment
	void restoreConfig();

public:
	QDateTime st, ct; //start timestamp, current timestamp
	double T;   //[sec]
	double dt;  //[sec]

	int state, last_state;	//State namespace value
	int mode;               //Mode namespace value
	Command_t cmd;          //Command structure
	HardwareInfo::Data_t hardware;	//Hardware Data

	//    StateVector X_t;	//State vector {x, y, theta}
	double v[3];			//Velocity [m/s]
	double ev[3];			//Error of velocity t and t-1 and t-2

	bool isRemote;							//Remote false:Off, true:On
	bool isCommClient;					//Command client false:logout, true:exists

	int VeloController;	//0:constant, 1:PID, 2:RL

	double V_ref, P, D, V_err;
	double Pout, Dout;

	//	bool isLog;
	//	QFile *log;
	//	QTextStream *out;
};


