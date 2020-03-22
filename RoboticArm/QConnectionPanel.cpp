#include "QConnectionPanel.h"
#include "QConnector.h"

const QString QConnectionPanel::sBoxTitle{ QString("Connection") };
const QString QConnectionPanel::sConnectButtonTitle{ QString("Connect") };

QConnectionPanel::QConnectionPanel(QWidget *parent)
	: QGroupBox(parent),
	mConnectButton{ new QPushButton(sConnectButtonTitle) },
	mPortSelector{ new QComboBox },
	mBaudRateSelector{ new QComboBox }
{
	setTitle(sBoxTitle);
	QFormLayout * inputLayout{ new QFormLayout };
	inputLayout->addRow("Port", mPortSelector);
	inputLayout->addRow("Baud rate", mBaudRateSelector);
	inputLayout->addRow(mConnectButton);
	setLayout(inputLayout);

	connect(mConnectButton, &QPushButton::pressed, this, &QConnectionPanel::connection);

	setParameters();
}

QConnectionPanel::~QConnectionPanel()
{
}

void QConnectionPanel::connection() 
{
	QConnector::connection();
}

void QConnectionPanel::setParameters() 
{
	// Setup ports name.
	for (QSerialPortInfo & port : QConnector::getPorts()) {
		mPortSelector->addItem(port.portName());
	}

	// Setup baud rates.
	mBaudRateSelector->addItem("1200");
	mBaudRateSelector->addItem("2400");
	mBaudRateSelector->addItem("4800");
	mBaudRateSelector->addItem("9600");
	mBaudRateSelector->addItem("19200");
	mBaudRateSelector->addItem("38400");
	mBaudRateSelector->addItem("57600");
	mBaudRateSelector->addItem("115200");
}