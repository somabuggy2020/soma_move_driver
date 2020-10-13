#include "mainwindow.h"
#include "ui_mainwindow.h"

#define TIMER_T 33

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qInfo() << "GUI thread:" << QThread::currentThreadId();
    ui->setupUi(this);

    connect(this, &MainWindow::updateTimestamp, this,
            [=](QDateTime timestamp, double T, double dt){
        QString str;
        str += timestamp.toString("hh:mm:ss");
        str += QString(" [T=%1 / dt=%2]").arg(QS_NUM2(T)).arg(dt);
        ui->statusBar->showMessage(str);
    });


    xbox = new Xbox();
    data = new Data();

    start();
}

MainWindow::~MainWindow()
{
    delete ui;
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

    xbox->recv(data);

    QMetaObject::invokeMethod(timer, "start");
    return;
}

void MainWindow::start()
{
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
