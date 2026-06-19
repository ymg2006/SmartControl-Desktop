#include "GAIARfcommClient.h"
#include "GAIAPropertyClasses.h"

#include <QDebug>
#include <QTimer>

GAIARfcommClient &GAIARfcommClient::getInstance()
{
    static GAIARfcommClient instance;
    return instance;
}

GAIARfcommClient *GAIARfcommClient::create(QQmlEngine *, QJSEngine *)
{
    auto *instance = &GAIARfcommClient::getInstance();
    QJSEngine::setObjectOwnership(instance, QJSEngine::CppOwnership);
    return instance;
}

GAIARfcommClient::GAIARfcommClient()
    : QObject(nullptr)
    , socket(new BluetoothSocketWrapper(this))
    , m_isConnected(false)
    , m_manualDisconnect(false)
    , m_transportReady(false)
    , m_deviceAddress("")
    , m_deviceName("")
    , m_lastError("")
    , propertyManager(new GAIAPropertyManager(this))
{
    connect(socket, &BluetoothSocketWrapper::connected, this, &GAIARfcommClient::socketConnected);
    connect(socket, &BluetoothSocketWrapper::readyRead, this, &GAIARfcommClient::socketReadyRead);
    connect(socket, &BluetoothSocketWrapper::disconnected, this, &GAIARfcommClient::socketDisconnected);
    connect(socket, &BluetoothSocketWrapper::connectionFailed, this, &GAIARfcommClient::socketConnectionFailed);
    connect(propertyManager, &GAIAPropertyManagerBase::propertyAdded, this, &GAIARfcommClient::propertyManagerAdded);
}

void GAIARfcommClient::openKnownWindowsDevice(const QString &name, const QString &address)
{
    const QString normalizedAddress = address.trimmed().toUpper();
    if (normalizedAddress.isEmpty()) {
        qWarning() << "Cannot open Windows Bluetooth device without an address";
        return;
    }

    const bool sameDevice = normalizedAddress == m_deviceAddress;
    m_deviceName = name.trimmed().isEmpty() ? QStringLiteral("Sennheiser headset") : name.trimmed();
    m_deviceAddress = normalizedAddress;
    m_manualDisconnect = false;
    m_lastError.clear();
    Q_EMIT lastErrorChanged();

    Q_EMIT deviceNameChanged();
    if (!sameDevice) {
        Q_EMIT deviceAddressChanged();
    }

    if (m_isConnected && socket->isOpen() && sameDevice) {
        Q_EMIT isConnectedChanged();
        return;
    }

    qDebug() << "Opening real Windows RFCOMM control channel" << m_deviceName << m_deviceAddress;
    socket->connectToService(m_deviceAddress);
}

void GAIARfcommClient::disconnectDevice()
{
    m_manualDisconnect = true;
    socket->close();
}

void GAIARfcommClient::socketConnected()
{
    qDebug() << "Windows RFCOMM control channel connected" << m_deviceName << m_deviceAddress;

    // The Windows worker has already opened and GAIA-probed the socket before
    // this queued signal reaches the UI thread. Mark transportReady before
    // emitting isConnectedChanged(), because that signal creates DevicePage and
    // its cards immediately send their first GAIA reads.
    m_transportReady = true;

    if (!m_isConnected) {
        m_isConnected = true;
        Q_EMIT isConnectedChanged();
    }

    flushPendingWrites();
    QTimer::singleShot(0, this, &GAIARfcommClient::flushPendingWrites);
    QTimer::singleShot(25, this, &GAIARfcommClient::flushPendingWrites);
    QTimer::singleShot(100, this, &GAIARfcommClient::flushPendingWrites);
}

void GAIARfcommClient::socketDisconnected()
{
    qDebug() << "Windows RFCOMM control channel disconnected" << m_deviceName << m_deviceAddress;
    m_transportReady = false;
    if (m_isConnected) {
        m_isConnected = false;
        Q_EMIT isConnectedChanged();
    }
}

void GAIARfcommClient::socketConnectionFailed(const QString &message)
{
    m_lastError = message;
    qWarning() << "Windows RFCOMM control channel failed" << m_deviceName << m_deviceAddress << message;
    Q_EMIT lastErrorChanged();
    Q_EMIT connectionFailed(message);
}

