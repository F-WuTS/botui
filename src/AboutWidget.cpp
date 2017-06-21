#include "AboutWidget.h"
#include "ui_AboutWidget.h"
#include "Device.h"
#include "NetworkManager.h"

#include <QDebug>

AboutWidget::AboutWidget(Device* device, QWidget* parent)
        : StandardWidget(device, parent)
        , ui(new Ui::AboutWidget)
{
        ui->setupUi(this);
        ui->deviceName->setText(device->name() + " v" + device->version());

        const NetworkManager& nm = NetworkManager::ref();
        const QString ip = nm.ipAddress();
        ui->ipAddress->setText(ip.isEmpty() ? tr("No IP") : ip);

        const QString name = nm.hostname();
        ui->hostname->setText(name.isEmpty() ? "<unknown>" : name);

        performStandardSetup(tr("About"));
}

AboutWidget::~AboutWidget()
{
        delete ui;
}
