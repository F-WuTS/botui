/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c NMSettings -p NMSettings -N -i NetworkManagerConnection.h nm-settings.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef NMSETTINGS_H_1353454821
#define NMSETTINGS_H_1353454821

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "NetworkManagerConnection.h"

/*
 * Proxy class for interface org.freedesktop.NetworkManager.Settings
 */
class NMSettings: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.NetworkManager.Settings"; }

public:
    NMSettings(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~NMSettings();

    Q_PROPERTY(bool CanModify READ canModify)
    inline bool canModify() const
    { return qvariant_cast< bool >(property("CanModify")); }

    Q_PROPERTY(QString Hostname READ hostname)
    inline QString hostname() const
    { return qvariant_cast< QString >(property("Hostname")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QDBusObjectPath> AddConnection(Connection connection)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(connection);
        return asyncCallWithArgumentList(QLatin1String("AddConnection"), argumentList);
    }

    inline QDBusPendingReply<QDBusObjectPath> GetConnectionByUuid(const QString &uuid)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(uuid);
        return asyncCallWithArgumentList(QLatin1String("GetConnectionByUuid"), argumentList);
    }

    inline QDBusPendingReply<QList<QDBusObjectPath> > ListConnections()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("ListConnections"), argumentList);
    }

    inline QDBusPendingReply<> SaveHostname(const QString &hostname)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(hostname);
        return asyncCallWithArgumentList(QLatin1String("SaveHostname"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void NewConnection(const QDBusObjectPath &connection);
    void PropertiesChanged(const QVariantMap &properties);
};

#endif
