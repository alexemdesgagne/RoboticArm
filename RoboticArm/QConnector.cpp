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

QList<QSerialPortInfo> QConnector::getPorts() {
	return QSerialPortInfo::availablePorts();
}
