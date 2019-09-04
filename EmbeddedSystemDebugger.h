#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
//#include "ui_EmbeddedSystemDebugger.h"

class EmbeddedSystemDebugger : public QMainWindow
{
	Q_OBJECT

public:
	EmbeddedSystemDebugger(QWidget *parent = Q_NULLPTR, QRect const *screenSize = Q_NULLPTR);

private:
	//Ui::EmbeddedSystemDebuggerClass ui; Not using creator for now

	// Widgets
	QWidget* centralWidget;
	QPushButton* enter_button;
	QPushButton* clear_button;
	QLineEdit* input_ledit;
	QTextEdit* console_tedit;

	// GUI setup functions
	void setMainWindowSize(QRect const* screenSize);
	void initWidgets();
};
