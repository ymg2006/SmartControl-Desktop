#include "BluetoothHandler.h"
#include "gaiaV3/GAIARfcommClient.h"

#include <QDebug>

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  include <bluetoothapis.h>
#endif

namespace {

bool looksLikeSupportedSennheiserName(const QString &name)
{
    const QString lower = name.toLower();
    return lower.contains(QStringLiteral("sennheiser"))
        || lower.contains(QStringLiteral("momentum"))
        || lower.contains(QStringLiteral("accentum"))
        || lower.contains(QStringLiteral("hd 350"))
        || lower.contains(QStringLiteral("hd 450"))
        || lower.contains(QStringLiteral("hd 4"))
        || lower.contains(QStringLiteral("m4"));
}

#ifdef _WIN32
QString windowsBluetoothAddressToString(const BLUETOOTH_ADDRESS &address)
{
    return QStringLiteral("%1:%2:%3:%4:%5:%6")
        .arg(address.rgBytes[5], 2, 16, QLatin1Char('0'))
        .arg(address.rgBytes[4], 2, 16, QLatin1Char('0'))
        .arg(address.rgBytes[3], 2, 16, QLatin1Char('0'))
        .arg(address.rgBytes[2], 2, 16, QLatin1Char('0'))
        .arg(address.rgBytes[1], 2, 16, QLatin1Char('0'))
        .arg(address.rgBytes[0], 2, 16, QLatin1Char('0'))
        .toUpper();
}
#endif

}

BluetoothHandler::BluetoothHandler(QObject *parent)
    : QObject(parent)
    , m_isSearching(false)
    , m_deviceAddress("")
{
}

void BluetoothHandler::refreshKnownDevices()
{
    if (!m_isSearching) {
        m_isSearching = true;
        Q_EMIT isSearchingChanged();
    }

    Q_EMIT refreshStarted();
    addKnownWindowsDevices();
    Q_EMIT refreshFinished();

    if (m_isSearching) {
        m_isSearching = false;
        Q_EMIT isSearchingChanged();
    }
}

bool BluetoothHandler::getIsSearching() const
{
    return m_isSearching;
}

QString BluetoothHandler::getDeviceAddress() const
{
    return m_deviceAddress;
}

void BluetoothHandler::setDeviceAddress(const QString &address)
{
    const QString normalized = address.trimmed().toUpper();
    if (m_deviceAddress == normalized) {
        return;
    }

    m_deviceAddress = normalized;
    Q_EMIT deviceAddressChanged();
}

void BluetoothHandler::addKnownWindowsDevices()
{
#ifdef _WIN32
    BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams;
    ZeroMemory(&searchParams, sizeof(searchParams));
    searchParams.dwSize = sizeof(searchParams);
    searchParams.fReturnAuthenticated = TRUE;
    searchParams.fReturnRemembered = TRUE;
    searchParams.fReturnConnected = TRUE;
    searchParams.fReturnUnknown = FALSE;
    searchParams.fIssueInquiry = FALSE;
    searchParams.cTimeoutMultiplier = 0;
    searchParams.hRadio = nullptr;

    BLUETOOTH_DEVICE_INFO deviceInfo;
    ZeroMemory(&deviceInfo, sizeof(deviceInfo));
    deviceInfo.dwSize = sizeof(deviceInfo);

    HBLUETOOTH_DEVICE_FIND findHandle = BluetoothFindFirstDevice(&searchParams, &deviceInfo);
    if (!findHandle) {
        qWarning() << "No Windows Bluetooth devices returned by BluetoothFindFirstDevice";
        return;
    }

    do {
        const QString name = QString::fromWCharArray(deviceInfo.szName).trimmed();
        if (name.isEmpty() || !looksLikeSupportedSennheiserName(name)) {
            continue;
        }

        const QString address = windowsBluetoothAddressToString(deviceInfo.Address);
        const bool connected = deviceInfo.fConnected != FALSE;
        const bool remembered = deviceInfo.fRemembered != FALSE || deviceInfo.fAuthenticated != FALSE;

        qDebug() << "Known Windows Bluetooth device:" << name << address
                 << "connected" << connected
                 << "remembered" << remembered
                 << "authenticated" << (deviceInfo.fAuthenticated != FALSE);

        Q_EMIT newDeviceAdded(name, address, QString(), connected, remembered);
    } while (BluetoothFindNextDevice(findHandle, &deviceInfo));

    BluetoothFindDeviceClose(findHandle);
#else
    qWarning() << "This application is now Windows-only.";
#endif
}
