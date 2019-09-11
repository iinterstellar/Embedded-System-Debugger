#include "serialPortScannerThread.h"

#include <QSerialPortInfo>

serialPortScannerThread::serialPortScannerThread(QObject *parent)
	: QThread(parent)
{
}

serialPortScannerThread::~serialPortScannerThread()
{
}

void serialPortScannerThread::run()	{
	// Get current list of available Ports
	/*static QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
	for (const QSerialPortInfo& info : ports) {
		QString s = QObject::tr("Port: ") + info.portName() + "\n"
			+ QObject::tr("Location: ") + info.systemLocation() + "\n"
			+ QObject::tr("Description: ") + info.description() + "\n"
			+ QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
			+ QObject::tr("Serial number: ") + info.serialNumber() + "\n"
			+ QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
			+ QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
			+ QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";

		//TODO: https://doc.qt.io/qt-5/qtcore-threads-semaphores-example.html
	}*/
}


