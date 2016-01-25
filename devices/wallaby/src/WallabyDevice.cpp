#include "WallabyDevice.h"

#include "WallabyBatteryProvider.h"
#include "WallabySettingsProvider.h"
#include "KissCompileProvider.h"

#include <wallaby/wallaby.hpp>

#ifdef ENABLE_DBUS_SUPPORT
#include <QDBusConnection>
#endif

#include <QDebug>

#ifdef Q_OS_MAC
#define NOT_A_WALLABY
#endif

Wallaby::Device::Device()
  : m_compileProvider(new KissCompileProvider(this)),
  m_batteryLevelProvider(new Wallaby::BatteryLevelProvider()),
  m_settingsProvider(new Wallaby::SettingsProvider())
{
  m_compileProvider->setBinariesPath("/wallaby/bin");
#ifndef NOT_A_WALLABY
  halt();
#endif
  set_auto_publish(0);
}

Wallaby::Device::~Device()
{
  delete m_compileProvider;
  delete m_batteryLevelProvider;
  delete m_settingsProvider;
}

QString Wallaby::Device::name() const
{
  return tr("Wallaby");
}

QString Wallaby::Device::version() const
{
  // TODO: get correct version
  return "2.2.1";
}

bool Wallaby::Device::isTouchscreen() const
{
#ifdef NOT_A_WALLABY
  return false;
#else
  return true;
#endif
}

CompileProvider *Wallaby::Device::compileProvider() const
{
  return m_compileProvider;
}

BatteryLevelProvider *Wallaby::Device::batteryLevelProvider() const
{
  return m_batteryLevelProvider;
}

SettingsProvider *Wallaby::Device::settingsProvider() const
{
  return m_settingsProvider;
}

ButtonProvider *Wallaby::Device::buttonProvider() const
{
  return 0;
}
