#include "EmbeddedSystemDebugger.h"
#include <QGridLayout>
#include <QGroupBox>
#include <sstream>
#include <algorithm>
//#include <iterator>

#define	MAINWINDOW_DEFAULT_WIDTH				2500
#define	MAINWINDOW_DEFAULT_HEIGHT			1700
#define	MAINWINDOW_SCREENPERCENTAGE			0.8

EmbeddedSystemDebugger::EmbeddedSystemDebugger(QWidget *parent, QRect const *screenSize)
	: QMainWindow(parent), centralWidget(Q_NULLPTR), enter_button(Q_NULLPTR), clear_button(Q_NULLPTR), input_ledit(Q_NULLPTR), console_tedit(Q_NULLPTR)
{
	//ui.setupUi(this); Not using Creator for now

	// Setup main Window size
	setMainWindowSize(screenSize);

	// Initialize all Widgets
	initWidgets();
	initConnections();
}

// Sets the application's main Window Size
void EmbeddedSystemDebugger::setMainWindowSize(QRect const *screenSize)
{
	// If screen dimensions are available, set window size to MAINWINDOW_SCREENPERCENTAGE % of screen
	int width, height;
	if (screenSize != Q_NULLPTR) {
		width = screenSize->width() * MAINWINDOW_SCREENPERCENTAGE;
		height = screenSize->height() * MAINWINDOW_SCREENPERCENTAGE;
	}
	else {
		width = MAINWINDOW_DEFAULT_WIDTH;
		height = MAINWINDOW_DEFAULT_HEIGHT;
	}

	QSize mainWindowSize(width,height);
	this->setFixedSize(mainWindowSize);
}

// Creates and configures layout on all widgets on the main application window
void EmbeddedSystemDebugger::initWidgets()
{
	// Must create and define central widget. All other widgets will be children of centralWidget
	centralWidget = new QWidget(this);

	// Create layout and add remaining Widget. Layout behaves similar to builder pattern.
	QVBoxLayout* vb_layout = new QVBoxLayout(centralWidget);

	// Configure input terminal and enter button
	QGroupBox* group_box = new QGroupBox();
	QHBoxLayout* h_layout = new QHBoxLayout();
	input_ledit = new QLineEdit();
	input_ledit->setPlaceholderText(tr("Enter Command"));
	h_layout->addWidget(input_ledit);
	enter_button = new QPushButton(tr("Enter"));
	h_layout->addWidget(enter_button);
	group_box->setLayout(h_layout);
	vb_layout->addWidget(group_box);

	// Configure console
	console_tedit = new QTextEdit();
	console_tedit->setReadOnly(true);
	vb_layout->addWidget(console_tedit);

	// Configure clear button to clear console
	clear_button = new QPushButton(tr("Clear"));
	clear_button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum); // This policy enforces the widget size to be no larger than the size provided by sizeHint().
	vb_layout->addWidget(clear_button);

	// The following sets the layout & reparents widgets from vb_layout to centralWidget
	centralWidget->setLayout(vb_layout);
	this->setCentralWidget(centralWidget); // required
}

// Connects Widgets to corresponding Slots which provide widget behavior/functionality
void EmbeddedSystemDebugger::initConnections()
{
	// Syntax: connect(widget, Signal, this, Slot)
	connect(input_ledit, &QLineEdit::returnPressed, this, &EmbeddedSystemDebugger::getEnteredCommand);
	connect(enter_button, &QPushButton::released, this, &EmbeddedSystemDebugger::getEnteredCommand);
	connect(clear_button, &QPushButton::released, this, &EmbeddedSystemDebugger::clearConsole);
}

// Writes msg to console widget
void EmbeddedSystemDebugger::consoleWrite(const QString& msg)
{
	console_tedit->append(msg);
}

// Splits command into tokens, delimited by spaces. Thanks stackoverflow.
bool EmbeddedSystemDebugger::tokenizeCommand(std::vector<std::string> &tokens, const std::string &command)
{
	std::istringstream iss(command);
	std::copy(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
		std::back_inserter(tokens));
	if (tokens.size() > 0)
		return true;
	else
		return false;
}

void EmbeddedSystemDebugger::getSerialPorts(const std::string &arg)
{
	if (!arg.empty())
		consoleWrite(QString::fromStdString("getSerialPorts, arg: " + arg));
	else
		consoleWrite(QString::fromStdString("getSerialPorts, no arg"));
}

void EmbeddedSystemDebugger::testSerialPorts(const std::string &arg)
{
	if (!arg.empty())
		consoleWrite(QString::fromStdString("testSerialPorts, arg: " + arg));
	else
		consoleWrite(QString::fromStdString("testSerialPorts, no arg"));
}

// Slot: Retrieves entered command from input terminal and writes it to console. Clears input terminal after retrieval
void EmbeddedSystemDebugger::getEnteredCommand()	
{
	const QString command = input_ledit->text();
	input_ledit->clear();
	if (command.isEmpty()) // Ignore empty input
		return;
	consoleWrite(command);
	
	// Check to see if command was a EmbeddedSystemDebugger Debug command
	std::vector<std::string> tokens;
	if (!tokenizeCommand(tokens, command.toStdString())) {
		QString error_msg = "Error: Unable to tokenize command" + command;
		consoleWrite(error_msg);
		return;
	}
	if (tokens.at(0) == debug_token) {
		std::unordered_map<std::string, _debugCallbackFunction>::const_iterator index = debug_functions.find(tokens.at(1));
		std::string test = "test";
		if (index != debug_functions.end()) {// if found, invoke the corresponding debug function
			if (tokens.size() == 2)
				(this->*(index->second)) (""); // this syntax took forever -__-
			else if (tokens.size() == 3)
				(this->*(index->second)) (tokens.at(2));
			else
				consoleWrite(QString::fromStdString("Error: Too many arguments for " + index->first));
		}
		else {
			if (tokens.size() > 1)
				consoleWrite(QString::fromStdString("Error: Command '" + command.toStdString() + "' not recognized"));
			else
				consoleWrite(QString::fromStdString("Error: No debug command entered"));
		}
	}
	else {
		consoleWrite(QString::fromStdString("TODO: Send this command to embedded device IF connected! Else error!"));
	}
}

// Slot: Clears the console
void EmbeddedSystemDebugger::clearConsole()
{
	console_tedit->clear();
}
