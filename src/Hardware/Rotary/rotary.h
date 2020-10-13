#pragma once

#include <QObject>
#include <QString>
#include <QDebug>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QSettings>

#include "../../Common/configfilepath.h"
#include "../../Common/definitions.h"
#include "rotaryinfo.h"

class Rotary : public QObject
{
	Q_OBJECT
public:
	explicit Rotary(QObject *parent = nullptr);

	int init();
	void setThread(QThread *th);
	void finalize();

	int open();
	void close();

	int CountReset();
	int recv(RotaryInfo::Data_t &data);

private:
	bool isUse;
	UDPInfo_t udp_recv;
	UDPInfo_t udp_send;
};
