#include "Options.h"

#ifdef NETWORK_ENABLED

#include "ManageNetworksWidget.h"

#include "ui_ManageNetworks.h"

#include "NetworkManager.h"
#include "NetworkUtils.h"

ManageNetworksWidget::ManageNetworksWidget(Device* device, QWidget* parent)
        : StandardWidget(device, parent)
        , ui(new Ui::ManageNetworks)
        , m_device(device)
{
        ui->setupUi(this);
        performStandardSetup(tr("Manage Networks"));

        for (const QString& network: NetworkUtils::listSavedNetworks())
                ui->networks->addItem(network);

        connect(ui->forget, SIGNAL(clicked()), SLOT(forget()));
}

ManageNetworksWidget::~ManageNetworksWidget()
{
        delete ui;
}

void ManageNetworksWidget::forget()
{
        if (ui->networks->currentItem()) {
                QString network = ui->networks->currentItem()->text();
                delete ui->networks->takeItem(ui->networks->row(ui->networks->currentItem()));
        }
}

#endif
