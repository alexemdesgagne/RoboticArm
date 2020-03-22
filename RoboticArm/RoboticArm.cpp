#include "RoboticArm.h"
#include "QControlPanel.h"
#include "QConnectionPanel.h"

RoboticArm::RoboticArm(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QVBoxLayout * mainLayout{ new QVBoxLayout };
	QWidget * mainWidget{ new QWidget };
	QControlPanel * controlWidget{ new QControlPanel(mainWidget) };
	QConnectionPanel * connectionWidget{ new QConnectionPanel(mainWidget) };

	mainLayout->addWidget(controlWidget);
	mainLayout->addWidget(connectionWidget);
	mainWidget->setLayout(mainLayout);
	setCentralWidget(mainWidget);
}
