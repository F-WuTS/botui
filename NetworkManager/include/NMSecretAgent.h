/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c NMSecretAgent -p NMSecretAgent -N -i NetworkManagerConnection.h nm-secret-agent.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef NMSECRETAGENT_H_1353454821
#define NMSECRETAGENT_H_1353454821

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
 * Proxy class for interface org.freedesktop.NetworkManager.SecretAgent
 */
class NMSecretAgent: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.NetworkManager.SecretAgent"; }

public:
    NMSecretAgent(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~NMSecretAgent();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> CancelGetSecrets(const QDBusObjectPath &connection_path, const QString &setting_name)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(connection_path) << qVariantFromValue(setting_name);
        return asyncCallWithArgumentList(QLatin1String("CancelGetSecrets"), argumentList);
    }

    inline QDBusPendingReply<> DeleteSecrets(const QVariantMap &connection, const QDBusObjectPath &connection_path)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(connection) << qVariantFromValue(connection_path);
        return asyncCallWithArgumentList(QLatin1String("DeleteSecrets"), argumentList);
    }

    inline QDBusPendingReply<QVariantMap> GetSecrets(const QVariantMap &connection, const QDBusObjectPath &connection_path, const QString &setting_name, const QStringList &hints, uint flags)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(connection) << qVariantFromValue(connection_path) << qVariantFromValue(setting_name) << qVariantFromValue(hints) << qVariantFromValue(flags);
        return asyncCallWithArgumentList(QLatin1String("GetSecrets"), argumentList);
    }

    inline QDBusPendingReply<> SaveSecrets(const QVariantMap &connection, const QDBusObjectPath &connection_path)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(connection) << qVariantFromValue(connection_path);
        return asyncCallWithArgumentList(QLatin1String("SaveSecrets"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

#endif
