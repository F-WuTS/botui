#ifndef _NETWORKUTILS_H_
#define _NETWORKUTILS_H_

#include "Options.h"

#ifdef NETWORK_ENABLED

#include <QList>
#include <QString>

namespace NetworkUtils {
        bool isWifiOn();
        void turnOnWifi();
        void turnOffWifi();
        QList<QString> performWifiScan();
        void connectToWifi(const QString& name);

        QString getCurrentNetwork();
        void addWifiNetwork(const QString& name, const QString& password);
        QList<QString> listSavedNetworks();
}

#endif

#endif
