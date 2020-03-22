#include "QConnectionPanel.h"

const QString QConnectionPanel::sBoxTitle{ QString("Connection") };

QConnectionPanel::QConnectionPanel(QWidget *parent)
	: QGroupBox(parent)
{
	setTitle(sBoxTitle);
}

QConnectionPanel::~QConnectionPanel()
{
}
