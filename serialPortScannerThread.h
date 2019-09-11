#pragma once

#include <QThread>

class serialPortScannerThread : public QThread
{
	Q_OBJECT

public:
	serialPortScannerThread(QObject *parent = Q_NULLPTR);
	~serialPortScannerThread();

private:
	void run() override;
};
