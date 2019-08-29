#include "EmbeddedSystemDebugger.h"

#define	MAINWINDOW_DEFAULT_WIDTH			2500
#define	MAINWINDOW_DEFAULT_HEIGHT		1700
#define	MAINWINDOW_SCREENPERCENTAGE		0.8

EmbeddedSystemDebugger::EmbeddedSystemDebugger(QWidget *parent, QRect const *screenSize)
	: QMainWindow(parent)
{
	//ui.setupUi(this); Not using Creator for now

	// Setup main Window size
	setMainWindowSize(screenSize);
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
