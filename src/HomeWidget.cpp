#include "HomeWidget.h"

#include <QApplication>
#include <QMessageBox>
#include <QProcess>

#include "ui_HomeWidget.h"
#include "MenuBar.h"
#include "StatusBar.h"
#include "RootController.h"
#include "SettingsWidget.h"
#include "AboutWidget.h"
#include "MotorsSensorsWidget.h"
#include "ProgramsWidget.h"
#include "Device.h"
#include "ProgramSelectionWidget.h"
#include "Program.h"
#include "UiStandards.h"

HomeWidget::HomeWidget(Device* device, QWidget* parent)
        : StandardWidget(device, parent)
        , ui(new Ui::HomeWidget)
{
        ui->setupUi(this);
        performStandardSetup(UiStandards::homeString());

        connect(ui->programs, SIGNAL(clicked()), SLOT(programs()));
        connect(ui->motorsSensors, SIGNAL(clicked()), SLOT(motorsSensors()));
        connect(ui->settings, SIGNAL(clicked()), SLOT(settings()));

        QAction* about = menuBar()->addAction(tr("About"));
        QAction* shutDown = menuBar()->addAction(tr("Shut Down"));
        menuBar()->adjustSize();
        connect(about, SIGNAL(triggered()), SLOT(about()));
        connect(shutDown, SIGNAL(triggered()), SLOT(shutDown()));
}

HomeWidget::~HomeWidget()
{
        delete ui;
}

void HomeWidget::programs()
{
        RootController::ref().presentWidget(Program::instance()->isRunning()
                                                    ? (QWidget*)new ProgramSelectionWidget(device())
                                                    : (QWidget*)new ProgramsWidget(device()));
}

void HomeWidget::motorsSensors()
{
        RootController::ref().presentWidget(new MotorsSensorsWidget(device()));
}

void HomeWidget::settings()
{
        RootController::ref().presentWidget(new SettingsWidget(device()));
}

void HomeWidget::about()
{
        RootController::ref().presentWidget(new AboutWidget(device()));
}

void HomeWidget::shutDown()
{
#ifdef WALLABY
        if (QMessageBox::question(this, "Shut Down?", "After system halted, slide power switch off or disconnect battery.\n\nContinue?", QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
                return;

        const int ret = QProcess::execute("poweroff");
        if (ret < 0)
                QMessageBox::information(this, "Failed", "Shut down failed.");
#else
        QMessageBox::information(this, "Not Available", "Shut down is only available on the kovan.");
#endif
}
