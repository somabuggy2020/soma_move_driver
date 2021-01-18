#ifndef HARDWAREMANUALCONTROLPANEL_H
#define HARDWAREMANUALCONTROLPANEL_H

#include <QWidget>
#include <QString>
#include <QDebug>

#include "Motor/motorinfo.h"

struct ControlValue_t{
	double steer_pos;
	double rearBrake_pos;
	double frontBrake_pos;
	double accel_pos;

	ControlValue_t():
		steer_pos(0.0),
		rearBrake_pos(0.0),
		frontBrake_pos(0.0),
		accel_pos(0.0) {}
};

namespace Ui {
	class HardwareManualControlPanel;
}

class HardwareManualControlPanel : public QWidget
{
	Q_OBJECT

public:
	explicit HardwareManualControlPanel(QWidget *parent = 0);
	~HardwareManualControlPanel();

private slots:
	void on_spnValue_valueChanged(double arg1);

signals:
	void On_actuator_controled(ControlValue_t values);

private:
	Ui::HardwareManualControlPanel *ui;
	double value;
	ControlValue_t values;
};

#endif // HARDWAREMANUALCONTROLPANEL_H
