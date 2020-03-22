#include "QConnector.h"
#include <QtDebug>


QConnector::QConnector(QObject *parent)
	: QObject(parent)
{
}

QConnector::~QConnector()
{
}

void QConnector::connection() {
	
}

void QConnector::disconnect() {

}

QList<QSerialPortInfo> QConnector::getPorts() {
	return QSerialPortInfo::availablePorts();
}
