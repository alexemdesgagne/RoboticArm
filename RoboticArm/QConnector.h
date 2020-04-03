#pragma once

#include <QObject>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class QConnector : public QObject
{
	Q_OBJECT

public:
	QConnector(QObject *parent);
	~QConnector();

	void connection(QString portName, int baudRate);
	void disconnect();
	void setControlMode();
	void setRecordMode();
	void sayHello();
	QList<QSerialPortInfo> getPorts();

private:
	QSerialPort * mSerial;
};
