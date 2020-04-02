#pragma once

#include <QHBoxLayout>
#include <QGroupBox>
#include <QString>
#include <QPushButton>

class QSlider;
class QPushButton;

class QControlPanel : public QGroupBox
{
	Q_OBJECT

public:
	QControlPanel(QWidget *parent);
	~QControlPanel();

	enum class State { control = 0, record = 1 };
	State state() const { return mState; }

private:
	State mState;

	QSlider * mWaistSlider;
	QSlider * mShoulderSlider;
	QSlider * mElbowSlider;
	QSlider * mWristRollSlider;
	QSlider * mWristPitchSlider;
	QSlider * mGripperSlider;

	QPushButton * mControlButton;
	QPushButton * mRecordButton;

	QHBoxLayout * sliderLayout(QSlider * & sb, int min, int max);
	void control();
	void record();
	void updateControls();

	static const QString sBoxTitle;
	static const QString mControlButtonTitle;
	static const QString mRecordButtonTitle;
};