#include "ConnectedDevicesCardHelper.h"
#include "gaiaV3/GAIARfcommClient.h"

#include <QTimer>

using namespace Qt::Literals::StringLiterals;

QVariant PairedDevicesModel::data(const QModelIndex &index, int role) const {
    const auto &i = index.row();
    if (!index.isValid() || i < 0 || i >= m_pairedDevices.length())
        return QVariant();

    switch (role) {
        case NameRole:
            return m_pairedDevices[i].name;
            break;
        case ConnectedRole:
            return m_pairedDevices[i].connected;
            break;
        case DeviceIndexRole:
            return m_pairedDevices[i].index;
            break;
        default:
            return QVariant();
    }
}

int PairedDevicesModel::rowCount(const QModelIndex &parent) const {
    return m_pairedDevices.size();
}


QHash<int, QByteArray> PairedDevicesModel::roleNames() const {
    return {
            {NameRole, "name"},
            {ConnectedRole, "connected"},
            {DeviceIndexRole, "deviceIndex"}
    };
}


void PairedDevicesModel::addPairedDevices(const PairedDeviceInfo &device) {
    for (int i = 0; i < m_pairedDevices.size(); ++i) {
        if (m_pairedDevices[i].index == device.index) {
            m_pairedDevices[i] = device;
            Q_EMIT dataChanged(index(i, 0), index(i, 0));
            return;
        }
    }

    beginInsertRows(QModelIndex(), m_pairedDevices.size(), m_pairedDevices.size());
//    beginInsertRows(QModelIndex(), 0, m_pairedDevices.size());
    m_pairedDevices << device;
    endInsertRows();
}

int PairedDevicesModel::connectedCount() const {
    int count = 0;
    for (const auto &device : m_pairedDevices) {
        if (device.connected)
            ++count;
    }
    return count;
}

PairedDevicesModel::PairedDevicesModel(QObject *parent) :
        QAbstractListModel(parent),
    m_pairedDevices{}
{
}

void PairedDevicesModel::clear() {
    if (m_pairedDevices.isEmpty())
        return;

    beginRemoveRows(QModelIndex(), 0, m_pairedDevices.size() - 1);
    m_pairedDevices.clear();
    endRemoveRows();
}

ConnectedDevicesCardHelper::ConnectedDevicesCardHelper(QObject *parent) :
    QObject(parent),
    m_maxConnections(0),
    m_ownIndex(0),
    m_totalPaired(0),
    pairedDevicesListSize(GAIARfcommClient::getInstance().getManager()->getProperty("\x04\x95\x15\x00"_ba)),
    pairedDevicesMaxBTConnections(GAIARfcommClient::getInstance().getManager()->getProperty("\x04\x95\x15\x09"_ba)),
    pairedDevicesOwnDeviceIndex(GAIARfcommClient::getInstance().getManager()->getProperty("\x04\x95\x15\x07"_ba)),
    pairedDevicesGetDeviceInfo(GAIARfcommClient::getInstance().getManager()->getProperty("\x04\x95\x15\x01"_ba)),
    pairedDevicesConnectDevice(GAIARfcommClient::getInstance().getManager()->getProperty("\x04\x95\x15\x02"_ba)),
    pairedDevicesDeleteEntry(GAIARfcommClient::getInstance().getManager()->getProperty("\x04\x95\x15\x05"_ba)),
    pairedDevicesDisconnectDevice(GAIARfcommClient::getInstance().getManager()->getProperty("\x04\x95\x15\x03"_ba)),
    m_model(new PairedDevicesModel(this))
{
    if (pairedDevicesListSize != nullptr){
        connect(pairedDevicesListSize, &GAIAPropertyBase::valueChanged, this, &ConnectedDevicesCardHelper::changePairedDevicesListSizeValue);
        pairedDevicesListSize->sendGet();
    }
    if (pairedDevicesMaxBTConnections != nullptr){
        connect(pairedDevicesMaxBTConnections, &GAIAPropertyBase::valueChanged, this, &ConnectedDevicesCardHelper::changePairedDevicesMaxBTConnectionsValue);
        pairedDevicesMaxBTConnections->sendGet();
    }
    if (pairedDevicesOwnDeviceIndex != nullptr){
        connect(pairedDevicesOwnDeviceIndex, &GAIAPropertyBase::valueChanged, this, &ConnectedDevicesCardHelper::changePairedDevicesOwnDeviceIndexValue);
        pairedDevicesOwnDeviceIndex->sendGet();
    }
    if (pairedDevicesGetDeviceInfo != nullptr){
        connect(pairedDevicesGetDeviceInfo, &GAIAPropertyBase::resultChanged, this, &ConnectedDevicesCardHelper::changePairedDevicesGetDeviceInfoResult);
    }
    if (pairedDevicesConnectDevice != nullptr){
        connect(pairedDevicesConnectDevice, &GAIAPropertyBase::resultChanged, this, &ConnectedDevicesCardHelper::deviceConnectionUpdated);
    }
    if (pairedDevicesDeleteEntry != nullptr){
        connect(pairedDevicesDeleteEntry, &GAIAPropertyBase::resultChanged, this, &ConnectedDevicesCardHelper::deviceConnectionUpdated);
    }
    if (pairedDevicesDisconnectDevice != nullptr){
        connect(pairedDevicesDisconnectDevice, &GAIAPropertyBase::resultChanged, this, &ConnectedDevicesCardHelper::deviceConnectionUpdated);
    }
}

