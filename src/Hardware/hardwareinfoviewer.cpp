#include "hardwareinfoviewer.h"
#include "ui_hardwareinfoviewer.h"

HardwareInfoViewer::HardwareInfoViewer(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::HardwareInfoViewer)
{
	ui->setupUi(this);

	ui->tw->setColumnCount(2);
	QStringList headers;
	headers << "key" << "value";
	ui->tw->setHeaderLabels(headers);

	twiSteering = new twiMotor(ui->tw, "Steering");
	twiRearBrake = new twiMotor(ui->tw, "RearBrake");
	twiFrontBrake = new twiMotor(ui->tw, "FrontBrake");
	twiAccel = new twiMotor(ui->tw, "Accel");
}

HardwareInfoViewer::~HardwareInfoViewer()
{
	delete ui;
}

void HardwareInfoViewer::set(HardwareInfo::Data_t d)
{
	twiSteering->set(d.steering);
	twiRearBrake->set(d.rearBrake);
	twiFrontBrake->set(d.frontBrake);
	twiAccel->set(d.accel);
	return;
}

/*!
 * \brief twiMotor::twiMotor
 * \param parent
 * \param name
 */
twiMotor::twiMotor(QTreeWidget *parent, QString name)
{
	this->parent = parent;

	label = new QTreeWidgetItem(parent);
	label->setText(0, name);
	label->setText(1, "0.0/0.0");

	pos = new QTreeWidgetItem(label);
	pos->setText(0, "Pos[deg]");
	pos->setText(1, "0.0");

	trgt_pos = new QTreeWidgetItem(label);
	trgt_pos->setText(0, "Target[deg]");
	trgt_pos->setText(1, "0.0");

	rpm = new QTreeWidgetItem(label);
	rpm->setText(0, "RPM");
	rpm->setText(1, "0.0");
}

void twiMotor::set(MotorInfo::Data_t data)
{
	QString str;
	str += QString("%1").arg(QS_NUM1(data.Out.pos));
	str += QString("/");
	str += QString("%2").arg(QS_NUM1(data.Out.trgPos));
	label->setText(1, str);

	pos->setText(1, QS_NUM1(data.Out.pos));
	trgt_pos->setText(1, QS_NUM1(data.Out.trgPos));
	rpm->setText(1, QS_NUM(data.Out.rpm));
}
