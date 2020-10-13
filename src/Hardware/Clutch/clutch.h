#ifndef CLUTCH_H
#define CLUTCH_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QSettings>
#include <QUdpSocket>

#include "../../Common/configfilepath.h"
#include "../../Common/definitions.h"
#include "clutchinfo.h"

class Clutch : public QObject
{
	Q_OBJECT
public:
	explicit Clutch(QObject *parent = nullptr);

	int init();
	void setThread(QThread *th);
	void finalize();

	int open();

	int set(ClutchInfo::Data_t &data);
	int recv(ClutchInfo::Data_t &data);

private:
	int Forward();
	int Backward();
	int Free();

private:
	bool isUse;
	UDPInfo_t udp_recv;
	UDPInfo_t udp_send;

//	QString IP;
//	int port;
//	int udp_recv_port, udp_send_port;
//	QUdpSocket *sock_recv, *sock_send;

};

#endif // CLUTCH_H
