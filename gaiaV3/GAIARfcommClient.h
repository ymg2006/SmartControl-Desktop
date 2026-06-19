#ifndef QBT_GAIARFCOMMCLIENT_H
#define QBT_GAIARFCOMMCLIENT_H

#include <QObject>
#include "gaiaV3_export.h"
#include <QtQmlIntegration>
#include <QJSEngine>
#include <QQmlApplicationEngine>
#include <QQueue>

#include "GAIAPropertyBase.h"
#include "GAIAPropertyManager.h"
#include "BluetoothSocketWrapper.h"

class GAIA_V3_EXPORT GAIARfcommClient : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(bool isConnected READ getIsConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(GAIAPropertyManagerBase* manager READ getManager NOTIFY managerChanged)
    Q_PROPERTY(QString deviceName READ getDeviceName WRITE setDeviceName NOTIFY deviceNameChanged)
    Q_PROPERTY(QString deviceAddress READ getDeviceAddress NOTIFY deviceAddressChanged)
    Q_PROPERTY(QString lastError READ getLastError NOTIFY lastErrorChanged)

public:
    static GAIARfcommClient &getInstance();
    static GAIARfcommClient *create(QQmlEngine *, QJSEngine *);

    Q_INVOKABLE void openKnownWindowsDevice(const QString &name, const QString &address);
    Q_INVOKABLE void disconnectDevice();

protected:
    GAIARfcommClient();
    ~GAIARfcommClient() override = default;

    QList<QByteArray> packetSplitter(const QByteArray &data) const;

private:
    GAIARfcommClient(const GAIARfcommClient &) = delete;
    GAIARfcommClient &operator=(const GAIARfcommClient &) = delete;

    BluetoothSocketWrapper *socket;
    bool m_isConnected;
    bool m_manualDisconnect;
    bool m_transportReady;
    QString m_deviceAddress;
    QString m_deviceName;
    QString m_lastError;
    GAIAPropertyManagerBase *propertyManager;
    QQueue<QByteArray> pendingWrites;

    void flushPendingWrites();

private slots:
    void socketConnected();
    void socketDisconnected();
    void socketReadyRead();
    void socketConnectionFailed(const QString &message);
    void propertyManagerAdded(const QByteArray &vendorCommand);

public slots:
    bool getIsConnected() const;
    void sendData(const QByteArray &data);
    GAIAPropertyManagerBase *getManager();
    QString getDeviceName() const;
    QString getDeviceAddress() const;
    QString getLastError() const;
    void setDeviceName(const QString &name);

signals:
    void isConnectedChanged();
    void managerChanged();
    void deviceNameChanged();
    void deviceAddressChanged();
    void lastErrorChanged();
    void connectionFailed(const QString &message);
};

#endif // QBT_GAIARFCOMMCLIENT_H
