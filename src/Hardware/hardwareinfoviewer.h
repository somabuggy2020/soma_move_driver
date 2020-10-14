#ifndef HARDWAREINFOVIEWER_H
#define HARDWAREINFOVIEWER_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QTreeWidget>

#include "../Common/definitions.h"
#include "hardwareinfo.h"

class twiMotor;
class twiClutch;
class twiRotary;

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
	twiMotor *steering;
	twiMotor *rearBrake;
	twiMotor *frontBrake;
	twiMotor *accel;
	twiClutch *clutch;
	twiRotary *rotary;
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

class twiClutch
{
public:
	twiClutch(QTreeWidget *parent);
	void set(ClutchInfo::Data_t data);

private:
	QTreeWidget *parent;
	QTreeWidgetItem *label;
};

class twiRotary
{
public:
	twiRotary(QTreeWidget *parent);
	void set(RotaryInfo::Data_t data);

private:
	QTreeWidget *parent;
	QTreeWidgetItem *label;
};

#endif // HARDWAREINFOVIEWER_H
