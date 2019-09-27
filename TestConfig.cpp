#include "TestConfig.h"

// Hard coded constructor creates dummy device_registry for testing
TestConfig::TestConfig()
{
	size_t i = 0;
	QString descr;
	QString manuf;
	QString vend;
	QString prod;
	for (i; i < 5; i++)
	{
		descr = QString::fromStdString("description_") + QString::number(i);
		manuf = QString::fromStdString("manufacturer_") + QString::number(i);
		vend = QString::fromStdString("vendor_") + QString::number(i);
		prod = QString::fromStdString("product_") + QString::number(i);
		device_registry.push_back(new const device_info(descr, manuf, vend, prod));
	}
	// Introduce actual, findable item reported in QSerialPortInfo
	descr = QString::fromStdString("Standard Serial over Bluetooth link");
	manuf = QString::fromStdString("Microsoft");
	vend = QString::fromStdString("N/A");
	prod = QString::fromStdString("N/A");
	device_registry.push_back(new const device_info(descr, manuf, vend, prod));
	++i;
	for (i; i < 10; i++)
	{
		descr = QString::fromStdString("description_") + QString::number(i);
		manuf = QString::fromStdString("manufacturer_") + QString::number(i);
		vend = QString::fromStdString("vendor_") + QString::number(i);
		prod = QString::fromStdString("product_") + QString::number(i);
		device_registry.push_back(new const device_info(descr, manuf, vend, prod));
	}
}

TestConfig::~TestConfig()
{
	for (auto it = device_registry.begin(); it != device_registry.end(); it++)
	{
		delete* it;
	}
}

// Returns formatted QString with device info for all devices registered
QString TestConfig::printDevices() const
{
	QString devices = "Test Config Registered Devices: Total = " + QString::number(device_registry.size()) + "\n";
	unsigned device_count = 1;
	for (auto it = device_registry.begin(); it != device_registry.end(); it++)
	{
		devices += QString::fromStdString("Device ") + QString::number(device_count) + QString::fromStdString("\n")
			+ (*it)->print() + QString::fromStdString("\n\n");
		++device_count;
	}
	return devices;
}

// Returns true if device is found within device registry
bool TestConfig::findDevice(const device_info &some_device) const
{
	for (auto it = device_registry.begin(); it != device_registry.end(); it++)
	{
		if (*((*it)) == some_device) // Should I have used vector of pointers?...
			return true;
	}
	return false;
}
