#include "Options.h"

#ifdef NETWORK_ENABLED

#include "OtherNetworkWidget.h"
#include "ui_OtherNetworkWidget.h"
#include "MenuBar.h"
#include "RootController.h"
#include "StatusBar.h"
#include "Device.h"
#include "NetworkManager.h"
#include "KeyboardDialog.h"
#include <QDebug>
#include "NetworkUtils.h"

const static Network::Security securityChoices[] = {
        Network::None,
        Network::Wpa,
        Network::Wep,
        Network::DynamicWep
};

OtherNetworkWidget::OtherNetworkWidget(Device* device, QWidget* parent)
        : StandardWidget(device, parent)
        , ui(new Ui::OtherNetworkWidget)
        , m_ssid(new KeyboardDialog("Network Name"))
        , m_password(new KeyboardDialog("Password"))
{
        ui->setupUi(this);
        performStandardSetup(tr("Other Network"));

        ui->ssid->setInputProvider(m_ssid);
        ui->password->setInputProvider(m_password);

        connect(ui->join, SIGNAL(clicked()), SLOT(join()));
}

OtherNetworkWidget::~OtherNetworkWidget()
{
        delete ui;

        delete m_ssid;
        delete m_password;
}

void OtherNetworkWidget::fillNetworkInfo(const QString& name)
{
        ui->ssid->setText(name);
}

void OtherNetworkWidget::join()
{
        NetworkUtils::addWifiNetwork(ui->ssid->text(), ui->password->text());
        RootController::ref().dismissWidget();
}

#endif
