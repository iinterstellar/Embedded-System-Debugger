#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EmbeddedSystemDebugger.h"

class EmbeddedSystemDebugger : public QMainWindow
{
	Q_OBJECT

public:
	EmbeddedSystemDebugger(QWidget *parent = Q_NULLPTR);

private:
	Ui::EmbeddedSystemDebuggerClass ui;
};
