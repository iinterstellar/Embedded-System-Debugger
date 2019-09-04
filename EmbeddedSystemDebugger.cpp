#include "EmbeddedSystemDebugger.h"
#include <QGridLayout>
#include <QGroupBox>

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
}

// Sets the application's main Window Size
void EmbeddedSystemDebugger::setMainWindowSize(QRect const *screenSize) {
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
void EmbeddedSystemDebugger::initWidgets()	{
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
	clear_button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum); // This policy enforces the size to be no larger than the size provided by sizeHint().
	vb_layout->addWidget(clear_button);

	// The following sets the layout & reparents widgets from vb_layout to centralWidget
	centralWidget->setLayout(vb_layout);
	this->setCentralWidget(centralWidget); // required
}
