#include "QConnectionPanel.h"

const QString QConnectionPanel::sBoxTitle{ QString("Connection") };
const QString QConnectionPanel::sConnectButtonTitle{ QString("Connect") };
const QString QConnectionPanel::sDisconnectButtonTitle{ QString("Disconnect") };
const QColor QConnectionPanel::sConnectedColor{ QColor(0, 161, 54) };
const QColor QConnectionPanel::sDisconnectedColor{ QColor(161, 38, 0) };
const int QConnectionPanel::sStateViewerHeight{ 15 };
const int QConnectionPanel::sStateViewerWidth{ 250 };

QConnectionPanel::QConnectionPanel(QWidget *parent)
	: QGroupBox(parent),
	mConnectButton{ new QPushButton(sConnectButtonTitle) },
	mDisconnectButton{ new QPushButton(sDisconnectButtonTitle) },
	mPortSelector{ new QComboBox },
	mBaudRateSelector{ new QComboBox },
	mConnector{new QConnector(this) },
	mState{ State::disconnected },
	mStateViewer{ new QLabel },
	mStatePixMap{ QPixmap(QSize(sStateViewerWidth, sStateViewerHeight)) }
{
	setTitle(sBoxTitle);

	QFormLayout * inputLayout{ new QFormLayout };
	inputLayout->addRow("Port", mPortSelector);
	inputLayout->addRow("Baud rate", mBaudRateSelector);
	inputLayout->addRow(mConnectButton);
	inputLayout->addRow(mDisconnectButton);
	inputLayout->addRow(mStateViewer);
	setLayout(inputLayout);

	setParameters();
	updateControls();

	connect(mConnectButton, &QPushButton::pressed, this, &QConnectionPanel::connection);
	connect(mDisconnectButton, &QPushButton::pressed, this, &QConnectionPanel::disconnection);
}

QConnectionPanel::~QConnectionPanel()
{
}

void QConnectionPanel::connection()
{
	if (mState == State::disconnected) {
		mConnector->connection(mPortSelector->currentText(), mBaudRateSelector->currentText().toInt());
		mState = State::connected;
	}
	updateControls();
}

void QConnectionPanel::disconnection()
{
	if (mState == State::connected) {
		mConnector->disconnect();
		mState = State::disconnected;
	}
	updateControls();
}

void QConnectionPanel::updateControls()
{
	mConnectButton->setEnabled(mState != State::connected);
	mDisconnectButton->setEnabled(mState != State::disconnected);

	if (mState == State::connected) {
		mStatePixMap.fill(sConnectedColor);
		mStateViewer->setPixmap(mStatePixMap);
	}
	else if (mState == State::disconnected) {
		mStatePixMap.fill(sDisconnectedColor);
		mStateViewer->setPixmap(mStatePixMap);
	}
}

void QConnectionPanel::setParameters() 
{
	// Setup ports name.
	for (QSerialPortInfo & port : mConnector->getPorts()) {
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