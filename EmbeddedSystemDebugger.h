#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EmbeddedSystemDebugger.h"

class EmbeddedSystemDebugger : public QMainWindow
{
	Q_OBJECT

public:
	EmbeddedSystemDebugger(QWidget *parent = Q_NULLPTR, QRect const *screenSize = Q_NULLPTR);

private:
	//Ui::EmbeddedSystemDebuggerClass ui; Not using creator for now
	// Sets the application's main Window Size
	void setMainWindowSize(QRect const* screenSize);
};
