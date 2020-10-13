#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
#include <QString>
#include <QDebug>

class Hardware : public QObject
{
	Q_OBJECT
public:
	explicit Hardware(QObject *parent = nullptr);

signals:

public slots:
};

#endif // HARDWARE_H
