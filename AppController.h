#pragma once

#include <QObject>
#include <QPointer>
#include <QSystemTrayIcon>
#include <QSettings>

class QAction;
class QMenu;

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool minimizeToTray READ minimizeToTray WRITE setMinimizeToTray NOTIFY minimizeToTrayChanged)
    Q_PROPERTY(bool autostartEnabled READ autostartEnabled WRITE setAutostartEnabled NOTIFY autostartEnabledChanged)
    Q_PROPERTY(bool trayAvailable READ trayAvailable CONSTANT)
    Q_PROPERTY(bool startMinimized READ startMinimized CONSTANT)
    Q_PROPERTY(bool quitting READ quitting NOTIFY quittingChanged)

public:
    explicit AppController(bool startMinimized, QObject *parent = nullptr);
    ~AppController() override;

    bool minimizeToTray() const;
    void setMinimizeToTray(bool enabled);

    bool autostartEnabled() const;
    void setAutostartEnabled(bool enabled);

    bool trayAvailable() const;
    bool startMinimized() const;
    bool quitting() const;

    Q_INVOKABLE void showTrayMessageOnce();
    Q_INVOKABLE void showWindowFromQml();
    Q_INVOKABLE void quitApplication();

signals:
    void minimizeToTrayChanged();
    void autostartEnabledChanged();
    void quittingChanged();
    void showWindowRequested();

private:
    QString autostartCommand() const;
    QString runKeyPath() const;
    void updateAutostartRegistry();
    void createTrayIcon();

    bool m_startMinimized = false;
    bool m_minimizeToTray = true;
    bool m_autostartEnabled = false;
    bool m_quitting = false;
    bool m_trayMessageShown = false;
    QSystemTrayIcon *m_trayIcon = nullptr;
    QMenu *m_trayMenu = nullptr;
    QAction *m_restoreAction = nullptr;
    QAction *m_quitAction = nullptr;
};
