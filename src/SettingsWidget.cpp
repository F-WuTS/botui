#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"
#include "MenuBar.h"
#include "RootController.h"
#include "StatusBar.h"
#include "Device.h"
#include "Options.h"

#include "NetworkSettingsWidget.h"
#include "ChannelConfigurationsWidget.h"
#include "GuiSettingsWidget.h"
#include "LanguageWidget.h"
#include "BatterySettingsWidget.h"
#include "CameraSettingsWidget.h"

#include <QProcess>

SettingsWidget::SettingsWidget(Device* device, QWidget* parent)
        : StandardWidget(device, parent)
        , ui(new Ui::SettingsWidget)
{
        ui->setupUi(this);
        performStandardSetup(tr("Settings"));

        connect(ui->channels, SIGNAL(clicked()), SLOT(channels()));
        connect(ui->gui, SIGNAL(clicked()), SLOT(gui()));
        connect(ui->battery, SIGNAL(clicked()), SLOT(battery()));
        connect(ui->cameraView, SIGNAL(clicked()), SLOT(cameraView()));
        connect(ui->language, SIGNAL(clicked()), SLOT(language()));
        connect(ui->network, SIGNAL(clicked()), SLOT(network()));
        connect(ui->calibration, SIGNAL(clicked()), SLOT(calibrate()));
}

SettingsWidget::~SettingsWidget()
{
        delete ui;
}

void SettingsWidget::channels()
{
        RootController::ref().presentWidget(new ChannelConfigurationsWidget(device()));
}

void SettingsWidget::gui()
{
        RootController::ref().presentWidget(new GuiSettingsWidget(device()));
}

void SettingsWidget::language()
{
        RootController::ref().presentWidget(new LanguageWidget(device()));
}

void SettingsWidget::battery()
{
        RootController::ref().presentWidget(new BatterySettingsWidget(device()));
}

void SettingsWidget::cameraView()
{
        RootController::ref().presentWidget(new CameraSettingsWidget(device()));
}

void SettingsWidget::network()
{
        RootController::ref().presentWidget(new NetworkSettingsWidget(device()));
}

void SettingsWidget::calibrate()
{
        QProcess process;

        process.start("xinput_calibrator");
        process.waitForFinished();
}
