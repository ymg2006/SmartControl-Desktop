#include "BluetoothSocketWrapper.h"

#include <QDebug>
#include <QMutexLocker>
#include <QMetaObject>
#include <QList>

#ifdef _WIN32
#  include <windows.h>
#  include <cstring>
#  include <vector>
#  include <chrono>
#endif

BluetoothSocketWrapper::BluetoothSocketWrapper(QObject *parent)
    : QObject(parent)
#ifdef _WIN32
    , socketHandle(INVALID_SOCKET)
    , stopRequested(false)
    , openState(false)
#endif
{
}

BluetoothSocketWrapper::~BluetoothSocketWrapper()
{
    close();
}

bool BluetoothSocketWrapper::isOpen() const
{
#ifdef _WIN32
    if (openState.load()) {
        return true;
    }

    QMutexLocker locker(&socketMutex);
    return socketHandle != INVALID_SOCKET;
#else
    return false;
#endif
}

void BluetoothSocketWrapper::close()
{
#ifdef _WIN32
    stopWorker(true);
#else
    Q_EMIT disconnected();
#endif
}

QByteArray BluetoothSocketWrapper::readAll()
{
    QMutexLocker locker(&queueMutex);
    QByteArray result;
    while (!readQueue.isEmpty()) {
        result.append(readQueue.dequeue());
    }
    return result;
}

void BluetoothSocketWrapper::connectToService(const QString &address)
{
#ifdef _WIN32
    stopWorker(true);
    stopRequested.store(false);
    workerThread = std::thread(&BluetoothSocketWrapper::workerMain, this, address.trimmed());
#else
    Q_UNUSED(address)
    qWarning() << "This build only supports Windows native Bluetooth RFCOMM.";
#endif
}

qint64 BluetoothSocketWrapper::write(const QByteArray &data)
{
#ifdef _WIN32
    QMutexLocker locker(&socketMutex);
    if (socketHandle == INVALID_SOCKET) {
        pendingWriteQueue.enqueue(data);
        qDebug() << "Queued RFCOMM write until native socket handle is ready" << pendingWriteQueue.size();
        return data.size();
    }

    const int sent = ::send(socketHandle, data.constData(), static_cast<int>(data.size()), 0);
    if (sent == SOCKET_ERROR) {
        const int error = WSAGetLastError();
        qWarning() << "RFCOMM send failed" << error << windowsSocketErrorText(error);
        pendingWriteQueue.enqueue(data);
        return -1;
    }

    return sent;
#else
    Q_UNUSED(data)
    return -1;
#endif
}

#ifdef _WIN32
bool BluetoothSocketWrapper::ensureWinsockStarted()
{
    static bool started = []() {
        WSADATA data;
        const int result = WSAStartup(MAKEWORD(2, 2), &data);
        if (result != 0) {
            qWarning() << "WSAStartup failed" << result;
            return false;
        }
        return true;
    }();

    return started;
}

bool BluetoothSocketWrapper::parseBluetoothAddress(const QString &address, BTH_ADDR *outAddress)
{
    if (outAddress == nullptr) {
        return false;
    }

    QString cleaned = address.trimmed();
    cleaned.remove(':');
    cleaned.remove('-');

    if (cleaned.size() != 12) {
        return false;
    }

    bool ok = false;
    const quint64 value = cleaned.toULongLong(&ok, 16);
    if (!ok) {
        return false;
    }

    *outAddress = static_cast<BTH_ADDR>(value);
    return true;
}

GUID BluetoothSocketWrapper::momentum4ControlServiceGuid()
{
    // Momentum 4 exposes the GAIA v3 control channel under this classic RFCOMM UUID.
    return GUID{0xa2129ff3, 0x081b, 0x4c45, {0x8a, 0xfe, 0x46, 0x9d, 0x9c, 0x48, 0x42, 0xec}};
}

GUID BluetoothSocketWrapper::legacyGaiaServiceGuid()
{
    // Older Sennheiser / Qualcomm GAIA UUID kept as a compatibility fallback.
    return GUID{0x0000fdce, 0x0000, 0x1000, {0x80, 0x00, 0x00, 0x80, 0x5f, 0x9b, 0x34, 0xfb}};
}

