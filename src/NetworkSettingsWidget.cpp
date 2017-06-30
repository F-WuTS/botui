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
#include "NetworkUtils.h"

#include <QTimer>

#include <QDebug>

NetworkSettingsWidget::NetworkSettingsWidget(Device* device, QWidget* parent)
        : StandardWidget(device, parent)
        , ui(new Ui::NetworkSettingsWidget)
{
        ui->setupUi(this);
        performStandardSetup(tr("Network Settings"));

        enableCoolOffTimer = new QTimer(this);
        enableCoolOffTimer->setSingleShot(true);

        ui->turnOn->setVisible(false);
        ui->turnOff->setVisible(false);

        QObject::connect(ui->connect, SIGNAL(clicked()), SLOT(connect()));
        QObject::connect(ui->manage, SIGNAL(clicked()), SLOT(manage()));
        QObject::connect(ui->turnOn, SIGNAL(clicked()), SLOT(enableWifi()));
        QObject::connect(ui->turnOff, SIGNAL(clicked()), SLOT(disableWifi()));

        QObject::connect(&NetworkManager::ref(),
                         SIGNAL(stateChanged(const NetworkManager::State&, const NetworkManager::State&)),
                         SLOT(stateChanged(const NetworkManager::State&, const NetworkManager::State&)));

        QTimer* updateTimer = new QTimer(this);
        QObject::connect(updateTimer, SIGNAL(timeout()), SLOT(updateInformation()));
        updateTimer->start(500);

        updateInformation();
}

NetworkSettingsWidget::~NetworkSettingsWidget()
{
        delete ui;
        delete enableCoolOffTimer;
}

void NetworkSettingsWidget::connect()
{
        RootController::ref().presentWidget(new ConnectWidget(device()));
}

void NetworkSettingsWidget::manage()
{
        RootController::ref().presentWidget(new ManageNetworksWidget(device()));
}

void NetworkSettingsWidget::updateInformation()
{
        const bool on = NetworkUtils::isWifiOn();
        ui->state->setText(on ? tr("ON") : tr("OFF"));
        ui->turnOn->setVisible(!on);
        ui->turnOff->setVisible(on);
        ui->connect->setEnabled(on);

        ui->ssid->setText(NetworkUtils::getCurrentNetwork());
        const QString ip = NetworkManager::ref().ipAddress();
        ui->ip->setText(!on ? tr("No IP") : ip);
}

void NetworkSettingsWidget::stateChanged(const NetworkManager::State& newState, const NetworkManager::State& oldState)
{
        qDebug() << "State Changed to" << newState;
        QTimer::singleShot(300, this, SLOT(updateInformation()));
}

void NetworkSettingsWidget::enableWifi()
{
        NetworkUtils::turnOnWifi();
}

void NetworkSettingsWidget::disableWifi()
{
        NetworkUtils::turnOffWifi();
}

#endif
