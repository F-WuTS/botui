#ifndef _NETWORKSETTINGSWIDGET_H_
#define _NETWORKSETTINGSWIDGET_H_

#include "Options.h"

#ifdef NETWORK_ENABLED

#include "StandardWidget.h"
#include "NetworkManager.h"

class QTimer;

namespace Ui {
class NetworkSettingsWidget;
}

class NetworkSettingsWidget : public StandardWidget {
        Q_OBJECT
public:
        NetworkSettingsWidget(Device* device, QWidget* parent = 0);
        ~NetworkSettingsWidget();

public slots:
        void connect();
        void manage();
        void updateInformation();

private slots:
        void stateChanged(const NetworkManager::State& newState, const NetworkManager::State& oldState);

        void enableWifi();
        void disableWifi();

private:
        Ui::NetworkSettingsWidget* ui;
        QTimer* enableCoolOffTimer;
};

#endif

#endif
