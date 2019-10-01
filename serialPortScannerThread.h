#pragma once

#include "ESDThread.h"
#include <QSerialPortInfo>

/*  SerialPortScannerThread Class
 *  Thread class that listens for desired serial device.
 */

class SerialPortScannerThread : public ESDThread
{
	Q_OBJECT

public:
	SerialPortScannerThread(QObject *parent = Q_NULLPTR);
	~SerialPortScannerThread();

public slots:
	void getSerialPorts();
	void testGetSerialPorts(unsigned int);
	void getConfig();
	void deviceConnectionLost();

private:
	// Private Data Structures
	QSerialPortInfo my_device_info;
	bool restart;
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
