#include "AppController.h"

#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QIcon>
#include <QMenu>
#include <QTimer>

using namespace Qt::Literals::StringLiterals;

AppController::AppController(bool startMinimized, QObject *parent)
    : QObject(parent), m_startMinimized(startMinimized)
{
    QSettings settings;
    m_minimizeToTray = settings.value(QStringLiteral("minimizeToTray"), true).toBool();
    m_autostartEnabled = settings.value(QStringLiteral("autostartEnabled"), false).toBool();
    createTrayIcon();
    updateAutostartRegistry();
}

AppController::~AppController()
{
    if (m_trayIcon)
        m_trayIcon->hide();
}

bool AppController::minimizeToTray() const
{
    return m_minimizeToTray;
}

void AppController::setMinimizeToTray(bool enabled)
{
    if (m_minimizeToTray == enabled)
        return;
    m_minimizeToTray = enabled;
    QSettings().setValue(QStringLiteral("minimizeToTray"), enabled);
    emit minimizeToTrayChanged();
}

bool AppController::autostartEnabled() const
{
    return m_autostartEnabled;
}

void AppController::setAutostartEnabled(bool enabled)
{
    if (m_autostartEnabled == enabled)
        return;
    m_autostartEnabled = enabled;
    QSettings().setValue(QStringLiteral("autostartEnabled"), enabled);
    updateAutostartRegistry();
    emit autostartEnabledChanged();
}

bool AppController::trayAvailable() const
{
    return QSystemTrayIcon::isSystemTrayAvailable();
}

bool AppController::startMinimized() const
{
    return m_startMinimized;
}

bool AppController::quitting() const
{
    return m_quitting;
}

QString AppController::runKeyPath() const
{
    return QStringLiteral("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run");
}

QString AppController::autostartCommand() const
{
    const QString exe = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    return QStringLiteral("\"") + exe + QStringLiteral("\" --minimized");
}

void AppController::updateAutostartRegistry()
{
#ifdef Q_OS_WIN
    QSettings runKey(runKeyPath(), QSettings::NativeFormat);
    const QString valueName = QCoreApplication::applicationName();
    if (m_autostartEnabled) {
        runKey.setValue(valueName, autostartCommand());
    } else {
        runKey.remove(valueName);
    }
    runKey.sync();
#endif
}

void AppController::createTrayIcon()
{
    if (!QSystemTrayIcon::isSystemTrayAvailable())
        return;

    m_trayMenu = new QMenu();
    m_restoreAction = m_trayMenu->addAction(tr("Show Smart Control"));
    m_trayMenu->addSeparator();
    m_quitAction = m_trayMenu->addAction(tr("Quit"));

    m_trayIcon = new QSystemTrayIcon(QIcon(QStringLiteral(":/appicon.png")), this);
    m_trayIcon->setToolTip(tr("Smart Control Desktop"));
    m_trayIcon->setContextMenu(m_trayMenu);
    m_trayIcon->show();

    connect(m_restoreAction, &QAction::triggered, this, &AppController::showWindowFromQml);
    connect(m_quitAction, &QAction::triggered, this, &AppController::quitApplication);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick)
            showWindowFromQml();
    });
}

void AppController::showTrayMessageOnce()
{
    if (m_trayMessageShown || !m_trayIcon)
        return;
    m_trayMessageShown = true;
    m_trayIcon->showMessage(tr("Smart Control Desktop"),
                            tr("The app is still running in the system tray."),
                            QSystemTrayIcon::Information,
                            2500);
}

void AppController::showWindowFromQml()
{
    emit showWindowRequested();
}

void AppController::quitApplication()
{
    if (!m_quitting) {
        m_quitting = true;
        emit quittingChanged();
    }
    if (m_trayIcon)
        m_trayIcon->hide();
    QTimer::singleShot(0, qApp, &QCoreApplication::quit);
}
