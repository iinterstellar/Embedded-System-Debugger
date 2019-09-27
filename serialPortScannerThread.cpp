#include "serialPortScannerThread.h"

#include <QTime>

// Constructor. Note: Object owner must kick off thread execution
SerialPortScannerThread::SerialPortScannerThread(QObject* parent)
	: QThread(parent), restart(false), abort_thread(false), keep_scanning(false), get_serialports_request(false), run_test(false), test_iterations(0), device_found(false)
{}

SerialPortScannerThread::~SerialPortScannerThread()
{
	mutex.lock();
	abort_thread = true;
	mutex.unlock();
	wait();
}

// Sets selected config
void SerialPortScannerThread::setConfig(std::unique_ptr<Config> selected_config) 
{
	mutex.lock();
	debugger_config = std::move(selected_config);
	mutex.unlock();
}

// Sets flag to abort thread execution
void SerialPortScannerThread::abortThread()
{
	mutex.lock();
	abort_thread = true;
	mutex.unlock();
	if (!isRunning())
		start(IdlePriority);
	else
		condition.wakeOne();
}

// Slot: Sets flag to retrieve serial devices info and sends them to GUI thread for outputting
void SerialPortScannerThread::getSerialPorts()
{
	mutex.lock();
	get_serialports_request = true;
	mutex.unlock();
	if (!isRunning())
		start(IdlePriority);
	else
		condition.wakeOne();
}

// Slot: Sets flag to benchmark test getSerialPorts
void SerialPortScannerThread::testGetSerialPorts(unsigned int repititions)
{
	mutex.lock();
	run_test = true;
	test_iterations = repititions;
	mutex.unlock();
	if (!isRunning())
		start(IdlePriority);
	else
		condition.wakeOne();
}

// Slot: Writes running config to GUI console
void SerialPortScannerThread::getConfig() 
{
	emit writeToConsole((*debugger_config).printDevices());
}

// Slot: Restarts scanning if device connection has been lost
void SerialPortScannerThread::deviceConnectionLost()
{
	mutex.lock();
	keep_scanning = true;
	device_found = false;
	mutex.unlock();
	if (!isRunning())
		start(IdlePriority);
	else
		condition.wakeOne();
}

// Main Thread. Execution controlled by state machine
void SerialPortScannerThread::run()	{
	enum SM1_States { Init, Scanning, Get_Ports, Test_Scanning, Device_Found, Sleep } state;
	state = Init;
	forever {
		// Action Handling
		switch (state) {
		case Init:
			if (!device_found) {
				mutex.lock();
				keep_scanning = true;
				mutex.unlock();
			}
			else {
				mutex.lock();
				keep_scanning = false;
				mutex.unlock();
			}
			break;
		case Scanning:
			scanSerialPorts();
			break;
		case Get_Ports:
			getScannedSerialPorts();
			break;
		case Test_Scanning:
			testScanSerialPorts();
			break;
		case Device_Found:
			setupDeviceComm(); // TODO: This should block until device comm attempt completes
			break;
		case Sleep:
			mutex.lock();
			if (!keep_scanning)
				condition.wait(&mutex);
			mutex.unlock();
			break;
		default:
			break;
		}
		// State Transition Handling
		switch (state) {
		case Init:
			if (keep_scanning)
				state = Scanning;
			else
				state = Sleep;
			break;
		case Scanning:
			if (device_found)
				state = Device_Found;
			else if (get_serialports_request)
				state = Get_Ports;
			else if (run_test)
				state = Test_Scanning;
			else if (!keep_scanning)
				state = Sleep;
			else// if (!device_found)
				state = Scanning;
			break;
		case Get_Ports:
			if (run_test)
				state = Test_Scanning;
			else if (keep_scanning)
				state = Scanning;
			else
				state = Sleep;
			break;
		case Test_Scanning:
			if (get_serialports_request)
				state = Get_Ports;
			else if (keep_scanning)
				state = Scanning;
			else
				state = Sleep;
			break;
		case Device_Found:
			state = Sleep; // TODO: Different transition depending on device comm config attempt outcome
			break;
		case Sleep:
			if (get_serialports_request)
				state = Get_Ports;
			else if (run_test)
				state = Test_Scanning;
			else if (keep_scanning)
				state = Scanning;
			else
				state = Sleep;
			break;
		default:
			break;
		}

		// Kill thread on request
		if (abort_thread)
			return;
	}
}

