#pragma once

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "Config.h"

/*  ESDThread Class
 *  Thread class containing main application interface logic. All threads shall have a reference to the application config. 
 *	Lastly, all threads shall have access to signal writeToConsole to output messages to GUI
 */

class ESDThread : public QThread
{
	Q_OBJECT

signals:
	void writeToConsole(const QString&);

protected:
	ESDThread(QObject* parent = Q_NULLPTR) : QThread(parent), abort_thread(false) {}
	std::shared_ptr<const Config> debugger_config;
	QMutex mutex;
	QWaitCondition condition;
	bool abort_thread;

public:
	virtual ~ESDThread() {}
	void setConfig(std::shared_ptr<const Config> const app_config) { debugger_config = app_config; }
	void abortThread() { 
		mutex.lock(); 
		abort_thread = true;
		mutex.unlock();
	}
	
};
