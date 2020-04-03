#include "QConnector.h"
#include <QtDebug>



QConnector::QConnector(QObject *parent)
	: QObject(parent),
	mSerial{ new QSerialPort }
{
}

QConnector::~QConnector()
{
}

void QConnector::connection(QString portName, int baudRate) {
	mSerial->setPortName(portName);
	if (mSerial->open(QIODevice::ReadWrite)) {
		mSerial->setBaudRate(baudRate);
	}
}


void QConnector::disconnect() {
	mSerial->close();
}

void QConnector::setServosPositions(int posA, int posB, int posC, int posD, int posE, int posF) 
{
	QString packet = QString( QString::number(posA) + "a;" +
	                          QString::number(posB) + "b;" +
							  QString::number(posC) + "c;" +
	                          QString::number(posD) + "d;" +
							  QString::number(posE) + "e;" +
							  QString::number(posF) + "f;");
	QByteArray command = QByteArray(packet.toUtf8());
	send(command);
}

void QConnector::setControlMode()
{
	QByteArray command = QByteArray("1m;");
	send(command);
}

void QConnector::setRecordMode()
{
	QByteArray command = QByteArray("2m;");
	send(command);
}

void QConnector::sayHello()
{
	QByteArray command = QByteArray("4p;");
	send(command);
}

void QConnector::send(QByteArray & buffer) {
	if (mSerial->isOpen()) {
		mSerial->write(buffer);
		mSerial->waitForBytesWritten(-1);
	}
}

QList<QSerialPortInfo> QConnector::getPorts() {
	return QSerialPortInfo::availablePorts();
}
