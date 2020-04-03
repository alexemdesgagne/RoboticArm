#pragma once

#include <QObject>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>

class QConnector : public QObject
{
	Q_OBJECT

public:
	QConnector(QObject *parent);
	~QConnector();

	void connection(QString portName, int baudRate);
	void disconnect();
	void setServosPositions(int posA, int posB, int posC, int posD, int posE, int posF);
	void setControlMode();
	void setRecordMode();
	void sayHello();
	void send(QByteArray & buffer);
	QList<QSerialPortInfo> getPorts();

private:
	QSerialPort * mSerial;
};
