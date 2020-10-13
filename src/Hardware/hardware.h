#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
#include <QString>
#include <QDebug>

#include "../Data/data.h"
#include "Motor/motor.h"
#include "Clutch/clutch.h"
#include "Rotary/rotary.h"

class Hardware : public QObject
{
	Q_OBJECT
public:
	explicit Hardware(QObject *parent = nullptr);

	int init();
	void setThread(QThread *th);
	void finalize();

	int recv(Data *data);
	int send(Data *data);

private:
	Motor *steering;
	Motor *rearBrake;
	Motor *frontBrake;
	Motor *accel;
	Clutch *clutch;
	Rotary *rotary;
};

#endif // HARDWARE_H
