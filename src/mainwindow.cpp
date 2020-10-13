#include "mainwindow.h"
#include "ui_mainwindow.h"

#define TIMER_T 33

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	qInfo() << "GUI thread:" << QThread::currentThreadId();
	ui->setupUi(this);

	hardwareInfoVwr = new HardwareInfoViewer(this);
	ui->dwHardwareInfoViewer->setWidget(hardwareInfoVwr);

	qRegisterMetaType<Data*>("Data");
	qRegisterMetaType<HardwareInfo::Data_t>("HardwareData");

	xbox = new Xbox();
	data = new Data();
	hardware = new Hardware();

	if(hardware->init() == -1) exit(1);

	connect(this, &MainWindow::updateTimestamp, this,
					[=](QDateTime timestamp, double T, double dt){
		QString str;
		str += timestamp.toString("hh:mm:ss");
		str += QString(" [T=%1 / dt=%2]").arg(QS_NUM2(T)).arg(dt);
		ui->statusBar->showMessage(str);
	});

	connect(this, &MainWindow::update, this,
					[=](Data *data){
		ui->lblState->setText(State::str[data->state]);
		ui->lblMode->setText(State::str[data->mode]);
		hardwareInfoVwr->set(data->hardware);
	});

	start();
}

MainWindow::~MainWindow()
{
	delete ui;
	qInfo() << "Finished";
}

void MainWindow::main()
{
	QMetaObject::invokeMethod(timer, "stop");

	//update timestamp
	QDateTime tmp = QDateTime::currentDateTime();
	data->T = (double)data->st.msecsTo(tmp)/1000.0;
	data->dt = (double)data->ct.msecsTo(tmp)/1000.0;
	data->ct = tmp;
	emit updateTimestamp(data->ct, data->T, data->dt);


	//main process
	xbox->recv(data);
	hardware->recv(data);
	// end



	if(!isThread){
		hardware->finalize();
		thread->deleteLater();
		return;
	}

	emit update(data);
	QMetaObject::invokeMethod(timer, "start");
	return;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	isThread = false;
}

void MainWindow::start()
{
	isThread = true;
	thread = new QThread();
	timer = new QTimer();
	timer->setInterval((int)TIMER_T);

	connect(timer, SIGNAL(timeout()), this,
					SLOT(main()), Qt::DirectConnection);

	timer->moveToThread(thread);
	thread->start();
	QMetaObject::invokeMethod(timer, "start");
	return;
}
