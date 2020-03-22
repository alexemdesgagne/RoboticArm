#pragma once

#include <QGroupBox>
#include <QString>

class QConnectionPanel : public QGroupBox
{
	Q_OBJECT

public:
	QConnectionPanel(QWidget *parent);
	~QConnectionPanel();

private:
	static const QString sBoxTitle;
};
