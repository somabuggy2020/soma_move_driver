#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QTimer>

#include "Xbox/xbox.h"
#include "Data/data.h"
#include "Hardware/hardware.h"

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

private slots:
    void main();

signals:
		void updateTimestamp(QDateTime timestamp, double T, double dt);
		void update(Data *data);

private:
    Ui::MainWindow *ui;
    QThread *thread;
    QTimer *timer;
		bool isThread;

    Xbox *xbox;
		Data *data;
		Hardware *hardware;

		void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
