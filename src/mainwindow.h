#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QTimer>

#include "Xbox/xbox.h"
#include "Data/data.h"

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

private:
    Ui::MainWindow *ui;
    QThread *thread;
    QTimer *timer;

    Xbox *xbox;
    Data *data;
};

#endif // MAINWINDOW_H
