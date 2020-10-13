#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
#include <QString>
#include <QDebug>

#include "Motor/motor.h"
#include "../Data/data.h"

class Hardware : public QObject
{
	Q_OBJECT
public:
	explicit Hardware(QObject *parent = nullptr);

	int init();
	void finalize();

	int recv(Data *data);

private:
	Motor *steering;
	Motor *rearBrake;
	Motor *frontBrake;
	Motor *accel;
};

#endif // HARDWARE_H
