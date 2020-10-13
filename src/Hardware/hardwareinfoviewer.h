#ifndef HARDWAREINFOVIEWER_H
#define HARDWAREINFOVIEWER_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QTreeWidget>

#include "../Common/definitions.h"
#include "hardwareinfo.h"

class twiMotor;

namespace Ui {
	class HardwareInfoViewer;
}

class HardwareInfoViewer : public QWidget
{
	Q_OBJECT

public:
	explicit HardwareInfoViewer(QWidget *parent = 0);
	~HardwareInfoViewer();

public slots:
	void set(HardwareInfo::Data_t d);

private:
	Ui::HardwareInfoViewer *ui;
	twiMotor *twiSteering;
	twiMotor *twiRearBrake;
	twiMotor *twiFrontBrake;
	twiMotor *twiAccel;
};

class twiMotor
{
public:
	twiMotor(QTreeWidget *parent, QString name);
	void set(MotorInfo::Data_t data);

private:
	QTreeWidget *parent;
	QTreeWidgetItem *label;
	QTreeWidgetItem *pos, *trgt_pos;
	QTreeWidgetItem *rpm;
};

#endif // HARDWAREINFOVIEWER_H