GUID BluetoothSocketWrapper::serialPortServiceGuid()
{
    return SerialPortServiceClass_UUID;
}

GUID BluetoothSocketWrapper::rfcommProtocolGuid()
{
    return GUID{0x00000003, 0x0000, 0x1000, {0x80, 0x00, 0x00, 0x80, 0x5f, 0x9b, 0x34, 0xfb}};
}

QString BluetoothSocketWrapper::windowsSocketErrorText(int errorCode)
{
    char *message = nullptr;
    const DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
    const DWORD length = FormatMessageA(flags, nullptr, static_cast<DWORD>(errorCode), 0, reinterpret_cast<char *>(&message), 0, nullptr);

    QString result;
    if (length > 0 && message != nullptr) {
        result = QString::fromLocal8Bit(message).trimmed();
        LocalFree(message);
    }

    return result;
}

SOCKET BluetoothSocketWrapper::createRfcommSocket()
{
    return ::socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
}

void BluetoothSocketWrapper::flushWriteQueueLocked()
{
    while (!pendingWriteQueue.isEmpty() && socketHandle != INVALID_SOCKET && openState.load()) {
        const QByteArray data = pendingWriteQueue.dequeue();
        const int sent = ::send(socketHandle, data.constData(), static_cast<int>(data.size()), 0);
        if (sent == SOCKET_ERROR) {
            const int error = WSAGetLastError();
            qWarning() << "Queued RFCOMM send failed" << error << windowsSocketErrorText(error);
            pendingWriteQueue.prepend(data);
            break;
        }
    }
}

bool BluetoothSocketWrapper::connectWithPort(SOCKET socketHandleToConnect, BTH_ADDR bluetoothAddress, ULONG port)
{
    SOCKADDR_BTH address;
    std::memset(&address, 0, sizeof(address));
    address.addressFamily = AF_BTH;
    address.btAddr = bluetoothAddress;
    address.port = port;

    const int result = ::connect(socketHandleToConnect, reinterpret_cast<SOCKADDR *>(&address), sizeof(address));
    return result != SOCKET_ERROR;
}

bool BluetoothSocketWrapper::connectWithGuid(SOCKET socketHandleToConnect, BTH_ADDR bluetoothAddress, const GUID &serviceGuid)
{
    SOCKADDR_BTH address;
    std::memset(&address, 0, sizeof(address));
    address.addressFamily = AF_BTH;
    address.btAddr = bluetoothAddress;
    address.serviceClassId = serviceGuid;
    address.port = BT_PORT_ANY;

    const int result = ::connect(socketHandleToConnect, reinterpret_cast<SOCKADDR *>(&address), sizeof(address));
    return result != SOCKET_ERROR;
}

bool BluetoothSocketWrapper::probeGaiaSocket(SOCKET socketHandleToProbe, const QString &label)
{
    // Try a generic GAIA v3 core request first, then the battery request used by
    // the existing UI. The channel is accepted only if it actually answers with
    // a GAIA packet; a plain RFCOMM socket open is not enough.
    const QList<QByteArray> probes = {
        QByteArray("\xFF\x03\x00\x00\x00\x1D\x00\x00", 8),
        QByteArray("\xFF\x03\x00\x00\x04\x95\x06\x03", 8)
    };

    for (const QByteArray &probe : probes) {
        int totalSent = 0;
        while (totalSent < probe.size()) {
            const int sent = ::send(socketHandleToProbe, probe.constData() + totalSent, static_cast<int>(probe.size() - totalSent), 0);
            if (sent == SOCKET_ERROR) {
                const int error = WSAGetLastError();
                qWarning() << "GAIA probe send failed for" << label << error << windowsSocketErrorText(error);
                return false;
            }
            totalSent += sent;
        }

        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(socketHandleToProbe, &readSet);

        timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

        const int selectResult = ::select(0, &readSet, nullptr, nullptr, &timeout);
        if (selectResult == SOCKET_ERROR) {
            const int error = WSAGetLastError();
            qWarning() << "GAIA probe select failed for" << label << error << windowsSocketErrorText(error);
            return false;
        }

        if (selectResult == 0 || !FD_ISSET(socketHandleToProbe, &readSet)) {
            qWarning() << "GAIA probe timed out for" << label << "probe" << probe.toHex(' ');
            continue;
        }

        char buffer[4096];
        const int received = ::recv(socketHandleToProbe, buffer, sizeof(buffer), 0);
        if (received <= 0) {
            const int error = WSAGetLastError();
            qWarning() << "GAIA probe receive failed for" << label << received << error << windowsSocketErrorText(error);
            return false;
        }

        const QByteArray response(buffer, received);
        qDebug() << "GAIA probe response for" << label << response;

        if (!response.contains(QByteArray("\xFF\x03", 2))) {
            qWarning() << "GAIA probe rejected" << label << "because the response is not a GAIA packet" << response;
            continue;
        }

        {
            QMutexLocker locker(&queueMutex);
            readQueue.enqueue(response);
        }

        return true;
    }

    qWarning() << "No GAIA probe succeeded for" << label << "; not opening the device page for this channel";
    return false;
}

