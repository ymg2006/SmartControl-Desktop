#ifndef SENNHEISERDESKTOPCLIENT_BLUETOOTHHANDLER_H
#define SENNHEISERDESKTOPCLIENT_BLUETOOTHHANDLER_H

#include <QObject>
#include <QtQmlIntegration>

class BluetoothHandler : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool isSearching READ getIsSearching NOTIFY isSearchingChanged)
    Q_PROPERTY(QString deviceAddress READ getDeviceAddress WRITE setDeviceAddress NOTIFY deviceAddressChanged)

public:
    explicit BluetoothHandler(QObject *parent = nullptr);

public slots:
    void refreshKnownDevices();
    bool getIsSearching() const;
    QString getDeviceAddress() const;
    void setDeviceAddress(const QString &address);

private:
    void addKnownWindowsDevices();
    bool m_isSearching;
    QString m_deviceAddress;

signals:
    void isSearchingChanged();
    void deviceAddressChanged();
    void refreshStarted();
    void refreshFinished();
    void newDeviceAdded(const QString &name, const QString &address, const QString &uuid, bool isConnected, bool isRemembered);
};

#endif // SENNHEISERDESKTOPCLIENT_BLUETOOTHHANDLER_H
