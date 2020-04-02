#include "QControlPanel.h"

#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>

const QString QControlPanel::sBoxTitle{  QString("Control") };
const QString QControlPanel::mControlButtonTitle{ QString("Control") };
const QString QControlPanel::mRecordButtonTitle{ QString("Record movements") };

QControlPanel::QControlPanel(QWidget *parent)
	: QGroupBox(parent),
	mState{ State::control },
	mWaistSlider{ new QSlider },
	mShoulderSlider{ new QSlider },
	mElbowSlider{ new QSlider },
	mWristRollSlider{ new QSlider },
	mWristPitchSlider{ new QSlider },
	mGripperSlider{ new QSlider },
	mControlButton{ new QPushButton(mControlButtonTitle) },
	mRecordButton{ new QPushButton(mRecordButtonTitle) }
{
	setTitle(sBoxTitle);
	QFormLayout * inputLayout{ new QFormLayout };
	inputLayout->addRow("Gripper", sliderLayout(mGripperSlider, 0, 180));
	inputLayout->addRow("Wrist pitch", sliderLayout(mWristPitchSlider, 0, 180));
	inputLayout->addRow("Wrist roll", sliderLayout(mWristRollSlider, 0, 180));
	inputLayout->addRow("Elbow", sliderLayout(mElbowSlider, 0, 180));
	inputLayout->addRow("Shoulder", sliderLayout(mShoulderSlider, 0, 180));
	inputLayout->addRow("Base rotation", sliderLayout(mWaistSlider, 0, 180));
	inputLayout->addRow(mControlButton);
	inputLayout->addRow(mRecordButton);
	setLayout(inputLayout);

	updateControls();

	connect(mControlButton, &QPushButton::pressed, this, &QControlPanel::control);
	connect(mRecordButton, &QPushButton::pressed, this, &QControlPanel::record);
}

QControlPanel::~QControlPanel()
{
}

QHBoxLayout * QControlPanel::sliderLayout(QSlider * & slider, int min, int max)
{
	const int minWidth{ 150 };

	slider = new QSlider;
	slider->setOrientation(Qt::Horizontal);
	slider->setRange(min, max);
	slider->setValue(min);
	slider->setMinimumWidth(minWidth);

	QLabel * label{ new QLabel(QString::number(min)) };

	connect(slider, &QSlider::valueChanged, label, static_cast<void(QLabel::*)(int)>(&QLabel::setNum));

	QHBoxLayout * layout{ new QHBoxLayout };
	layout->addWidget(slider);
	layout->addWidget(label);

	return layout;
}

void QControlPanel::control() {
	mState = State::control;
	updateControls();
}

void QControlPanel::record() {
	mState = State::record;
	updateControls();
}

void QControlPanel::updateControls() 
{
	mControlButton->setEnabled(mState != State::control);
	mRecordButton->setEnabled(mState != State::record);

	mWaistSlider->setEnabled(mState != State::record);
	mShoulderSlider->setEnabled(mState != State::record);
	mElbowSlider->setEnabled(mState != State::record);
	mWristRollSlider->setEnabled(mState != State::record);
	mWristPitchSlider->setEnabled(mState != State::record);
	mGripperSlider->setEnabled(mState != State::record);
}
