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

	static void connection();
	static void disconnect();
	static QList<QSerialPortInfo> getPorts();

private:
	QSerialPort * serial;
};
