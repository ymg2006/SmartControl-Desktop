#include "GAIAPropertyClasses.h"

Upgrade_Abort::Upgrade_Abort(QObject *parent) : GAIAPropertyBase(parent) {
}

Upgrade_CommitCfm::Upgrade_CommitCfm(QObject *parent) : GAIAPropertyBase(parent) {
}

Upgrade_ErrorConfirmation::Upgrade_ErrorConfirmation(QObject *parent) : GAIAPropertyBase(parent) {
}

Upgrade_GaiaConnect::Upgrade_GaiaConnect(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0C00;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0D00;
    resultTypes = {};
}

Upgrade_GaiaData::Upgrade_GaiaData(QObject *parent) : GAIAPropertyBase(parent) {
}

Upgrade_GaiaDisconnect::Upgrade_GaiaDisconnect(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0C01;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0D01;
    resultTypes = {};
}

Upgrade_GaiaIsValidationDone::Upgrade_GaiaIsValidationDone(QObject *parent) : GAIAPropertyBase(parent) {
}

Upgrade_GaiaStart::Upgrade_GaiaStart(QObject *parent) : GAIAPropertyBase(parent) {
}

Upgrade_GaiaStartData::Upgrade_GaiaStartData(QObject *parent) : GAIAPropertyBase(parent) {
}

Upgrade_GaiaSync::Upgrade_GaiaSync(QObject *parent) : GAIAPropertyBase(parent) {
}

Upgrade_ProceedToCommit::Upgrade_ProceedToCommit(QObject *parent) : GAIAPropertyBase(parent) {
}

Upgrade_TransferComplete_Trigger::Upgrade_TransferComplete_Trigger(QObject *parent) : GAIAPropertyBase(parent) {
}

Core_SerialNumber::Core_SerialNumber(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x001D;
    getCommandId = 0x0003;
    getResponseVendorId = 0x001D;
    getResponseCommandId = 0x0103;
    valueTypes = {ParameterType::STRING};
}

Service_FactoryReset::Service_FactoryReset(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0040;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0140;
    resultTypes = {};
}

Service_HWRevision::Service_HWRevision(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1200;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1300;
    valueTypes = {ParameterType::UINT16, ParameterType::UINT16};
}

Service_SystemReleaseVersion::Service_SystemReleaseVersion(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1201;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1301;
    valueTypes = {ParameterType::UINT16, ParameterType::UINT16, ParameterType::UINT16};
}

Config_SetTimer::Config_SetTimer(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0600;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0700;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8, ParameterType::UINT16};
}

Config_GetTimer::Config_GetTimer(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0601;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0701;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT16};
    parameterTypes = {ParameterType::UINT8};
}

Setting_AudioPromptMode::Setting_AudioPromptMode(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0802;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0902;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x0801;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x0901;
    setTypes = {ParameterType::UINT8};
}

AudioPrompt_GetAudioPromptsLanguageVersions::AudioPrompt_GetAudioPromptsLanguageVersions(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0809;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0909;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT32, ParameterType::UINT8, ParameterType::UINT32};
    parameterTypes = {ParameterType::UINT8};
}

AudioPrompt_GetAvailableAudioPromptsLanguages::AudioPrompt_GetAvailableAudioPromptsLanguages(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0808;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0908;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT8};
}

Battery_ChargingStatus::Battery_ChargingStatus(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0602;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0702;
    valueTypes = {ParameterType::UINT8, ParameterType::UINT8};
}

Upgrade_Enable::Upgrade_Enable(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0200;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0300;
    resultTypes = {};
}

UpgradeFileSize::UpgradeFileSize(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0201;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0301;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT32};
}

Battery_Percent::Battery_Percent(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0603;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0703;
    valueTypes = {ParameterType::UINT8, ParameterType::UINT8};
}

PairedDevicesListSize::PairedDevicesListSize(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1400;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1500;
    valueTypes = {ParameterType::UINT16};
}

PairedDevicesMaxBTConnections::PairedDevicesMaxBTConnections(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1409;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1509;
    valueTypes = {ParameterType::UINT8};
}

PairedDevicesOwnDeviceIndex::PairedDevicesOwnDeviceIndex(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1407;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1507;
    valueTypes = {ParameterType::UINT8};
}

