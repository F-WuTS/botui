#ifdef QT_DBUS_LIB

#ifndef _CONNECTWIDGET_H_
#define _CONNECTWIDGET_H_

#include "StandardWidget.h"

#include <QItemSelection>

namespace Ui {
class ConnectWidget;
}

class NetworkItemModel;

class ConnectWidget : public StandardWidget {
        Q_OBJECT
public:
        ConnectWidget(Device* device, QWidget* parent = 0);
        ~ConnectWidget();

public slots:
        void connect();
        void other();
        void refresh();

private:
        Ui::ConnectWidget* ui;
};

#endif

#endif
