#include "QControlPanel.h"

#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>

const QString QControlPanel::sBoxTitle{  QString("Control") };

QControlPanel::QControlPanel(QWidget *parent)
	: QGroupBox(parent),
	mWaistSlider{ new QSlider },
	mShoulderSlider{ new QSlider },
	mElbowSlider{ new QSlider },
	mWristRollSlider{ new QSlider },
	mWristPitchSlider{ new QSlider },
	mGripperSlider{ new QSlider }
{
	setTitle(sBoxTitle);
	QFormLayout * inputLayout{ new QFormLayout };
	inputLayout->addRow("Gripper", sliderLayout(mGripperSlider, 0, 180));
	inputLayout->addRow("Wrist pitch", sliderLayout(mWristPitchSlider, 0, 180));
	inputLayout->addRow("Wrist roll", sliderLayout(mWristRollSlider, 0, 180));
	inputLayout->addRow("Elbow", sliderLayout(mElbowSlider, 0, 180));
	inputLayout->addRow("Shoulder", sliderLayout(mShoulderSlider, 0, 180));
	inputLayout->addRow("Base rotation", sliderLayout(mWaistSlider, 0, 180));
	setLayout(inputLayout);
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