std::vector<ULONG> BluetoothSocketWrapper::lookupRfcommChannels(BTH_ADDR bluetoothAddress, const GUID &serviceGuid, const QString &label)
{
    std::vector<ULONG> channels;

    SOCKADDR_BTH contextAddress;
    std::memset(&contextAddress, 0, sizeof(contextAddress));
    contextAddress.addressFamily = AF_BTH;
    contextAddress.btAddr = bluetoothAddress;
    contextAddress.port = BT_PORT_ANY;

    wchar_t contextBuffer[128];
    std::memset(contextBuffer, 0, sizeof(contextBuffer));
    DWORD contextLength = static_cast<DWORD>(sizeof(contextBuffer) / sizeof(contextBuffer[0]));
    const int addressStringResult = WSAAddressToStringW(
        reinterpret_cast<SOCKADDR *>(&contextAddress),
        sizeof(contextAddress),
        nullptr,
        contextBuffer,
        &contextLength);

    if (addressStringResult == SOCKET_ERROR) {
        const int error = WSAGetLastError();
        qWarning() << "Bluetooth SDP context address conversion failed for" << label << error << windowsSocketErrorText(error);
        return channels;
    }

    WSAQUERYSET query;
    std::memset(&query, 0, sizeof(query));
    query.dwSize = sizeof(query);
    query.dwNameSpace = NS_BTH;
    query.lpServiceClassId = const_cast<GUID *>(&serviceGuid);
    query.lpszContext = contextBuffer;
    query.dwNumberOfCsAddrs = 0;
    query.lpcsaBuffer = nullptr;

    HANDLE lookupHandle = nullptr;
    const DWORD flags = LUP_FLUSHCACHE | LUP_RETURN_NAME | LUP_RETURN_ADDR | LUP_RETURN_BLOB;
    int result = WSALookupServiceBegin(&query, flags, &lookupHandle);
    if (result == SOCKET_ERROR) {
        const int error = WSAGetLastError();
        qWarning() << "Bluetooth SDP lookup failed for" << label << error << windowsSocketErrorText(error)
                   << "context" << QString::fromWCharArray(contextBuffer);
        return channels;
    }

    QByteArray buffer;
    buffer.resize(8192);

    while (true) {
        DWORD bufferLength = static_cast<DWORD>(buffer.size());
        auto *resultSet = reinterpret_cast<WSAQUERYSET *>(buffer.data());
        std::memset(resultSet, 0, buffer.size());
        resultSet->dwSize = sizeof(WSAQUERYSET);

        result = WSALookupServiceNext(lookupHandle, flags, &bufferLength, resultSet);
        if (result == SOCKET_ERROR) {
            const int error = WSAGetLastError();
            if (error == WSA_E_NO_MORE) {
                break;
            }
            if (error == WSAEFAULT && bufferLength > static_cast<DWORD>(buffer.size())) {
                buffer.resize(static_cast<int>(bufferLength));
                continue;
            }
            qWarning() << "Bluetooth SDP lookup next failed for" << label << error << windowsSocketErrorText(error);
            break;
        }

        const QString serviceName = resultSet->lpszServiceInstanceName != nullptr
            ? QString::fromWCharArray(resultSet->lpszServiceInstanceName)
            : QString();

        for (DWORD i = 0; i < resultSet->dwNumberOfCsAddrs; ++i) {
            const CSADDR_INFO &entry = resultSet->lpcsaBuffer[i];
            if (entry.RemoteAddr.lpSockaddr == nullptr || entry.RemoteAddr.iSockaddrLength < static_cast<int>(sizeof(SOCKADDR_BTH))) {
                continue;
            }

            const auto *serviceAddress = reinterpret_cast<const SOCKADDR_BTH *>(entry.RemoteAddr.lpSockaddr);
            if (serviceAddress->addressFamily != AF_BTH) {
                continue;
            }

            const ULONG port = serviceAddress->port;
            qDebug() << "Bluetooth SDP result" << label << serviceName << "port" << port;
            if (port == 0 || port == BT_PORT_ANY) {
                continue;
            }

            bool alreadyKnown = false;
            for (const ULONG knownPort : channels) {
                if (knownPort == port) {
                    alreadyKnown = true;
                    break;
                }
            }

            if (!alreadyKnown) {
                channels.push_back(port);
                qDebug() << "Bluetooth SDP found RFCOMM channel for" << label << port;
            }
        }
    }

    WSALookupServiceEnd(lookupHandle);
    if (channels.empty()) {
        qWarning() << "Bluetooth SDP lookup returned no usable RFCOMM channels for" << label
                   << "context" << QString::fromWCharArray(contextBuffer);
    }
    return channels;
}

