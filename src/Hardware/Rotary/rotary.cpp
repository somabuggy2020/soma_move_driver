#include "rotary.h"

Rotary::Rotary(QObject *parent)
	: QObject(parent)
{
}

/*!
 * \brief Rotary::initialize
 * \return
 */
int Rotary::init()
{
	QSettings *cfg = new QSettings(CONFIG_FILE_PATH,
																 QSettings::IniFormat);

	cfg->beginGroup("USE");
	isUse = cfg->value("ROTARY").toBool();
	cfg->endGroup();

	cfg->beginGroup("ROTARY");
	udp_recv.IP = cfg->value("IP", "192.168.1.79").toString();
	udp_recv.port = cfg->value("UDP_RECV_PORT", 12346).toInt();
	udp_send.IP = cfg->value("IP", "192.168.1.79").toString();
	udp_send.port = cfg->value("UDP_SEND_PORT", 22346).toInt();
	cfg->endGroup();

//	qDebug() << udp_recv.port;

	return 0;
}

void Rotary::setThread(QThread *th)
{
	udp_recv.socket->moveToThread(th);
	udp_send.socket->moveToThread(th);
	this->moveToThread(th);
}

void Rotary::finalize()
{
}

/*!
 * \brief Rotary::connect
 * \return
 */
int Rotary::open()
{
	udp_recv.socket = new QUdpSocket();
	udp_recv.socket->bind(udp_recv.port);

	udp_send.socket = new QUdpSocket();
	return 0;
}

/*!
 * \brief Rotary::disconnect
 */
void Rotary::close()
{
	return;
}

/*!
 * \brief Rotary::CountReset
 * \return
 */
int Rotary::CountReset()
{
	return 0;
}

int Rotary::recv(RotaryInfo::Data_t &data)
{
	if(!isUse) return 0;

	RotaryInfo::Recv_t recv;
	//	qDebug() << udp_recv.socket->bytesAvailable();
	if(udp_recv.socket->waitForReadyRead(33)){
		while(udp_recv.socket->bytesAvailable() > 0){
			udp_recv.socket->readDatagram((char*)&recv, sizeof(RotaryInfo::Recv_t));
		}
	}
	else{
		//		qDebug() << "Not available datagram";
		return 0;
	}

	data.pulse[1] = data.pulse[1];
	data.pulse[0] = recv.pulse;
	//	data.d[1] = data.d[0];
	//	data.d[0] = recv.dis;
	data.v = recv.velo;
	return 0;
}



