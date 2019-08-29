#include "EmbeddedSystemDebugger.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	EmbeddedSystemDebugger w;
	w.show();
	return a.exec();
}
