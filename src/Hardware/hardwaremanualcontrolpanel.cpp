#include "hardwaremanualcontrolpanel.h"
#include "ui_hardwaremanualcontrolpanel.h"

HardwareManualControlPanel::HardwareManualControlPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::HardwareManualControlPanel)
{
	ui->setupUi(this);
	value = ui->spnValue->value();
}

HardwareManualControlPanel::~HardwareManualControlPanel()
{
	delete ui;
}

void HardwareManualControlPanel::on_spnValue_valueChanged(double arg1)
{
	value = arg1;
}
