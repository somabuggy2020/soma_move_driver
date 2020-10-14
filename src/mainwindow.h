#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>

#include "Xbox/xbox.h"
#include "Data/data.h"
#include "Hardware/hardware.h"
#include "Behavior/behavior.h"

#include "Hardware/hardwareinfoviewer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void start();

		void closeEvent(QCloseEvent *event);

private slots:
    void main();

signals:
		void updateTimestamp(QDateTime timestamp, double T, double dt);
		void update(Data *data);

private:
    Ui::MainWindow *ui;
		HardwareInfoViewer *hardwareInfoVwr;
    QThread *thread;
    QTimer *timer;
		bool isThread;

    Xbox *xbox;
		Data *data;
		Hardware *hardware;
		Behavior *behavior;

		UDPInfo_t udp2NUC1;
};

#endif // MAINWINDOW_H
