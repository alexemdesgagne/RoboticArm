#include "RoboticArm.h"
#include "QControlPanel.h"
#include "QConnectionPanel.h"
#include "QConnector.h"
#include "Q3DView.h"
#include <QSize>

RoboticArm::RoboticArm(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QHBoxLayout * mainLayout{ new QHBoxLayout };
	QVBoxLayout * rightLayout{ new QVBoxLayout };
	QWidget * mainWidget{ new QWidget };
	QConnector * connector{ new QConnector(mainWidget) };
	QControlPanel * controlWidget{ new QControlPanel(mainWidget, connector) };
	QConnectionPanel * connectionWidget{ new QConnectionPanel(mainWidget, connector) };
	Q3DView * armView{ new Q3DView() };
	QWidget *container = QWidget::createWindowContainer(armView);
	container->setMinimumSize(QSize(200, 100));

	rightLayout->addWidget(controlWidget);
	rightLayout->addWidget(connectionWidget);
	mainLayout->addWidget(container, 1);
	mainLayout->addLayout(rightLayout);
	mainWidget->setLayout(mainLayout);
	setCentralWidget(mainWidget);
}
