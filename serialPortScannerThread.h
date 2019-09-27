#pragma once

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSerialPortInfo>
#include "TestConfig.h"

/*  SerialPortScannerThread Class
 *  Thread class that listens for desired serial device.
 */

class SerialPortScannerThread : public QThread
{
	Q_OBJECT

public:
	SerialPortScannerThread(QObject *parent = Q_NULLPTR);
	~SerialPortScannerThread();
	void setConfig(std::unique_ptr<Config>);
	void abortThread();

signals:
	void writeToConsole(const QString&);

public slots:
	void getSerialPorts();
	void testGetSerialPorts(unsigned int);
	void getConfig();
	void deviceConnectionLost();

private:
	// Private Data Structures
	std::unique_ptr<Config> debugger_config;
	QMutex mutex;
	QWaitCondition condition;
	QSerialPortInfo my_device_info;
	bool restart;
	bool abort_thread;
	bool keep_scanning;
	bool get_serialports_request;
	bool run_test;
	bool device_found;
	unsigned int test_iterations;
	// Private Functions
	void run() override;
	void scanSerialPorts();
	void getScannedSerialPorts();
	void testScanSerialPorts();
	void setupDeviceComm();
};
