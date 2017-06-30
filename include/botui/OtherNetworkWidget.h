#include "Options.h"

#ifdef NETWORK_ENABLED

#ifndef _OTHERNETWORKWIDGET_H_
#define _OTHERNETWORKWIDGET_H_

#include "StandardWidget.h"
#include "Network.h"

namespace Ui {
class OtherNetworkWidget;
}

class KeyboardDialog;

class OtherNetworkWidget : public StandardWidget {
        Q_OBJECT
public:
        OtherNetworkWidget(Device* device, QWidget* parent = 0);
        ~OtherNetworkWidget();

        void fillNetworkInfo(const QString& name);

private slots:
        void join();

private:
        Ui::OtherNetworkWidget* ui;

        KeyboardDialog* m_ssid;
        KeyboardDialog* m_password;
};

#endif

#endif
