#pragma once
#include "Config.h"
#include <vector>

/* Test Config Class
 * Implements a dummy Config class for testing purposes.
 */

class TestConfig : public Config
{
	public:
		TestConfig();
		~TestConfig();
		QString printDevices() const;
		bool findDevice(const device_info&) const;
	private:
		std::vector<const device_info*> device_registry;
};

