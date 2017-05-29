#include "AboutWidget.h"
#include "ui_AboutWidget.h"
#include "Device.h"
#include "SystemUtils.h"

#include <QDebug>
#include <QProcess>

AboutWidget::AboutWidget(Device *device, QWidget *parent)
	: StandardWidget(device, parent),
	ui(new Ui::AboutWidget)
{
	ui->setupUi(this);
	ui->deviceName->setText(device->name() + " v" + device->version());
	ui->ipAddress->setText(getIpAddress());

	performStandardSetup(tr("About"));
}

AboutWidget::~AboutWidget()
{
	delete ui;
}

QString AboutWidget::getIpAddress() const
{
	QProcess proc;
	proc.start("hostname", QStringList("-I"));
	proc.waitForFinished(5000);

	auto list = QString(proc.readAllStandardOutput()).split(' ');
	return list[list.size() - 2];
}
