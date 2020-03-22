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

}