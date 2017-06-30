#ifdef QT_DBUS_LIB

#include <QTimer>
#include "ConnectWidget.h"
#include "ui_ConnectWidget.h"
#include "MenuBar.h"
#include "RootController.h"
#include "StatusBar.h"
#include "NetworkManager.h"
#include "OtherNetworkWidget.h"
#include "Device.h"
#include "NetworkUtils.h"

ConnectWidget::ConnectWidget(Device* device, QWidget* parent)
        : StandardWidget(device, parent)
        , ui(new Ui::ConnectWidget)
{
        ui->setupUi(this);
        performStandardSetup(tr("Connect"));

        QObject::connect(ui->refresh, SIGNAL(clicked()), SLOT(refresh()));
        QObject::connect(ui->other, SIGNAL(clicked()), SLOT(other()));
        QObject::connect(ui->connect, SIGNAL(clicked()), SLOT(connect()));

        QTimer::singleShot(500, this, SLOT(refresh()));
}

ConnectWidget::~ConnectWidget()
{
        delete ui;
}

void ConnectWidget::connect()
{
        if (ui->networks->currentItem()) {
                QString network = ui->networks->currentItem()->text();

                if (!NetworkUtils::listSavedNetworks().contains(network)) {
                        OtherNetworkWidget* other = new OtherNetworkWidget(device());
                        other->fillNetworkInfo(network);
                        RootController::ref().presentWidget(other);
                }

                NetworkUtils::connectToWifi(network);
        }
}

void ConnectWidget::other()
{
        RootController::ref().presentWidget(new OtherNetworkWidget(device()));
}

void ConnectWidget::refresh()
{
        ui->networks->clear();

        for (const QString& network: NetworkUtils::performWifiScan())
                ui->networks->addItem(network);
}

#endif