bool BluetoothSocketWrapper::connectToServiceByGuid(BTH_ADDR bluetoothAddress, const GUID &serviceGuid, const QString &label, SOCKET *connectedSocket)
{
    if (connectedSocket == nullptr) {
        return false;
    }

    const auto channels = lookupRfcommChannels(bluetoothAddress, serviceGuid, label);
    for (const ULONG channel : channels) {
        SOCKET candidate = createRfcommSocket();
        if (candidate == INVALID_SOCKET) {
            const int error = WSAGetLastError();
            qWarning() << "Unable to create Windows RFCOMM socket for" << label << error << windowsSocketErrorText(error);
            continue;
        }

        qDebug() << "Trying Windows RFCOMM channel" << channel << "for" << label;
        if (connectWithPort(candidate, bluetoothAddress, channel)) {
            qDebug() << "Connected Windows RFCOMM channel" << channel << "for" << label << "- validating GAIA response";
            if (probeGaiaSocket(candidate, QStringLiteral("%1 channel %2").arg(label).arg(channel))) {
                *connectedSocket = candidate;
                return true;
            }

            qWarning() << "RFCOMM channel" << channel << "for" << label << "accepted the socket but did not answer GAIA; trying next service";
            ::closesocket(candidate);
            continue;
        }

        const int error = WSAGetLastError();
        qWarning() << "RFCOMM channel connect failed for" << label << "channel" << channel << error << windowsSocketErrorText(error);
        ::closesocket(candidate);
    }

    SOCKET candidate = createRfcommSocket();
    if (candidate == INVALID_SOCKET) {
        const int error = WSAGetLastError();
        qWarning() << "Unable to create direct Windows RFCOMM socket for" << label << error << windowsSocketErrorText(error);
        return false;
    }

    qDebug() << "Trying direct Windows RFCOMM UUID connect for" << label;
    if (connectWithGuid(candidate, bluetoothAddress, serviceGuid)) {
        qDebug() << "Connected direct Windows RFCOMM UUID for" << label << "- validating GAIA response";
        if (probeGaiaSocket(candidate, QStringLiteral("%1 direct UUID").arg(label))) {
            *connectedSocket = candidate;
            return true;
        }

        qWarning() << "Direct UUID connection for" << label << "opened but did not answer GAIA";
        ::closesocket(candidate);
        return false;
    }

    const int error = WSAGetLastError();
    qWarning() << "Direct UUID connect failed for" << label << error << windowsSocketErrorText(error);
    ::closesocket(candidate);
    return false;
}

