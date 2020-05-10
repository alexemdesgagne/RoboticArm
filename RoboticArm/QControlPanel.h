#pragma once

#include <QHBoxLayout>
#include <QGroupBox>
#include <QString>
#include <QSpinBox>
#include <QPushButton>

#include "QConnector.h"

class QPushButton;
class QSpinBox;

class QControlPanel : public QGroupBox
{
	Q_OBJECT

public:
	QControlPanel(QWidget *parent, QConnector *connector);
	~QControlPanel();

	enum class State { control = 0, record = 1 };
	State state() const { return mState; }

private:
	State mState;

	QSpinBox * mWaistInput;
	QSpinBox * mShoulderInput;
	QSpinBox * mElbowInput;
	QSpinBox * mWristRollInput;
	QSpinBox * mWristPitchInput;
	QSpinBox * mGripperInput;

	QPushButton * mSetPositionsButton;
	QPushButton * mControlButton;
	QPushButton * mRecordButton;

	QConnector * mConnector;

	QHBoxLayout * servoInputLayout(QSpinBox * & sb, int min, int max);
	void control();
	void record();
	void updateControls();
	void updateServosPositions();

	static const QString sBoxTitle;
	static const QString sSetPositionsButtonTitle;
	static const QString sControlButtonTitle;
	static const QString sRecordButtonTitle;
};