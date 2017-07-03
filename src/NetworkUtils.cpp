#include "Options.h"

#ifdef NETWORK_ENABLED

#include <QProcess>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "NetworkUtils.h"

#define WIFI_INTERFACE "wlan0"


static QString executeCommand(const QString& cmd)
{
        QProcess process;

        process.start(cmd);
        process.waitForFinished();

        return QString(process.readAllStandardOutput());
}

bool NetworkUtils::isWifiOn()
{
        struct ifreq ifr;

        memset(&ifr, 0, sizeof(ifr));
        strcpy(ifr.ifr_name, WIFI_INTERFACE);

        int dummy_fd = socket(AF_INET, SOCK_DGRAM, 0);

        if (ioctl(dummy_fd, SIOCGIFFLAGS, &ifr) != -1)
                return (ifr.ifr_flags & (IFF_UP | IFF_RUNNING)) == (IFF_UP | IFF_RUNNING);

        return false;
}

void NetworkUtils::turnOnWifi()
{
        executeCommand("wpa_cli reconnect");
}

void NetworkUtils::turnOffWifi()
{
        executeCommand("wpa_cli disconnect");
}

QList<QString> NetworkUtils::performWifiScan()
{
        executeCommand("wpa_cli scan");
        sleep(5);

        QString ret = executeCommand("wpa_cli scan_results");

        QList<QString> networks;
        for (const QString& line: ret.split('\n').filter("\t"))
                networks.push_back(line.section('\t', 4, 4));

        return networks;
}

void NetworkUtils::connectToWifi(const QString& name)
{
        QList<QString> networks = NetworkUtils::listSavedNetworks();

        for (int i = 0; i < networks.count(); i++) {
                if (networks[i] == name) {
                        QString index = QString(std::to_string(i).c_str());

                        executeCommand("wpa_cli enable_network " + index);
                        executeCommand("wpa_cli select_network " + index);
                }
        }
}

QString NetworkUtils::getCurrentNetwork()
{
        QString ret = executeCommand("wpa_cli status");

        return ret.contains("ssid") ? ret.split('\n').filter("ssid").first().section('=', 1, 1) : "Not connected";
}

void NetworkUtils::addWifiNetwork(const QString& name, const QString& password)
{
        char* buffer = new char[256];
        snprintf(buffer, 256,
                "\nnetwork={\n"
                "\tssid=\"%s\"\n"
                "\tpsk=\"%s\"\n"
                "}\n", name.toUtf8().data(), password.toUtf8().data()
        );

        std::ofstream file("/etc/wpa_supplicant/wpa_supplicant.conf", std::ios_base::app);
        file << buffer;

        delete buffer;
}

QList<QString> NetworkUtils::listSavedNetworks()
{
        std::ifstream file("/etc/wpa_supplicant/wpa_supplicant.conf");
        std::stringstream buffer;
        buffer << file.rdbuf();
        QString str = QString(buffer.str().c_str());

        QList<QString> networks;
        for (const QString& line: str.split('\n').filter("ssid"))
                networks.push_back(line.section('=', 1, 1).remove('"'));

        return networks;
}

#endif
