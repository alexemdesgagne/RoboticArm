#pragma once

#include <QHBoxLayout>
#include <QGroupBox>
#include <QString>

class QSlider;

class QControlPanel : public QGroupBox
{
	Q_OBJECT

public:
	QControlPanel(QWidget *parent);
	~QControlPanel();

private:
	QSlider * mWaistSlider;
	QSlider * mShoulderSlider;
	QSlider * mElbowSlider;
	QSlider * mWristRollSlider;
	QSlider * mWristPitchSlider;
	QSlider * mGripperSlider;

	QHBoxLayout * sliderLayout(QSlider * & sb, int min, int max);

	static const QString sBoxTitle;
};
