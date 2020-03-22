#pragma once

#include <QGroupBox>
#include <QPushButton>
#include <QString>
#include <QFormLayout>
#include <QComboBox>

class QPushButton;

class QConnectionPanel : public QGroupBox
{
	Q_OBJECT

public:
	QConnectionPanel(QWidget *parent);
	~QConnectionPanel();

private:
	QPushButton * mConnectButton;
	QComboBox * mPortSelector;
	QComboBox * mBaudRateSelector;

	void connection();
	void setParameters();

	static const QString sBoxTitle;
	static const QString sConnectButtonTitle;
};
