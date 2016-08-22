#include "Options.h"

#ifdef NETWORK_ENABLED

#include "NetworkSettingsWidget.h"
#include "NetworkStatusWidget.h"
#include "ui_NetworkSettingsWidget.h"
#include "MenuBar.h"
#include "RootController.h"
#include "StatusBar.h"
#include "Device.h"
#include "ConnectWidget.h"
#include "ManageNetworksWidget.h"
#include "NetworkManager.h"
#include "SystemUtils.h"

#include <QTimer>

#include <QDebug>

NetworkSettingsWidget::NetworkSettingsWidget(Device *device, QWidget *parent)
	: StandardWidget(device, parent),
	ui(new Ui::NetworkSettingsWidget)
{
	ui->setupUi(this);
	performStandardSetup(tr("Network Settings"));
	
	ui->turnOn->setVisible(false);
	ui->turnOff->setVisible(false);


	QObject::connect(ui->connect, SIGNAL(clicked()), SLOT(connect()));
	QObject::connect(ui->manage, SIGNAL(clicked()), SLOT(manage()));
	NetworkManager::ref().connect(ui->turnOn, SIGNAL(clicked()), SLOT(enableAP())); //SLOT(turnOn()));
	NetworkManager::ref().connect(ui->turnOff, SIGNAL(clicked()), SLOT(disableAP())); //SLOT(turnOff()));

	// TODO: put back after we support client mode WiFi
	ui->connect->setVisible(false);
	ui->manage->setVisible(false);
	ui->security->setVisible(false);
	ui->securityLabel->setVisible(false);
	
	QObject::connect(&NetworkManager::ref(),
		SIGNAL(stateChanged(const NetworkManager::State &, const NetworkManager::State &)),
		SLOT(stateChanged(const NetworkManager::State &, const NetworkManager::State &)));
	
	QTimer *updateTimer = new QTimer(this);
	QObject::connect(updateTimer, SIGNAL(timeout()), SLOT(updateInformation()));
	updateTimer->start(10000);

	updateInformation();
}

NetworkSettingsWidget::~NetworkSettingsWidget()
{
	delete ui;
}

void NetworkSettingsWidget::connect()
{
	RootController::ref().presentWidget(new ConnectWidget(device()));
}

void NetworkSettingsWidget::manage()
{
	RootController::ref().presentWidget(new ManageNetworksWidget(device()));
}

bool NetworkSettingsWidget::enableAP()
{
#ifdef WALLABY
	int ret = system("/usr/bin/python /usr/bin/wifi_configurator.py");
	return (ret == 0);
#endif
	return true;
}


bool NetworkSettingsWidget::disableAP()
{
#ifdef WALLABY
	int ret = system("killall hostapd");
	return (ret == 0);
#endif
	return true;
}

void NetworkSettingsWidget::updateInformation()
{
	const bool on = NetworkStatusWidget::isNetworkUp(); //NetworkManager::ref().isOn();
	ui->state->setText(on ? tr("ON") : tr("OFF"));
	ui->turnOn->setVisible(!on);
	ui->turnOff->setVisible(on);
	ui->connect->setEnabled(on);

	const QString id = device()->id();
	if(!id.isEmpty()) {
		const QString password = SystemUtils::sha256(id).left(6) + "00";
		const QString ssid = id + "-wallaby";
		ui->ssid->setText(ssid);
		ui->password->setText(password);
	}

	Network active = NetworkManager::ref().active();
	//ui->ssid->setText(active.ssid());
	ui->security->setText(active.securityString());
	const QString ip = NetworkManager::ref().ipAddress();
	ui->ip->setText(ip.isEmpty() ? tr("No IP") : ip);
}

void NetworkSettingsWidget::stateChanged(const NetworkManager::State &newState, const NetworkManager::State &oldState)
{
	qDebug() << "State Changed to" << newState;
	QTimer::singleShot(300, this, SLOT(updateInformation()));
}

#endif
