#pragma once

#include <QGroupBox>
#include <QPushButton>
#include <QString>
#include <QFormLayout>
#include <QComboBox>
#include <QColor>
#include <QLabel>
#include <QSize>
#include <QPixmap>
#include "QConnector.h"

class QPushButton;

class QConnectionPanel : public QGroupBox
{
	Q_OBJECT

public:
	QConnectionPanel(QWidget *parent, QConnector *connector);
	~QConnectionPanel();

	enum class State { connected = 0, disconnected = 1 };
	State state() const { return mState; }

private:
	State mState;
	QPushButton * mConnectButton;
	QPushButton * mDisconnectButton;
	QPushButton * mFunnyButton;
	QComboBox * mPortSelector;
	QComboBox * mBaudRateSelector;
	QConnector * mConnector;
	QLabel * mStateViewer;
	QPixmap mStatePixMap;
	
	void connection();
	void disconnection();
	void updateControls();
	void setParameters();
	void sayHello();

	static const QString sBoxTitle;
	static const QString sConnectButtonTitle;
	static const QString sDisconnectButtonTitle;
	static const QString sFunnyButtonTitle;
	static const QColor sConnectedColor;
	static const QColor sDisconnectedColor;
	static const int sStateViewerHeight;
	static const int sStateViewerWidth;
};
