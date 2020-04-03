#include "QConnector.h"
#include <QtDebug>
#include <QByteArray>


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

void QConnector::setControlMode()
{
	if (mSerial->isOpen()) {
		QByteArray buffer = QByteArray("1m;");
		mSerial->write(buffer);
		mSerial->waitForBytesWritten(-1);
	}
}

void QConnector::setRecordMode()
{
	if (mSerial->isOpen()) {
		QByteArray buffer = QByteArray("2m;");
		mSerial->write(buffer);
		mSerial->waitForBytesWritten(-1);
	}
}

void QConnector::sayHello()
{
	if (mSerial->isOpen()) {
		QByteArray buffer = QByteArray("4p;");
		mSerial->write(buffer);
		mSerial->waitForBytesWritten(-1);
	}
}

QList<QSerialPortInfo> QConnector::getPorts() {
	return QSerialPortInfo::availablePorts();
}
