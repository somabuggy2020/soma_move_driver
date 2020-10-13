#include "clutch.h"

Clutch::Clutch(QObject *parent) : QObject(parent)
{

}

int Clutch::init()
{
	QSettings *cfg = new QSettings(CONFIG_FILE_PATH,
																 QSettings::IniFormat);
	cfg->beginGroup("USE");
	isUse = cfg->value("CLUTCH").toBool();
	cfg->endGroup();

	cfg->beginGroup("CLUTCH");
	udp_recv.IP = cfg->value("IP", "192.168.1.79").toString();
	udp_recv.port = cfg->value("UDP_RECV_PORT", 12345).toInt();
	udp_send.IP = cfg->value("IP", "192.168.1.79").toString();
	udp_send.port = cfg->value("UDP_SEND_PORT", 12346).toInt();
	cfg->endGroup();

	return 0;
}

void Clutch::setThread(QThread *th)
{
	udp_recv.socket->moveToThread(th);
	udp_send.socket->moveToThread(th);
	this->moveToThread(th);
}

void Clutch::finalize()
{

}

int Clutch::open()
{
	udp_recv.socket = new QUdpSocket();
	udp_recv.socket->bind(udp_recv.port);

	udp_send.socket = new QUdpSocket();
	return 0;
}

int Clutch::set(ClutchInfo::Data_t &data)
{
	int ret = -1;

	switch(data.In){
	case ClutchInfo::Forward:
		ret = Forward();
		break;
	case ClutchInfo::Backward:
		ret = Backward();
		break;
	case ClutchInfo::Free:
		ret = Free();
		break;
	default:
		break;
	}

	return ret;
}

int Clutch::recv(ClutchInfo::Data_t &data)
{
	if(!isUse){
		data.Out = data.In;
		return 0;
	}

	if(udp_recv.socket->waitForReadyRead(33)){
		while(udp_recv.socket->bytesAvailable() > 0){

			int recv; //Integer type 4byte date
			udp_recv.socket->readDatagram((char*)&recv, sizeof(int));
			data.Out = recv;
		}
	}
	else{
	}

	return 0;
}

int Clutch::Forward()
{
	int send = ClutchInfo::Forward;
	udp_send.socket->writeDatagram((char*)&send,
																 sizeof(int),
																 QHostAddress(udp_send.IP),
																 udp_send.port);
	return 0;
}

int Clutch::Backward()
{
	int send = ClutchInfo::Backward;
	udp_send.socket->writeDatagram((char*)&send,
																 sizeof(int),
																 QHostAddress(udp_send.IP),
																 udp_send.port);
}

int Clutch::Free()
{
	int send = ClutchInfo::Free;
	udp_send.socket->writeDatagram((char*)&send,
																 sizeof(int),
																 QHostAddress(udp_send.IP),
																 udp_send.port);
}
