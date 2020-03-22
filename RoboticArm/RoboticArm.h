#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RoboticArm.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QWidget>

class RoboticArm : public QMainWindow
{
	Q_OBJECT

public:
	RoboticArm(QWidget *parent = Q_NULLPTR);

private:
	Ui::RoboticArmClass ui;
};
