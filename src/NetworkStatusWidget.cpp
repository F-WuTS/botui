#include "Options.h"

#ifdef NETWORK_ENABLED

#include "NetworkStatusWidget.h"

#include "NetworkManager.h"

#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QDebug>

#ifdef WALLABY
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <fstream>
#endif

void setWiFiStatusLED(bool on)
{
#ifdef WALLABY
        std::fstream fs;
        fs.open("/sys/class/leds/botball:D11:blue/brightness", std::fstream::out);

        if (on) {
                fs << "1";
        } else {
                fs << "0";
        }

        fs.close();
#endif
}

NetworkStatusWidget::NetworkStatusWidget(QWidget* parent)
        : QWidget(parent)
{
        constrain();
        connect(&NetworkManager::ref(),
                SIGNAL(stateChanged(NetworkManager::State, NetworkManager::State)),
                SLOT(networkStateChanged()));
        QTimer* updateTimer = new QTimer(this);
        connect(updateTimer, SIGNAL(timeout()), SLOT(update()));
        updateTimer->start(10000);
}

void NetworkStatusWidget::paintEvent(QPaintEvent* event)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        const int w = width();
        const int h = height();
        const int ellipseSize = w / 6;
        const int startAngle = 30 * 16;
        const int spanAngle = 120 * 16;

        static const QColor green = QColor(50, 150, 50);
        static const QColor red = QColor(250, 100, 100);
// static const QColor orange = QColor(250, 127, 0);

        const bool off = NetworkManager::ref().isOn();
        QColor color = off ? red : green;
        setWiFiStatusLED(!off);

        painter.setPen(QPen(color, w / 10));
        painter.setBrush(color);

        if (off) {
                const int min = w > h ? h : w;
                const float minOff = min / 3.0;
                painter.drawLine(w / 2.0 - minOff, h / 2.0 - minOff,
                                 w / 2.0 + minOff, h / 2.0 + minOff);
                painter.drawLine(w / 2.0 - minOff, h / 2.0 + minOff,
                                 w / 2.0 + minOff, h / 2.0 - minOff);
                return;
        }

#ifdef WALLABY
        const float percentage = 100.0f;
#else
        const float percentage = NetworkManager::ref().active().strength() / 100.0;
#endif

        QRectF rectangle(0, h / 5.0, w, h);
        if (percentage > 0.66) {
                painter.drawArc(rectangle, startAngle, spanAngle);
        }
        rectangle = QRectF(w / 5.0, 2.0 * h / 5.0, 3.0 * w / 5.0, h / 1.5);
        if (percentage > 0.33) {
                painter.drawArc(rectangle, startAngle, spanAngle);
        }
        painter.setPen(Qt::NoPen);

        painter.drawEllipse(w / 2.0 - ellipseSize / 2.0, 3.5 * h / 5.0 - ellipseSize / 2.0,
                            ellipseSize, ellipseSize);
}

void NetworkStatusWidget::networkStateChanged()
{
        update();
}

void NetworkStatusWidget::constrain()
{
        setMinimumSize(24, 20);
        setMaximumSize(24, 20);
}

#endif
