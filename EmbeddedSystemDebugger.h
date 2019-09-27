#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <unordered_map>
#include <string>
#include <vector>
#include "serialPortScannerThread.h"
//#include "ui_EmbeddedSystemDebugger.h"

class EmbeddedSystemDebugger : public QMainWindow
{
	Q_OBJECT

public:
	EmbeddedSystemDebugger(QWidget *parent = Q_NULLPTR, QRect const *screenSize = Q_NULLPTR);
	~EmbeddedSystemDebugger();

private:
	//Ui::EmbeddedSystemDebuggerClass ui; Not using creator for now

	// Widgets
	QWidget* centralWidget;
	QPushButton* enter_button;
	QPushButton* clear_button;
	QLineEdit* input_ledit;
	QTextEdit* console_tedit;

	// GUI setup functions
	void setMainWindowSize(QRect const* screenSize = Q_NULLPTR);
	void initWidgets();
	void initConnections();

	// Functions
	void consoleWrite(const QString&);
	bool tokenizeCommand(std::vector<std::string>&,const std::string&);
	void requestSerialPorts(const std::string& arg = "");
	void testRequestSerialPorts(const std::string &arg = "");
	void requestConfig(const std::string &arg = "");

	// Private Data Structures
	const std::string debug_token = "_esd";
	std::vector<std::string> const debug_commands = {
		"get_serialPorts",
		"test_serialPorts"
	};
	typedef void (EmbeddedSystemDebugger:: * _debugCallbackFunction) (const std::string&);
	std::unordered_map<std::string, _debugCallbackFunction> const debug_functions = {
		{ "get_serialPorts", &EmbeddedSystemDebugger::requestSerialPorts },
		{ "test_serialPorts", &EmbeddedSystemDebugger::testRequestSerialPorts },
		{ "get_config", &EmbeddedSystemDebugger::requestConfig }
	};
	SerialPortScannerThread device_manager;

signals:
	void getSerialPortsRequest();
	void testGetSerialPortsRequest(unsigned int);
	void getConfigRequest();

private slots:
	void getEnteredCommand();
	void clearConsole();
};