int ConnectedDevicesCardHelper::getTotalPaired() const {
    return m_totalPaired;
}

int ConnectedDevicesCardHelper::getMaxConnections() const {
    return m_maxConnections;
}

int ConnectedDevicesCardHelper::getOwnIndex() const {
    return m_ownIndex;
}

int ConnectedDevicesCardHelper::getConnectedCount() const {
    return m_model != nullptr ? m_model->connectedCount() : 0;
}

PairedDevicesModel *ConnectedDevicesCardHelper::getModel() {
    return m_model;
}

void ConnectedDevicesCardHelper::changePairedDevicesListSizeValue() {
    const auto &pdls = pairedDevicesListSize->getValue();
    if (pdls.length() < 1){
        return;
    }
    m_totalPaired = pdls.at(0).toInt();
    Q_EMIT totalPairedChanged();

    if (pairedDevicesGetDeviceInfo != nullptr){
        for (auto i = 0; i < m_totalPaired; i++){
            pairedDevicesGetDeviceInfo->sendInvocation({static_cast<uint8_t>(i)});
        }
    }
}

void ConnectedDevicesCardHelper::changePairedDevicesMaxBTConnectionsValue() {
    const auto & padmbc = pairedDevicesMaxBTConnections->getValue();
    if (padmbc.length() < 1){
        return;
    }

    m_maxConnections = padmbc.at(0).toInt();
    Q_EMIT maxConnectionsChanged();
}

void ConnectedDevicesCardHelper::changePairedDevicesOwnDeviceIndexValue() {
    const auto pdodi = pairedDevicesOwnDeviceIndex->getValue();
    if (pdodi.length() < 1){
        return;
    }
    m_ownIndex = pdodi.at(0).toInt();
    Q_EMIT ownIndexChanged();
}

void ConnectedDevicesCardHelper::changePairedDevicesGetDeviceInfoResult() {
    const auto &pdgdi = pairedDevicesGetDeviceInfo->getResult();
    if (pdgdi.length() < 4){
        return;
    }
    const PairedDeviceInfo di{
        pdgdi.at(3).toString().trimmed().replace("\u0000"_ba, ""),
        pdgdi.at(2).toBool(),
        pdgdi.at(0).toInt(),
    };

    m_model->addPairedDevices(di);
    Q_EMIT connectedCountChanged();

}

void ConnectedDevicesCardHelper::connectDevice(const int &index) {
    pairedDevicesConnectDevice->sendInvocation({
        {static_cast<uint8_t >(index)}
    });
}

void ConnectedDevicesCardHelper::disconnectDevice(const int &index) {
    pairedDevicesDisconnectDevice->sendInvocation({
           {static_cast<uint8_t >(index)}
   });
}

void ConnectedDevicesCardHelper::deleteDevice(const int &index) {
    pairedDevicesDeleteEntry->sendInvocation({
          {static_cast<uint8_t >(index)}
    });
}

void ConnectedDevicesCardHelper::deviceConnectionUpdated() {

    auto t = new QTimer(this);
    t->singleShot(1000, [this, t](){
        m_model->clear();
        Q_EMIT connectedCountChanged();
        pairedDevicesListSize->sendGet();
        t->deleteLater();
    });
}