// Scans serial ports for desired serial device. Sets flag and device serial port info if device found
void SerialPortScannerThread::scanSerialPorts()
{
	static unsigned count = 0;
	QString collectedSerialPorts;
	const auto serialPortInfos = QSerialPortInfo::availablePorts();

	collectedSerialPorts = QString::fromStdString("Total number of ports available: ") + QString::number(serialPortInfos.count()) + QString::fromStdString("\n");

	const QString blankString = "N/A";
	QString description;
	QString manufacturer;
	QString serial_num;
	QString vendor_id;
	QString product_id;

	for (const QSerialPortInfo& serialPortInfo : serialPortInfos) {
		description = serialPortInfo.description();
		manufacturer = serialPortInfo.manufacturer();
		vendor_id = serialPortInfo.hasVendorIdentifier() 
			? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) 
			: blankString;
		product_id = serialPortInfo.hasProductIdentifier()
			? QByteArray::number(serialPortInfo.productIdentifier(), 16) 
			: blankString;
		device_info current_device(description,manufacturer,vendor_id,product_id);
		if ((*debugger_config).findDevice(current_device)) {
			if (run_test); // Skip evaluation if test is running
			else if (serialPortInfo.isBusy() && !run_test) {
				QString notification = "Attention! Device found, but the device was busy!\n"
					+ QString::fromStdString("Port: ") + serialPortInfo.portName() + QString::fromStdString("\n")
					+ QString::fromStdString("Location: ") + serialPortInfo.systemLocation() + QString::fromStdString("\n")
					+ QString::fromStdString("Description: ") + (!description.isEmpty() ? description : blankString) + QString::fromStdString("\n")
					+ QString::fromStdString("Manufacturer: ") + (!manufacturer.isEmpty() ? manufacturer : blankString) + QString::fromStdString("\n")
					+ QString::fromStdString("Serial number: ") + (!serial_num.isEmpty() ? serial_num : blankString) + QString::fromStdString("\n")
					+ QString::fromStdString("Vendor Identifier: ") + (serialPortInfo.hasVendorIdentifier()
						? QByteArray::number(serialPortInfo.vendorIdentifier(), 16)
						: blankString) + QString::fromStdString("\n")
					+ QString::fromStdString("Product Identifier: ") + (serialPortInfo.hasProductIdentifier()
						? QByteArray::number(serialPortInfo.productIdentifier(), 16)
						: blankString) + QString::fromStdString("\n")
					+ QString::fromStdString("Busy: ") + (serialPortInfo.isBusy() ? "Yes" : "No") + QString::fromStdString("\n");
				emit writeToConsole(notification);
			}
			else {
				mutex.lock();
				device_found = true;
				my_device_info = serialPortInfo;
				mutex.unlock();
			}
		}
	}

	// Test output to ensure thread is running
	++count;
	if (count > 10000) {
		count = 0;
		emit writeToConsole(QString::fromStdString("We stay scanning homie"));
	}
}

// Retrieves and writes serial devices to GUI console
void SerialPortScannerThread::getScannedSerialPorts()
{
	QString collectedSerialPorts;
	const auto serialPortInfos = QSerialPortInfo::availablePorts();

	collectedSerialPorts = QString::fromStdString("Total number of ports available: ") + QString::number(serialPortInfos.count()) + QString::fromStdString("\n");

	const QString blankString = "N/A";
	QString description;
	QString manufacturer;
	QString serialNumber;

	for (const QSerialPortInfo& serialPortInfo : serialPortInfos) {
		description = serialPortInfo.description();
		manufacturer = serialPortInfo.manufacturer();
		serialNumber = serialPortInfo.serialNumber();
		collectedSerialPorts += QString::fromStdString("\n")
			+ QString::fromStdString("Port: ") + serialPortInfo.portName() + QString::fromStdString("\n")
			+ QString::fromStdString("Location: ") + serialPortInfo.systemLocation() + QString::fromStdString("\n")
			+ QString::fromStdString("Description: ") + (!description.isEmpty() ? description : blankString) + QString::fromStdString("\n")
			+ QString::fromStdString("Manufacturer: ") + (!manufacturer.isEmpty() ? manufacturer : blankString) + QString::fromStdString("\n")
			+ QString::fromStdString("Serial number: ") + (!serialNumber.isEmpty() ? serialNumber : blankString) + QString::fromStdString("\n")
			+ QString::fromStdString("Vendor Identifier: ") + (serialPortInfo.hasVendorIdentifier()
				? QByteArray::number(serialPortInfo.vendorIdentifier(), 16)
				: blankString) + QString::fromStdString("\n")
			+ QString::fromStdString("Product Identifier: ") + (serialPortInfo.hasProductIdentifier()
				? QByteArray::number(serialPortInfo.productIdentifier(), 16)
				: blankString) + QString::fromStdString("\n")
			+ QString::fromStdString("Busy: ") + (serialPortInfo.isBusy() ? "Yes" : "No") + QString::fromStdString("\n");
	}

	emit writeToConsole(collectedSerialPorts);

	mutex.lock();
	get_serialports_request = false;
	mutex.unlock();
}

// Tests scanSerialPorts function for benchmarking execution speed
void SerialPortScannerThread::testScanSerialPorts()
{
	QString collectedSerialPorts;
	QTime test_timer(0, 0, 0, 0);
	unsigned int sum = 0;
	test_timer.start();
	for (unsigned int i = 0; i < test_iterations; i++) {
		scanSerialPorts();
		sum += (unsigned)test_timer.restart();
	}
	double average = (double)sum / (double)test_iterations;
	collectedSerialPorts += "\ngetSerialPorts Benchmark\navg. elapsed time: " + QString::number(average, 'g', 6) + QString::fromStdString(" ms, iterations: ")
		+ QString::number(test_iterations) + QString::fromStdString("\n");
	emit writeToConsole(collectedSerialPorts);
	mutex.lock();
	run_test = false;
	test_iterations = 0;
	mutex.unlock();
}

// This function configures serial communication to found serial device
void SerialPortScannerThread::setupDeviceComm()
{
	// TODO: Implement real device setup
	emit writeToConsole(QString::fromStdString("Setting up Found Device [ ") + my_device_info.description() + QString::fromStdString(" ] !\n"));
	mutex.lock();
	keep_scanning = false;
	mutex.unlock();
}