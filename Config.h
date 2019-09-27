#pragma once
#include <QString>

/* Abstract Class Config 
 * Specifies interface to Config Class and defines basic struct container for storing device information
 */

struct device_info
{
	const QString description;
	const QString manufacturer;
	const QString vendor_identifier;
	const QString product_identifier;
	device_info() : description(""), manufacturer(""), vendor_identifier(""), product_identifier("") {}
	device_info(QString descr, QString manuf, QString vend, QString prod) : description(descr), manufacturer(manuf),
		vendor_identifier(vend), product_identifier(prod) {}
	device_info(const device_info &original_copy) : description(original_copy.description), manufacturer(original_copy.manufacturer), 
		vendor_identifier(original_copy.vendor_identifier), product_identifier(original_copy.product_identifier) {}
	bool operator==(const device_info&rhs) const {
		if ((*this).description == rhs.description && (*this).manufacturer == rhs.manufacturer  && (*this).vendor_identifier == rhs.vendor_identifier 
			&& (*this).product_identifier == rhs.product_identifier)
			return true;
		else 
			return false;
	}
	bool operator!=(const device_info& rhs) const {
		return !operator==(rhs);
	}
	QString print() const {
		QString formatted_device_info = QString::fromStdString("Description: ") + (*this).description + QString::fromStdString("\n")
			+ QString::fromStdString("Manufacturer: ") + (*this).manufacturer + QString::fromStdString("\n")
			+ QString::fromStdString("Vendor Identifier: ") + (*this).vendor_identifier + QString::fromStdString("\n")
			+ QString::fromStdString("Product Identifier: ") + (*this).product_identifier + QString::fromStdString("\n");
		return formatted_device_info;
	}
};

class Config
{
	protected:
		Config() {}
	public:
		virtual ~Config() {}
		// Returns formatted QString with device info for all devices registered
		virtual QString printDevices() const = 0;
		// Returns true if device is found within device registry
		virtual bool findDevice(const device_info&) const = 0;

};

