/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c NMSettingsConnection -p NMSettingsConnection nm-settings-connection.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "NMSettingsConnection.h"

/*
 * Implementation of interface class NMSettingsConnection
 */

NMSettingsConnection::NMSettingsConnection(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

NMSettingsConnection::~NMSettingsConnection()
{
}
