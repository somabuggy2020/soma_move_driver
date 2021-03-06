#pragma once

#include <QUdpSocket>
#include <QtMath>
#include <QString>
#include <QDebug>

#define QS_NUM(v)   QString::number(v)
#define QS_NUM1(v)  QString::number(v, 'f', 1)
#define QS_NUM2(v)  QString::number(v, 'f', 2)
#define QS_GPS(v)   QString::number(v, 'f', 8)
#define QPOW2(v)    qPow(v, 2)

/*!
 * namespace State
 * Definition of state variable
 */
namespace State
{
	const int Init = 0;
	const int Starting = 1;
	const int Traveling = 2;
	const int Stopping = 3;
	const int Stop = 4;
	const int Stacking = 5;

	const int ManualControl = 6;
	const int RotaryReset = 7;

	const QMap<int, QString> str{{Init, "Init"},
															 {Starting, "Starting"},
															 {Traveling, "Traveling"},
															 {Stopping, "Stopping"},
															 {Stop, "Stop"},
															 {Stacking, "Stacking"},
															 {ManualControl, "ManualControl"}};
}

/*!
 * namespace Mode
 * Definition of mode variable
 */
namespace Mode
{
	const int Forward = 1;
	const int Backward = 2;
	const int Stop = 3;

	namespace Remote
	{
		const int Go = 4;		//Remote?O?i??????
		const int Back = 5;	//Remote???i??????
		const int Stop = 6;	//Remote???~??????
	}

	const int ManualControl = 7;

	const QMap<int, QString> str{{Forward, "Forward"},
															 {Backward, "Backward"},
															 {Stop, "Stop"},
															 {Remote::Go, "Remote Go"},
															 {Remote::Back, "Remote Back"},
															 {Remote::Stop, "Remote Stop"},
															 {ManualControl, "ManualControl"}};

}

struct UDPInfo_t
{
	QString IP;
	int port;
	QUdpSocket *socket;
};
