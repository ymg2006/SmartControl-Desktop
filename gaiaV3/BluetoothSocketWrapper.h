#ifndef SENNHEISERDESKTOPCLIENT_BLUETOOTHSOCKETWRAPPER_H
#define SENNHEISERDESKTOPCLIENT_BLUETOOTHSOCKETWRAPPER_H

#include <QObject>
#include "gaiaV3_export.h"
#include <QByteArray>
#include <QQueue>
#include <QString>
#include <QMutex>

#include <atomic>
#include <thread>

#ifdef _WIN32
#  include <winsock2.h>
#  include <ws2bth.h>
#  include <vector>
#endif

class GAIA_V3_EXPORT BluetoothSocketWrapper : public QObject {
    Q_OBJECT

public:
    explicit BluetoothSocketWrapper(QObject *parent = nullptr);
    ~BluetoothSocketWrapper() override;

    bool isOpen() const;
    void close();
    QByteArray readAll();
    void connectToService(const QString &address);
    qint64 write(const QByteArray &data);

private:
#ifdef _WIN32
    static bool ensureWinsockStarted();
    static bool parseBluetoothAddress(const QString &address, BTH_ADDR *outAddress);
    static GUID momentum4ControlServiceGuid();
    static GUID legacyGaiaServiceGuid();
    static GUID serialPortServiceGuid();
    static GUID rfcommProtocolGuid();
    static QString windowsSocketErrorText(int errorCode);
    static SOCKET createRfcommSocket();
    static bool connectWithPort(SOCKET socketHandle, BTH_ADDR bluetoothAddress, ULONG port);
    static bool connectWithGuid(SOCKET socketHandle, BTH_ADDR bluetoothAddress, const GUID &serviceGuid);
    static std::vector<ULONG> lookupRfcommChannels(BTH_ADDR bluetoothAddress, const GUID &serviceGuid, const QString &label);
    bool probeGaiaSocket(SOCKET socketHandle, const QString &label);
    bool connectToServiceByGuid(BTH_ADDR bluetoothAddress, const GUID &serviceGuid, const QString &label, SOCKET *connectedSocket);
    void flushWriteQueueLocked();
    void workerMain(QString address);
    void stopWorker(bool waitForThread);

    mutable QMutex socketMutex;
    SOCKET socketHandle;
    std::thread workerThread;
    std::atomic_bool stopRequested;
    std::atomic_bool openState;
#endif

    mutable QMutex queueMutex;
    QQueue<QByteArray> readQueue;
    QQueue<QByteArray> pendingWriteQueue;

signals:
    void connected();
    void disconnected();
    void readyRead();
    void connectionFailed(const QString &message);
};

#endif // SENNHEISERDESKTOPCLIENT_BLUETOOTHSOCKETWRAPPER_H
