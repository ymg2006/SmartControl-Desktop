#include "GAIAPropertyManager.h"

using namespace Qt::Literals::StringLiterals;

GAIAPropertyManager::GAIAPropertyManager(QObject *parent) : GAIAPropertyManagerBase() {}
GAIAPropertyBase *GAIAPropertyManager::getPropertyFromVendorCommand(const quint16 &vendorId, const quint16 &commandId) {
    if (vendorId == 0x001D && commandId == 0x0D00){
            return new Upgrade_GaiaConnect(this);
        }
    if (vendorId == 0x001D && commandId == 0x0D01){
            return new Upgrade_GaiaDisconnect(this);
        }
    if (vendorId == 0x001D && commandId == 0x0103){
            return new Core_SerialNumber(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0140){
            return new Service_FactoryReset(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1300){
            return new Service_HWRevision(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1301){
            return new Service_SystemReleaseVersion(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0700){
            return new Config_SetTimer(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0701){
            return new Config_GetTimer(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0902){
            return new Setting_AudioPromptMode(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0901){
            return getPropertyFromVendorCommand(0x0495, 0x0902);
        }
    if (vendorId == 0x0495 && commandId == 0x0909){
            return new AudioPrompt_GetAudioPromptsLanguageVersions(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0908){
            return new AudioPrompt_GetAvailableAudioPromptsLanguages(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0702){
            return new Battery_ChargingStatus(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0300){
            return new Upgrade_Enable(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0301){
            return new UpgradeFileSize(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0703){
            return new Battery_Percent(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1500){
            return new PairedDevicesListSize(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1509){
            return new PairedDevicesMaxBTConnections(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1507){
            return new PairedDevicesOwnDeviceIndex(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1502){
            return new PairedDevicesConnectDevice(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1505){
            return new PairedDevicesDeleteEntry(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1506){
            return new PairedDevicesDeleteList(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1503){
            return new PairedDevicesDisconnectDevice(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1504){
            return new PairedDevicesGetConnectionStatus(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1501){
            return new PairedDevicesGetDeviceInfo(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0900){
            return new Sound_CodecUsed(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1302){
            return new FirmwareVersions(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1707){
            return new Setting_AutoLockMode(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1706){
            return getPropertyFromVendorCommand(0x0495, 0x1707);
        }
    if (vendorId == 0x0495 && commandId == 0x1705){
            return new IsDefaultMMIConfig(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1700){
            return new SetMMIConfig(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1704){
            return new SetDefaultMMIConfig(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1701){
            return new GetMMIConfig(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1B05){
            return new ANC_Status(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1B04){
            return getPropertyFromVendorCommand(0x0495, 0x1B05);
        }
    if (vendorId == 0x0495 && commandId == 0x1B01){
            return new ANC(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1B00){
            return getPropertyFromVendorCommand(0x0495, 0x1B01);
        }
    if (vendorId == 0x0495 && commandId == 0x1B03){
            return new ANC_Transparency(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1B02){
            return getPropertyFromVendorCommand(0x0495, 0x1B03);
        }
    if (vendorId == 0x0495 && commandId == 0x1901){
            return new TransparentHearingMode(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1900){
            return getPropertyFromVendorCommand(0x0495, 0x1901);
        }
    if (vendorId == 0x0495 && commandId == 0x1905){
            return new TransparentHearing_Status(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1904){
            return getPropertyFromVendorCommand(0x0495, 0x1905);
        }
    if (vendorId == 0x0495 && commandId == 0x1903){
            return new TransparentHearing(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1902){
            return getPropertyFromVendorCommand(0x0495, 0x1903);
        }
    if (vendorId == 0x001D && commandId == 0x0107){
            return new RegisterNotification_qcore(this);
        }
    if (vendorId == 0x001D && commandId == 0x0107){
            return new RegisterNotification_qEarbud(this);
        }
    if (vendorId == 0x001D && commandId == 0x0107){
            return new RegisterNotification_qAudioCuration(this);
        }
    if (vendorId == 0x001D && commandId == 0x0107){
            return new RegisterNotification_qVoiceUI(this);
        }
    if (vendorId == 0x001D && commandId == 0x0107){
            return new RegisterNotification_qDebug(this);
        }
    if (vendorId == 0x001D && commandId == 0x0107){
            return new RegisterNotification_qDFU(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_core(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_genericAudio(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_userEQ(this);
        }
    if (vendorId == 0x0495 && commandId == 0x1306){
            return new Versions_ModelId(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_versions(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_deviceManagement(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_mmi(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_transparentHearing(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_ANC(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_battery(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0107){
            return new RegisterNotification_Device(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0906){
            return new SidetoneState(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0905){
            return getPropertyFromVendorCommand(0x0495, 0x0906);
        }
    if (vendorId == 0x0495 && commandId == 0x090B){
            return new Setting_AutoCall(this);
        }
    if (vendorId == 0x0495 && commandId == 0x090A){
            return getPropertyFromVendorCommand(0x0495, 0x090B);
        }
    if (vendorId == 0x0495 && commandId == 0x0501){
            return new Setting_OnHeadDetection(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0500){
            return getPropertyFromVendorCommand(0x0495, 0x0501);
        }
    if (vendorId == 0x0495 && commandId == 0x0915){
            return new Setting_ComfortCall(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0914){
            return getPropertyFromVendorCommand(0x0495, 0x0915);
        }
    if (vendorId == 0x0495 && commandId == 0x090D){
            return new Setting_SmartPause(this);
        }
    if (vendorId == 0x0495 && commandId == 0x090C){
            return getPropertyFromVendorCommand(0x0495, 0x090D);
        }
    if (vendorId == 0x0495 && commandId == 0x0141){
            return new Primary_Side(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0506){
            return new BluetoothCompatibilityMode(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0505){
            return getPropertyFromVendorCommand(0x0495, 0x0506);
        }
    if (vendorId == 0x0495 && commandId == 0x0907){
            return new VoicePrompt_Language(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0502){
            return new PhysicalDevice_State(this);
        }
    if (vendorId == 0x001D && commandId == 0x1900){
            return new Statistics_GetAvailableCategories(this);
        }
    if (vendorId == 0x001D && commandId == 0x1901){
            return new Statistics_GetAllStatisticsInCategory(this);
        }
    if (vendorId == 0x001D && commandId == 0x1902){
            return new Statistics_GetStatisticsValues(this);
        }
    if (vendorId == 0x001D && commandId == 0x0700){
            return new VoiceUI_Selected_Assistant(this);
        }
    if (vendorId == 0x001D && commandId == 0x0701){
            return getPropertyFromVendorCommand(0x001D, 0x0700);
        }
    if (vendorId == 0x001D && commandId == 0x0702){
            return new VoiceUI_Supported_Assistants(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0918){
            return new LowLatencyMode(this);
        }
    if (vendorId == 0x0495 && commandId == 0x0917){
            return getPropertyFromVendorCommand(0x0495, 0x0918);
        }
    if (vendorId == 0x001D && commandId == 0x0903){
            return new Debug_GetPanicLogInfo(this);
        }
    if (vendorId == 0x001D && commandId == 0x0109){
            return new Core_DataTransferSetup(this);
        }
    if (vendorId == 0x001D && commandId == 0x010A){
            return new Core_DataTransferGet(this);
        }
    if (vendorId == 0x001D && commandId == 0x010C){
            return new Core_GetTransportInfo(this);
        }
    if (vendorId == 0x001D && commandId == 0x0904){
            return new Debug_ErasePanicLog(this);
        }
    if (vendorId == 0x001d && commandId == 0x0100){
            return new Core_Api_Version(this);
        }
    if (vendorId == 0x001d && commandId == 0x0101){
            return new Core_GetSupportedFeatures(this);
        }
    if (vendorId == 0x001d && commandId == 0x0102){
            return new Core_GetSupportedFeaturesNext(this);
        }
    if (vendorId == 0x001d && commandId == 0x010d){
            return new Core_SetTransportParameter(this);
        }
    return nullptr;
}

GAIAPropertyBase *GAIAPropertyManager::getUpgrade_GaiaConnect() {
    return getProperty("\x00\x1D\x0D\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getUpgrade_GaiaDisconnect() {
    return getProperty("\x00\x1D\x0D\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getCore_SerialNumber() {
    return getProperty("\x00\x1D\x01\x03"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getService_FactoryReset() {
    return getProperty("\x04\x95\x01\x40"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getService_HWRevision() {
    return getProperty("\x04\x95\x13\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getService_SystemReleaseVersion() {
    return getProperty("\x04\x95\x13\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getConfig_SetTimer() {
    return getProperty("\x04\x95\x07\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getConfig_GetTimer() {
    return getProperty("\x04\x95\x07\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSetting_AudioPromptMode() {
    return getProperty("\x04\x95\x09\x02"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getAudioPrompt_GetAudioPromptsLanguageVersions() {
    return getProperty("\x04\x95\x09\x09"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getAudioPrompt_GetAvailableAudioPromptsLanguages() {
    return getProperty("\x04\x95\x09\x08"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getBattery_ChargingStatus() {
    return getProperty("\x04\x95\x07\x02"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getUpgrade_Enable() {
    return getProperty("\x04\x95\x03\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getUpgradeFileSize() {
    return getProperty("\x04\x95\x03\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getBattery_Percent() {
    return getProperty("\x04\x95\x07\x03"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPairedDevicesListSize() {
    return getProperty("\x04\x95\x15\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPairedDevicesMaxBTConnections() {
    return getProperty("\x04\x95\x15\x09"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPairedDevicesOwnDeviceIndex() {
    return getProperty("\x04\x95\x15\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPairedDevicesConnectDevice() {
    return getProperty("\x04\x95\x15\x02"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPairedDevicesDeleteEntry() {
    return getProperty("\x04\x95\x15\x05"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPairedDevicesDeleteList() {
    return getProperty("\x04\x95\x15\x06"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPairedDevicesDisconnectDevice() {
    return getProperty("\x04\x95\x15\x03"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPairedDevicesGetConnectionStatus() {
    return getProperty("\x04\x95\x15\x04"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPairedDevicesGetDeviceInfo() {
    return getProperty("\x04\x95\x15\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSound_CodecUsed() {
    return getProperty("\x04\x95\x09\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getFirmwareVersions() {
    return getProperty("\x04\x95\x13\x02"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSetting_AutoLockMode() {
    return getProperty("\x04\x95\x17\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getIsDefaultMMIConfig() {
    return getProperty("\x04\x95\x17\x05"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSetMMIConfig() {
    return getProperty("\x04\x95\x17\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSetDefaultMMIConfig() {
    return getProperty("\x04\x95\x17\x04"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getGetMMIConfig() {
    return getProperty("\x04\x95\x17\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getANC_Status() {
    return getProperty("\x04\x95\x1B\x05"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getANC() {
    return getProperty("\x04\x95\x1B\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getANC_Transparency() {
    return getProperty("\x04\x95\x1B\x03"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getTransparentHearingMode() {
    return getProperty("\x04\x95\x19\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getTransparentHearing_Status() {
    return getProperty("\x04\x95\x19\x05"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getTransparentHearing() {
    return getProperty("\x04\x95\x19\x03"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_qcore() {
    return getProperty("\x00\x1D\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_qEarbud() {
    return getProperty("\x00\x1D\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_qAudioCuration() {
    return getProperty("\x00\x1D\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_qVoiceUI() {
    return getProperty("\x00\x1D\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_qDebug() {
    return getProperty("\x00\x1D\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_qDFU() {
    return getProperty("\x00\x1D\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_core() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_genericAudio() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_userEQ() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getVersions_ModelId() {
    return getProperty("\x04\x95\x13\x06"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_versions() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_deviceManagement() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_mmi() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_transparentHearing() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_ANC() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_battery() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getRegisterNotification_Device() {
    return getProperty("\x04\x95\x01\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSidetoneState() {
    return getProperty("\x04\x95\x09\x06"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSetting_AutoCall() {
    return getProperty("\x04\x95\x09\x0B"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSetting_OnHeadDetection() {
    return getProperty("\x04\x95\x05\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSetting_ComfortCall() {
    return getProperty("\x04\x95\x09\x15"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getSetting_SmartPause() {
    return getProperty("\x04\x95\x09\x0D"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPrimary_Side() {
    return getProperty("\x04\x95\x01\x41"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getBluetoothCompatibilityMode() {
    return getProperty("\x04\x95\x05\x06"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getVoicePrompt_Language() {
    return getProperty("\x04\x95\x09\x07"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getPhysicalDevice_State() {
    return getProperty("\x04\x95\x05\x02"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getStatistics_GetAvailableCategories() {
    return getProperty("\x00\x1D\x19\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getStatistics_GetAllStatisticsInCategory() {
    return getProperty("\x00\x1D\x19\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getStatistics_GetStatisticsValues() {
    return getProperty("\x00\x1D\x19\x02"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getVoiceUI_Selected_Assistant() {
    return getProperty("\x00\x1D\x07\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getVoiceUI_Supported_Assistants() {
    return getProperty("\x00\x1D\x07\x02"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getLowLatencyMode() {
    return getProperty("\x04\x95\x09\x18"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getDebug_GetPanicLogInfo() {
    return getProperty("\x00\x1D\x09\x03"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getCore_DataTransferSetup() {
    return getProperty("\x00\x1D\x01\x09"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getCore_DataTransferGet() {
    return getProperty("\x00\x1D\x01\x0A"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getCore_GetTransportInfo() {
    return getProperty("\x00\x1D\x01\x0C"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getDebug_ErasePanicLog() {
    return getProperty("\x00\x1D\x09\x04"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getCore_Api_Version() {
    return getProperty("\x00\x1d\x01\x00"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getCore_GetSupportedFeatures() {
    return getProperty("\x00\x1d\x01\x01"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getCore_GetSupportedFeaturesNext() {
    return getProperty("\x00\x1d\x01\x02"_ba);
}
GAIAPropertyBase *GAIAPropertyManager::getCore_SetTransportParameter() {
    return getProperty("\x00\x1d\x01\x0d"_ba);
}