PairedDevicesConnectDevice::PairedDevicesConnectDevice(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1402;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1502;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

PairedDevicesDeleteEntry::PairedDevicesDeleteEntry(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1405;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1505;
    resultTypes = {ParameterType::UINT8};
    parameterTypes = {ParameterType::UINT8};
}

PairedDevicesDeleteList::PairedDevicesDeleteList(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1406;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1506;
    resultTypes = {};
}

PairedDevicesDisconnectDevice::PairedDevicesDisconnectDevice(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1403;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1503;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

PairedDevicesGetConnectionStatus::PairedDevicesGetConnectionStatus(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1404;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1504;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT8};
    parameterTypes = {ParameterType::UINT8};
}

PairedDevicesGetDeviceInfo::PairedDevicesGetDeviceInfo(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1401;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1501;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8, ParameterType::STRING};
    parameterTypes = {ParameterType::UINT8};
}

Sound_CodecUsed::Sound_CodecUsed(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0800;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0900;
    valueTypes = {ParameterType::UINT8};
}

FirmwareVersions::FirmwareVersions(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1202;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1302;
    valueTypes = {ParameterType::UINT8};
}

Setting_AutoLockMode::Setting_AutoLockMode(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1607;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1707;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x1606;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x1706;
    setTypes = {ParameterType::UINT8};
}

IsDefaultMMIConfig::IsDefaultMMIConfig(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1605;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1705;
    resultTypes = {ParameterType::BOOL};
}

SetMMIConfig::SetMMIConfig(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1600;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1700;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8};
}

SetDefaultMMIConfig::SetDefaultMMIConfig(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1604;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1704;
    resultTypes = {};
}

GetMMIConfig::GetMMIConfig(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x1601;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x1701;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8};
    parameterTypes = {ParameterType::UINT8, ParameterType::UINT8};
}

ANC_Status::ANC_Status(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1A05;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1B05;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x1A04;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x1B04;
    setTypes = {ParameterType::UINT8};
}