void GAIARfcommClient::flushPendingWrites()
{
    if (!m_transportReady && !socket->isOpen()) {
        return;
    }

    if (!m_isConnected) {
        m_isConnected = true;
        Q_EMIT isConnectedChanged();
    }

    if (!pendingWrites.isEmpty()) {
        qDebug() << "Flushing queued GAIA writes" << pendingWrites.size();
    }

    while (!pendingWrites.isEmpty() && (m_transportReady || socket->isOpen())) {
        const QByteArray data = pendingWrites.dequeue();
        qDebug() << "[SOCKET] >>" << data;
        const qint64 written = socket->write(data);
        if (written < 0) {
            qWarning() << "GAIA write failed after Windows RFCOMM channel opened; re-queueing packet";
            pendingWrites.prepend(data);
            QTimer::singleShot(100, this, &GAIARfcommClient::flushPendingWrites);
            break;
        }
    }
}

QList<QByteArray> GAIARfcommClient::packetSplitter(const QByteArray &data) const
{
    QList<QByteArray> packets;
    QByteArray remaining = data;

    while (remaining.length() >= 8) {
        const int payloadSize = ((static_cast<unsigned char>(remaining.at(2)) << 8) & 0xff00)
                              + (static_cast<unsigned char>(remaining.at(3)) & 0x00ff);
        const int packetSize = payloadSize + 8;
        if (remaining.length() < packetSize) {
            break;
        }

        packets << remaining.left(packetSize);
        remaining = remaining.mid(packetSize);
    }

    return packets;
}

void GAIARfcommClient::socketReadyRead()
{
    const QByteArray dataAll = socket->readAll();
    if (dataAll.length() < 6) {
        qDebug() << "[SOCKET] <<" << dataAll;
        return;
    }

    const auto packets = packetSplitter(dataAll);
    for (const auto &data : packets) {
        const QByteArray vendorCommand = data.mid(4, 4);
        auto *property = propertyManager->getProperty(vendorCommand);

        if (property != nullptr) {
            qDebug() << "[SOCKET] <<" << data << "->" << property;
            property->parse(data);
        } else {
            qDebug() << "[SOCKET] <<" << data << "-> {Unknown}";
        }
    }
}

bool GAIARfcommClient::getIsConnected() const
{
    return m_isConnected;
}

void GAIARfcommClient::sendData(const QByteArray &data)
{
    if (data.isEmpty()) {
        return;
    }

    // The native worker validates the Momentum 4 control socket before it emits
    // connected(). DevicePage is created from that signal and immediately sends
    // property reads, so use this client's transportReady flag as the primary
    // truth and the wrapper open state as a fallback.
    if (!m_transportReady && !socket->isOpen()) {
        pendingWrites.enqueue(data);
        qDebug() << "Queued GAIA write until Windows RFCOMM transport is ready" << pendingWrites.size();
        QTimer::singleShot(50, this, &GAIARfcommClient::flushPendingWrites);
        QTimer::singleShot(200, this, &GAIARfcommClient::flushPendingWrites);
        return;
    }

    if (!m_isConnected) {
        m_isConnected = true;
        Q_EMIT isConnectedChanged();
    }

    qDebug() << "[SOCKET] >>" << data;
    const qint64 written = socket->write(data);
    if (written < 0) {
        pendingWrites.enqueue(data);
        qWarning() << "GAIA write failed; queued packet for retry" << pendingWrites.size();
        QTimer::singleShot(100, this, &GAIARfcommClient::flushPendingWrites);
    }
}

GAIAPropertyManagerBase *GAIARfcommClient::getManager()
{
    return propertyManager;
}

void GAIARfcommClient::propertyManagerAdded(const QByteArray &vendorCommand)
{
    auto *property = propertyManager->getProperty(vendorCommand, false);
    connect(property, &GAIAPropertyBase::sendData, this, &GAIARfcommClient::sendData);
}

QString GAIARfcommClient::getDeviceName() const
{
    return m_deviceName;
}

void GAIARfcommClient::setDeviceName(const QString &name)
{
    if (m_deviceName == name) {
        return;
    }

    m_deviceName = name;
    Q_EMIT deviceNameChanged();
}

QString GAIARfcommClient::getDeviceAddress() const
{
    return m_deviceAddress;
}

QString GAIARfcommClient::getLastError() const
{
    return m_lastError;
}
