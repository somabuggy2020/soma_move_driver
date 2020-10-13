#include "mainwindow.h"
#include "ui_mainwindow.h"

#define TIMER_T 33

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qInfo() << "GUI thread:" << QThread::currentThreadId();
    ui->setupUi(this);


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
    qDebug() << "Main process";
    qDebug() << "Thread ID:" << this->thread->currentThreadId();

    xbox->recv(data);

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
