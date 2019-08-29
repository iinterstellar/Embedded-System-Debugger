#include "EmbeddedSystemDebugger.h"
#include <QtWidgets/QApplication>
#include <qscreen.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Get screen size and pass it to main window constructor
	QScreen* screen = QApplication::primaryScreen();
	QRect const screenSize = screen->availableGeometry();
	EmbeddedSystemDebugger w(Q_NULLPTR, &screenSize);
	w.show();
	return a.exec();
}