void BluetoothSocketWrapper::workerMain(QString address)
{
    auto fail = [this](const QString &message) {
        QMetaObject::invokeMethod(this, [this, message]() {
            Q_EMIT connectionFailed(message);
            Q_EMIT disconnected();
        }, Qt::QueuedConnection);
    };

    if (!ensureWinsockStarted()) {
        fail(QStringLiteral("Windows socket startup failed."));
        return;
    }

    BTH_ADDR bluetoothAddress = 0;
    if (!parseBluetoothAddress(address, &bluetoothAddress)) {
        qWarning() << "Invalid Bluetooth address for Windows RFCOMM" << address;
        fail(QStringLiteral("Invalid Bluetooth address: %1").arg(address));
        return;
    }

    qDebug() << "Opening native Windows RFCOMM Momentum 4 control socket" << address;

    SOCKET candidate = INVALID_SOCKET;
    if (!connectToServiceByGuid(bluetoothAddress, momentum4ControlServiceGuid(), QStringLiteral("Momentum 4 Control"), &candidate)) {
        qWarning() << "Momentum 4 control service connect failed; trying legacy GAIA service";
        if (!connectToServiceByGuid(bluetoothAddress, legacyGaiaServiceGuid(), QStringLiteral("Legacy GAIA FDCE"), &candidate)) {
            qWarning() << "Legacy GAIA service connect failed; trying serial-port service";
            if (!connectToServiceByGuid(bluetoothAddress, serialPortServiceGuid(), QStringLiteral("Serial Port"), &candidate)) {
                const QString message = QStringLiteral("No usable Momentum 4 / GAIA RFCOMM control service answered on %1. The headset socket may be available, but it is not responding to GAIA control packets.").arg(address);
                qWarning() << message;
                fail(message);
                return;
            }
        }
    }

    {
        QMutexLocker locker(&socketMutex);
        socketHandle = candidate;
        openState.store(true);
        qDebug() << "Native Windows RFCOMM socket marked open; flushing queued writes" << pendingWriteQueue.size();
        flushWriteQueueLocked();
    }

    QMetaObject::invokeMethod(this, [this]() {
        Q_EMIT connected();
        Q_EMIT readyRead();
    }, Qt::QueuedConnection);

    char buffer[4096];
    while (!stopRequested.load()) {
        const int received = ::recv(candidate, buffer, sizeof(buffer), 0);
        if (received > 0) {
            {
                QMutexLocker locker(&queueMutex);
                readQueue.enqueue(QByteArray(buffer, received));
            }
            QMetaObject::invokeMethod(this, [this]() { Q_EMIT readyRead(); }, Qt::QueuedConnection);
            continue;
        }

        if (received == 0 || !stopRequested.load()) {
            const int error = WSAGetLastError();
            if (error != WSAEINTR && error != WSAENOTSOCK) {
                qWarning() << "Windows RFCOMM receive stopped" << error << windowsSocketErrorText(error);
            }
        }
        break;
    }

    bool shouldCloseSocket = false;
    {
        QMutexLocker locker(&socketMutex);
        if (socketHandle == candidate) {
            socketHandle = INVALID_SOCKET;
            shouldCloseSocket = true;
        }
        openState.store(false);
    }

    if (shouldCloseSocket) {
        ::closesocket(candidate);
    }
    QMetaObject::invokeMethod(this, [this]() { Q_EMIT disconnected(); }, Qt::QueuedConnection);
}

void BluetoothSocketWrapper::stopWorker(bool waitForThread)
{
    stopRequested.store(true);

    {
        QMutexLocker locker(&socketMutex);
        if (socketHandle != INVALID_SOCKET) {
            ::shutdown(socketHandle, SD_BOTH);
            ::closesocket(socketHandle);
            socketHandle = INVALID_SOCKET;
        }
        pendingWriteQueue.clear();
        openState.store(false);
    }

    if (waitForThread && workerThread.joinable() && workerThread.get_id() != std::this_thread::get_id()) {
        workerThread.join();
    } else if (workerThread.joinable() && workerThread.get_id() == std::this_thread::get_id()) {
        workerThread.detach();
    }
}
#endif