ANC::ANC(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1A01;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1B01;
    valueTypes = {ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x1A00;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x1B00;
    setTypes = {ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8};
}

ANC_Transparency::ANC_Transparency(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1A03;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1B03;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x1A02;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x1B02;
    setTypes = {ParameterType::UINT8};
}

TransparentHearingMode::TransparentHearingMode(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1801;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1901;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x1800;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x1900;
    setTypes = {ParameterType::UINT8};
}

TransparentHearing_Status::TransparentHearing_Status(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1805;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1905;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x1804;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x1904;
    setTypes = {ParameterType::UINT8};
}

TransparentHearing::TransparentHearing(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1803;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1903;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x1802;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x1902;
    setTypes = {ParameterType::UINT8};
}

RegisterNotification_qcore::RegisterNotification_qcore(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_qEarbud::RegisterNotification_qEarbud(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_qAudioCuration::RegisterNotification_qAudioCuration(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_qVoiceUI::RegisterNotification_qVoiceUI(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_qDebug::RegisterNotification_qDebug(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_qDFU::RegisterNotification_qDFU(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_core::RegisterNotification_core(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_genericAudio::RegisterNotification_genericAudio(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_userEQ::RegisterNotification_userEQ(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

Versions_ModelId::Versions_ModelId(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x1206;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x1306;
    valueTypes = {ParameterType::STRING};
}

RegisterNotification_versions::RegisterNotification_versions(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_deviceManagement::RegisterNotification_deviceManagement(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_mmi::RegisterNotification_mmi(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_transparentHearing::RegisterNotification_transparentHearing(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_ANC::RegisterNotification_ANC(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_battery::RegisterNotification_battery(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

RegisterNotification_Device::RegisterNotification_Device(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x0495;
    invocationCommandId = 0x0007;
    invocationResponseVendorId = 0x0495;
    invocationResponseCommandId = 0x0107;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT8};
}

SidetoneState::SidetoneState(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0806;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0906;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x0805;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x0905;
    setTypes = {ParameterType::UINT8};
}

Setting_AutoCall::Setting_AutoCall(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x080B;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x090B;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x080A;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x090A;
    setTypes = {ParameterType::UINT8};
}

Setting_OnHeadDetection::Setting_OnHeadDetection(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0401;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0501;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x0400;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x0500;
    setTypes = {ParameterType::UINT8};
}

Setting_ComfortCall::Setting_ComfortCall(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0815;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0915;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x0814;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x0914;
    setTypes = {ParameterType::UINT8};
}

Setting_SmartPause::Setting_SmartPause(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x080D;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x090D;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x080C;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x090C;
    setTypes = {ParameterType::UINT8};
}

Primary_Side::Primary_Side(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0041;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0141;
    valueTypes = {ParameterType::UINT8};
}

BluetoothCompatibilityMode::BluetoothCompatibilityMode(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0406;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0506;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x0405;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x0505;
    setTypes = {ParameterType::UINT8};
}

VoicePrompt_Language::VoicePrompt_Language(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0807;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0907;
    valueTypes = {ParameterType::UINT8};
}

PhysicalDevice_State::PhysicalDevice_State(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0402;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0502;
    valueTypes = {ParameterType::UINT8, ParameterType::UINT8};
}

Statistics_GetAvailableCategories::Statistics_GetAvailableCategories(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x1800;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x1900;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT16};
    parameterTypes = {ParameterType::UINT16};
}

Statistics_GetAllStatisticsInCategory::Statistics_GetAllStatisticsInCategory(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x1801;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x1901;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT16, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8};
    parameterTypes = {ParameterType::UINT16, ParameterType::UINT8};
}

Statistics_GetStatisticsValues::Statistics_GetStatisticsValues(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x1802;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x1902;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT16, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8, ParameterType::UINT8};
    parameterTypes = {ParameterType::UINT16, ParameterType::UINT8};
}

VoiceUI_Selected_Assistant::VoiceUI_Selected_Assistant(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x001D;
    getCommandId = 0x0600;
    getResponseVendorId = 0x001D;
    getResponseCommandId = 0x0700;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x001D;
    setCommandId = 0x0601;
    setResponseVendorId = 0x001D;
    setResponseCommandId = 0x0701;
    setTypes = {ParameterType::UINT8};
}

VoiceUI_Supported_Assistants::VoiceUI_Supported_Assistants(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x001D;
    getCommandId = 0x0602;
    getResponseVendorId = 0x001D;
    getResponseCommandId = 0x0702;
    valueTypes = {ParameterType::UINT8, ParameterType::UINT8};
}

LowLatencyMode::LowLatencyMode(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x0495;
    getCommandId = 0x0818;
    getResponseVendorId = 0x0495;
    getResponseCommandId = 0x0918;
    valueTypes = {ParameterType::UINT8};
    setVendorId = 0x0495;
    setCommandId = 0x0817;
    setResponseVendorId = 0x0495;
    setResponseCommandId = 0x0917;
    setTypes = {ParameterType::UINT8};
}

Debug_GetPanicLogInfo::Debug_GetPanicLogInfo(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0803;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0903;
    resultTypes = {ParameterType::UINT16, ParameterType::UINT32};
    parameterTypes = {};
}

Core_DataTransferSetup::Core_DataTransferSetup(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0009;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0109;
    resultTypes = {ParameterType::UINT16};
    parameterTypes = {ParameterType::UINT16, ParameterType::UINT8};
}

Core_DataTransferGet::Core_DataTransferGet(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x000A;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x010A;
    resultTypes = {ParameterType::UINT16, ParameterType::UINT8};
    parameterTypes = {ParameterType::UINT16, ParameterType::UINT32, ParameterType::UINT32};
}

Core_GetTransportInfo::Core_GetTransportInfo(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x000C;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x010C;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT32};
    parameterTypes = {ParameterType::UINT8};
}

Debug_ErasePanicLog::Debug_ErasePanicLog(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001D;
    invocationCommandId = 0x0804;
    invocationResponseVendorId = 0x001D;
    invocationResponseCommandId = 0x0904;
    resultTypes = {};
    parameterTypes = {ParameterType::UINT16};
}

Core_Api_Version::Core_Api_Version(QObject *parent) : GAIAPropertyBase(parent) {
    getVendorId = 0x001d;
    getCommandId = 0x0000;
    getResponseVendorId = 0x001d;
    getResponseCommandId = 0x0100;
    valueTypes = {ParameterType::UINT8, ParameterType::UINT8};
}

Core_GetSupportedFeatures::Core_GetSupportedFeatures(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001d;
    invocationCommandId = 0x0001;
    invocationResponseVendorId = 0x001d;
    invocationResponseCommandId = 0x0101;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT8};
    parameterTypes = {};
}

Core_GetSupportedFeaturesNext::Core_GetSupportedFeaturesNext(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001d;
    invocationCommandId = 0x0002;
    invocationResponseVendorId = 0x001d;
    invocationResponseCommandId = 0x0102;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT8};
    parameterTypes = {};
}

Core_SetTransportParameter::Core_SetTransportParameter(QObject *parent) : GAIAPropertyBase(parent) {
    invocationVendorId = 0x001d;
    invocationCommandId = 0x000d;
    invocationResponseVendorId = 0x001d;
    invocationResponseCommandId = 0x010d;
    resultTypes = {ParameterType::UINT8, ParameterType::UINT32};
    parameterTypes = {ParameterType::UINT8, ParameterType::UINT32};
}
