#include "QControlPanel.h"

#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>

const QString QControlPanel::sBoxTitle{  QString("Control") };
const QString QControlPanel::sSetPositionsButtonTitle{ QString("Send positions") };
const QString QControlPanel::sControlButtonTitle{ QString("Control mode") };
const QString QControlPanel::sRecordButtonTitle{ QString("Record mode") };

QControlPanel::QControlPanel(QWidget *parent, QConnector *connector)
	: QGroupBox(parent),
	mState{ State::control },
	mWaistInput{ new QSpinBox },
	mShoulderInput{ new QSpinBox },
	mElbowInput{ new QSpinBox },
	mWristRollInput{ new QSpinBox },
	mWristPitchInput{ new QSpinBox },
	mGripperInput{ new QSpinBox },
	mSetPositionsButton{ new QPushButton(sSetPositionsButtonTitle) },
	mControlButton{ new QPushButton(sControlButtonTitle) },
	mRecordButton{ new QPushButton(sRecordButtonTitle) },
	mConnector{ connector }
{
	setTitle(sBoxTitle);
	QFormLayout * inputLayout{ new QFormLayout };
	inputLayout->addRow("Gripper", servoInputLayout(mGripperInput, 120, 180));
	inputLayout->addRow("Wrist pitch", servoInputLayout(mWristPitchInput, 0, 180));
	inputLayout->addRow("Wrist roll", servoInputLayout(mWristRollInput, 0, 180));
	inputLayout->addRow("Elbow", servoInputLayout(mElbowInput, 0, 180));
	inputLayout->addRow("Shoulder", servoInputLayout(mShoulderInput, 0, 180));
	inputLayout->addRow("Base rotation", servoInputLayout(mWaistInput, 0, 180));
	inputLayout->addRow(mSetPositionsButton);
	inputLayout->addRow(mControlButton);
	inputLayout->addRow(mRecordButton);
	setLayout(inputLayout);

	updateControls();

	connect(mSetPositionsButton, &QPushButton::pressed, this, &QControlPanel::updateServosPositions);
	connect(mControlButton, &QPushButton::pressed, this, &QControlPanel::control);
	connect(mRecordButton, &QPushButton::pressed, this, &QControlPanel::record);
}

QControlPanel::~QControlPanel()
{
}

QHBoxLayout * QControlPanel::servoInputLayout(QSpinBox * & spin, int min, int max)
{
	const int minWidth{ 150 };

	spin = new QSpinBox;
	spin->setRange(min, max);
	spin->setValue(min);
	spin->setMinimumWidth(minWidth);

	QHBoxLayout * layout{ new QHBoxLayout };
	layout->addWidget(spin);

	return layout;
}

void QControlPanel::control() {
	mState = State::control;
	updateControls();
	mConnector->setControlMode();
}

void QControlPanel::record() {
	mState = State::record;
	updateControls();
	mConnector->setRecordMode();
}

void QControlPanel::updateControls() 
{
	mControlButton->setEnabled(mState != State::control);
	mRecordButton->setEnabled(mState != State::record);

	mWaistInput->setEnabled(mState != State::record);
	mShoulderInput->setEnabled(mState != State::record);
	mElbowInput->setEnabled(mState != State::record);
	mWristRollInput->setEnabled(mState != State::record);
	mWristPitchInput->setEnabled(mState != State::record);
	mGripperInput->setEnabled(mState != State::record);
}

void QControlPanel::updateServosPositions()
{
	mConnector->setServosPositions( mGripperInput->value(),
	                                mWristPitchInput->value(),
									mWristRollInput->value(),
									mElbowInput->value(),
									mShoulderInput->value(),
									mWaistInput->value());
}
