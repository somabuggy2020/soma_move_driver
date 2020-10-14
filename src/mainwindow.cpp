#include "mainwindow.h"
#include "ui_mainwindow.h"

#define TIMER_T 1

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
	behavior = new Behavior();

	if(hardware->init() == -1) exit(1);
	if(behavior->init() == -1) exit(1);

	udp2NUC1.IP = "192.168.1.11";
	udp2NUC1.port = 7002;
	udp2NUC1.socket = new QUdpSocket();

	connect(this, &MainWindow::updateTimestamp, this,
					[=](QDateTime timestamp, double T, double dt){
		QString str;
		str += timestamp.toString("hh:mm:ss");
		str += QString(" [T=%1 / dt=%2]").arg(QS_NUM2(T)).arg(dt);
		ui->statusBar->showMessage(str);
	});

	connect(this, &MainWindow::update, this,
					[=](Data *data){
		ui->lblCmd->setText(QString(":>%1 : %2 [deg] : %3 [m/s]").arg(Mode::str[data->cmd.mode]).arg(data->cmd.steer).arg(data->cmd.v));
		ui->lblState->setText(State::str[data->state]);
		ui->lblMode->setText(Mode::str[data->mode]);
		hardwareInfoVwr->set(data->hardware);
	}, Qt::QueuedConnection);

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
	behavior->main(data);
	hardware->send(data);
	// end main process


	struct Send_t
	{
		int state;
		double steer;
	} send;
	send.state = data->state;
	send.steer = data->hardware.steering.Out.pos;

	udp2NUC1.socket->writeDatagram(
				(char*)&send,
				sizeof(Send_t),
				QHostAddress(udp2NUC1.IP),
				udp2NUC1.port);


	if(!isThread){
		hardware->finalize();
		return;
	}

	emit update(data);
	QMetaObject::invokeMethod(timer, "start");
	return;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	isThread = false;
	QThread::sleep(1);
	thread->quit();
	thread->wait();
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
	hardware->setThread(thread);
	udp2NUC1.socket->moveToThread(thread);

	thread->start();
	QMetaObject::invokeMethod(timer, "start");
	return;
}
