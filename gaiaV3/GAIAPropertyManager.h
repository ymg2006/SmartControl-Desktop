#ifndef QBT_GAIAPROPERTYMANAGER_H
#define QBT_GAIAPROPERTYMANAGER_H

#include <QtCore/QObject>
#include <QtQmlIntegration>
#include "GAIAPropertyBase.h"
#include "GAIAPropertyManagerBase.h"
#include "gaiaV3_export.h"
#include "GAIAPropertyClasses.h"

class GAIA_V3_EXPORT GAIAPropertyManager: public GAIAPropertyManagerBase {
    Q_OBJECT

    Q_PROPERTY(GAIAPropertyBase* Upgrade_GaiaConnect READ getUpgrade_GaiaConnect NOTIFY Upgrade_GaiaConnectChanged)
    Q_PROPERTY(GAIAPropertyBase* Upgrade_GaiaDisconnect READ getUpgrade_GaiaDisconnect NOTIFY Upgrade_GaiaDisconnectChanged)
    Q_PROPERTY(GAIAPropertyBase* Core_SerialNumber READ getCore_SerialNumber NOTIFY Core_SerialNumberChanged)
    Q_PROPERTY(GAIAPropertyBase* Service_FactoryReset READ getService_FactoryReset NOTIFY Service_FactoryResetChanged)
    Q_PROPERTY(GAIAPropertyBase* Service_HWRevision READ getService_HWRevision NOTIFY Service_HWRevisionChanged)
    Q_PROPERTY(GAIAPropertyBase* Service_SystemReleaseVersion READ getService_SystemReleaseVersion NOTIFY Service_SystemReleaseVersionChanged)
    Q_PROPERTY(GAIAPropertyBase* Config_SetTimer READ getConfig_SetTimer NOTIFY Config_SetTimerChanged)
    Q_PROPERTY(GAIAPropertyBase* Config_GetTimer READ getConfig_GetTimer NOTIFY Config_GetTimerChanged)
    Q_PROPERTY(GAIAPropertyBase* Setting_AudioPromptMode READ getSetting_AudioPromptMode NOTIFY Setting_AudioPromptModeChanged)
    Q_PROPERTY(GAIAPropertyBase* AudioPrompt_GetAudioPromptsLanguageVersions READ getAudioPrompt_GetAudioPromptsLanguageVersions NOTIFY AudioPrompt_GetAudioPromptsLanguageVersionsChanged)
    Q_PROPERTY(GAIAPropertyBase* AudioPrompt_GetAvailableAudioPromptsLanguages READ getAudioPrompt_GetAvailableAudioPromptsLanguages NOTIFY AudioPrompt_GetAvailableAudioPromptsLanguagesChanged)
    Q_PROPERTY(GAIAPropertyBase* Battery_ChargingStatus READ getBattery_ChargingStatus NOTIFY Battery_ChargingStatusChanged)
    Q_PROPERTY(GAIAPropertyBase* Upgrade_Enable READ getUpgrade_Enable NOTIFY Upgrade_EnableChanged)
    Q_PROPERTY(GAIAPropertyBase* UpgradeFileSize READ getUpgradeFileSize NOTIFY UpgradeFileSizeChanged)
    Q_PROPERTY(GAIAPropertyBase* Battery_Percent READ getBattery_Percent NOTIFY Battery_PercentChanged)
    Q_PROPERTY(GAIAPropertyBase* PairedDevicesListSize READ getPairedDevicesListSize NOTIFY PairedDevicesListSizeChanged)
    Q_PROPERTY(GAIAPropertyBase* PairedDevicesMaxBTConnections READ getPairedDevicesMaxBTConnections NOTIFY PairedDevicesMaxBTConnectionsChanged)
    Q_PROPERTY(GAIAPropertyBase* PairedDevicesOwnDeviceIndex READ getPairedDevicesOwnDeviceIndex NOTIFY PairedDevicesOwnDeviceIndexChanged)
    Q_PROPERTY(GAIAPropertyBase* PairedDevicesConnectDevice READ getPairedDevicesConnectDevice NOTIFY PairedDevicesConnectDeviceChanged)
    Q_PROPERTY(GAIAPropertyBase* PairedDevicesDeleteEntry READ getPairedDevicesDeleteEntry NOTIFY PairedDevicesDeleteEntryChanged)
    Q_PROPERTY(GAIAPropertyBase* PairedDevicesDeleteList READ getPairedDevicesDeleteList NOTIFY PairedDevicesDeleteListChanged)
    Q_PROPERTY(GAIAPropertyBase* PairedDevicesDisconnectDevice READ getPairedDevicesDisconnectDevice NOTIFY PairedDevicesDisconnectDeviceChanged)
    Q_PROPERTY(GAIAPropertyBase* PairedDevicesGetConnectionStatus READ getPairedDevicesGetConnectionStatus NOTIFY PairedDevicesGetConnectionStatusChanged)
    Q_PROPERTY(GAIAPropertyBase* PairedDevicesGetDeviceInfo READ getPairedDevicesGetDeviceInfo NOTIFY PairedDevicesGetDeviceInfoChanged)
    Q_PROPERTY(GAIAPropertyBase* Sound_CodecUsed READ getSound_CodecUsed NOTIFY Sound_CodecUsedChanged)
    Q_PROPERTY(GAIAPropertyBase* FirmwareVersions READ getFirmwareVersions NOTIFY FirmwareVersionsChanged)
    Q_PROPERTY(GAIAPropertyBase* Setting_AutoLockMode READ getSetting_AutoLockMode NOTIFY Setting_AutoLockModeChanged)
    Q_PROPERTY(GAIAPropertyBase* IsDefaultMMIConfig READ getIsDefaultMMIConfig NOTIFY IsDefaultMMIConfigChanged)
    Q_PROPERTY(GAIAPropertyBase* SetMMIConfig READ getSetMMIConfig NOTIFY SetMMIConfigChanged)
    Q_PROPERTY(GAIAPropertyBase* SetDefaultMMIConfig READ getSetDefaultMMIConfig NOTIFY SetDefaultMMIConfigChanged)
    Q_PROPERTY(GAIAPropertyBase* GetMMIConfig READ getGetMMIConfig NOTIFY GetMMIConfigChanged)
    Q_PROPERTY(GAIAPropertyBase* ANC_Status READ getANC_Status NOTIFY ANC_StatusChanged)
    Q_PROPERTY(GAIAPropertyBase* ANC READ getANC NOTIFY ANCChanged)
    Q_PROPERTY(GAIAPropertyBase* ANC_Transparency READ getANC_Transparency NOTIFY ANC_TransparencyChanged)
    Q_PROPERTY(GAIAPropertyBase* TransparentHearingMode READ getTransparentHearingMode NOTIFY TransparentHearingModeChanged)
    Q_PROPERTY(GAIAPropertyBase* TransparentHearing_Status READ getTransparentHearing_Status NOTIFY TransparentHearing_StatusChanged)
    Q_PROPERTY(GAIAPropertyBase* TransparentHearing READ getTransparentHearing NOTIFY TransparentHearingChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_qcore READ getRegisterNotification_qcore NOTIFY RegisterNotification_qcoreChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_qEarbud READ getRegisterNotification_qEarbud NOTIFY RegisterNotification_qEarbudChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_qAudioCuration READ getRegisterNotification_qAudioCuration NOTIFY RegisterNotification_qAudioCurationChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_qVoiceUI READ getRegisterNotification_qVoiceUI NOTIFY RegisterNotification_qVoiceUIChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_qDebug READ getRegisterNotification_qDebug NOTIFY RegisterNotification_qDebugChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_qDFU READ getRegisterNotification_qDFU NOTIFY RegisterNotification_qDFUChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_core READ getRegisterNotification_core NOTIFY RegisterNotification_coreChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_genericAudio READ getRegisterNotification_genericAudio NOTIFY RegisterNotification_genericAudioChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_userEQ READ getRegisterNotification_userEQ NOTIFY RegisterNotification_userEQChanged)
    Q_PROPERTY(GAIAPropertyBase* Versions_ModelId READ getVersions_ModelId NOTIFY Versions_ModelIdChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_versions READ getRegisterNotification_versions NOTIFY RegisterNotification_versionsChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_deviceManagement READ getRegisterNotification_deviceManagement NOTIFY RegisterNotification_deviceManagementChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_mmi READ getRegisterNotification_mmi NOTIFY RegisterNotification_mmiChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_transparentHearing READ getRegisterNotification_transparentHearing NOTIFY RegisterNotification_transparentHearingChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_ANC READ getRegisterNotification_ANC NOTIFY RegisterNotification_ANCChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_battery READ getRegisterNotification_battery NOTIFY RegisterNotification_batteryChanged)
    Q_PROPERTY(GAIAPropertyBase* RegisterNotification_Device READ getRegisterNotification_Device NOTIFY RegisterNotification_DeviceChanged)
    Q_PROPERTY(GAIAPropertyBase* SidetoneState READ getSidetoneState NOTIFY SidetoneStateChanged)
    Q_PROPERTY(GAIAPropertyBase* Setting_AutoCall READ getSetting_AutoCall NOTIFY Setting_AutoCallChanged)
    Q_PROPERTY(GAIAPropertyBase* Setting_OnHeadDetection READ getSetting_OnHeadDetection NOTIFY Setting_OnHeadDetectionChanged)
    Q_PROPERTY(GAIAPropertyBase* Setting_ComfortCall READ getSetting_ComfortCall NOTIFY Setting_ComfortCallChanged)
    Q_PROPERTY(GAIAPropertyBase* Setting_SmartPause READ getSetting_SmartPause NOTIFY Setting_SmartPauseChanged)
    Q_PROPERTY(GAIAPropertyBase* Primary_Side READ getPrimary_Side NOTIFY Primary_SideChanged)
    Q_PROPERTY(GAIAPropertyBase* BluetoothCompatibilityMode READ getBluetoothCompatibilityMode NOTIFY BluetoothCompatibilityModeChanged)
    Q_PROPERTY(GAIAPropertyBase* VoicePrompt_Language READ getVoicePrompt_Language NOTIFY VoicePrompt_LanguageChanged)
    Q_PROPERTY(GAIAPropertyBase* PhysicalDevice_State READ getPhysicalDevice_State NOTIFY PhysicalDevice_StateChanged)
    Q_PROPERTY(GAIAPropertyBase* Statistics_GetAvailableCategories READ getStatistics_GetAvailableCategories NOTIFY Statistics_GetAvailableCategoriesChanged)
    Q_PROPERTY(GAIAPropertyBase* Statistics_GetAllStatisticsInCategory READ getStatistics_GetAllStatisticsInCategory NOTIFY Statistics_GetAllStatisticsInCategoryChanged)
    Q_PROPERTY(GAIAPropertyBase* Statistics_GetStatisticsValues READ getStatistics_GetStatisticsValues NOTIFY Statistics_GetStatisticsValuesChanged)
    Q_PROPERTY(GAIAPropertyBase* VoiceUI_Selected_Assistant READ getVoiceUI_Selected_Assistant NOTIFY VoiceUI_Selected_AssistantChanged)
    Q_PROPERTY(GAIAPropertyBase* VoiceUI_Supported_Assistants READ getVoiceUI_Supported_Assistants NOTIFY VoiceUI_Supported_AssistantsChanged)
    Q_PROPERTY(GAIAPropertyBase* LowLatencyMode READ getLowLatencyMode NOTIFY LowLatencyModeChanged)
    Q_PROPERTY(GAIAPropertyBase* Debug_GetPanicLogInfo READ getDebug_GetPanicLogInfo NOTIFY Debug_GetPanicLogInfoChanged)
    Q_PROPERTY(GAIAPropertyBase* Core_DataTransferSetup READ getCore_DataTransferSetup NOTIFY Core_DataTransferSetupChanged)
    Q_PROPERTY(GAIAPropertyBase* Core_DataTransferGet READ getCore_DataTransferGet NOTIFY Core_DataTransferGetChanged)
    Q_PROPERTY(GAIAPropertyBase* Core_GetTransportInfo READ getCore_GetTransportInfo NOTIFY Core_GetTransportInfoChanged)
    Q_PROPERTY(GAIAPropertyBase* Debug_ErasePanicLog READ getDebug_ErasePanicLog NOTIFY Debug_ErasePanicLogChanged)
    Q_PROPERTY(GAIAPropertyBase* Core_Api_Version READ getCore_Api_Version NOTIFY Core_Api_VersionChanged)
    Q_PROPERTY(GAIAPropertyBase* Core_GetSupportedFeatures READ getCore_GetSupportedFeatures NOTIFY Core_GetSupportedFeaturesChanged)
    Q_PROPERTY(GAIAPropertyBase* Core_GetSupportedFeaturesNext READ getCore_GetSupportedFeaturesNext NOTIFY Core_GetSupportedFeaturesNextChanged)
    Q_PROPERTY(GAIAPropertyBase* Core_SetTransportParameter READ getCore_SetTransportParameter NOTIFY Core_SetTransportParameterChanged)

public:
    GAIAPropertyManager(QObject *parent = nullptr);
    GAIAPropertyBase *getPropertyFromVendorCommand(const quint16 &vendorId, const quint16 &commandId) override;

public slots:

    GAIAPropertyBase* getUpgrade_GaiaConnect();
    GAIAPropertyBase* getUpgrade_GaiaDisconnect();
    GAIAPropertyBase* getCore_SerialNumber();
    GAIAPropertyBase* getService_FactoryReset();
    GAIAPropertyBase* getService_HWRevision();
    GAIAPropertyBase* getService_SystemReleaseVersion();
    GAIAPropertyBase* getConfig_SetTimer();
    GAIAPropertyBase* getConfig_GetTimer();
    GAIAPropertyBase* getSetting_AudioPromptMode();
    GAIAPropertyBase* getAudioPrompt_GetAudioPromptsLanguageVersions();
    GAIAPropertyBase* getAudioPrompt_GetAvailableAudioPromptsLanguages();
    GAIAPropertyBase* getBattery_ChargingStatus();
    GAIAPropertyBase* getUpgrade_Enable();
    GAIAPropertyBase* getUpgradeFileSize();
    GAIAPropertyBase* getBattery_Percent();
    GAIAPropertyBase* getPairedDevicesListSize();
    GAIAPropertyBase* getPairedDevicesMaxBTConnections();
    GAIAPropertyBase* getPairedDevicesOwnDeviceIndex();
    GAIAPropertyBase* getPairedDevicesConnectDevice();
    GAIAPropertyBase* getPairedDevicesDeleteEntry();
    GAIAPropertyBase* getPairedDevicesDeleteList();
    GAIAPropertyBase* getPairedDevicesDisconnectDevice();
    GAIAPropertyBase* getPairedDevicesGetConnectionStatus();
    GAIAPropertyBase* getPairedDevicesGetDeviceInfo();
    GAIAPropertyBase* getSound_CodecUsed();
    GAIAPropertyBase* getFirmwareVersions();
    GAIAPropertyBase* getSetting_AutoLockMode();
    GAIAPropertyBase* getIsDefaultMMIConfig();
    GAIAPropertyBase* getSetMMIConfig();
    GAIAPropertyBase* getSetDefaultMMIConfig();
    GAIAPropertyBase* getGetMMIConfig();
    GAIAPropertyBase* getANC_Status();
    GAIAPropertyBase* getANC();
    GAIAPropertyBase* getANC_Transparency();
    GAIAPropertyBase* getTransparentHearingMode();
    GAIAPropertyBase* getTransparentHearing_Status();
    GAIAPropertyBase* getTransparentHearing();
    GAIAPropertyBase* getRegisterNotification_qcore();
    GAIAPropertyBase* getRegisterNotification_qEarbud();
    GAIAPropertyBase* getRegisterNotification_qAudioCuration();
    GAIAPropertyBase* getRegisterNotification_qVoiceUI();
    GAIAPropertyBase* getRegisterNotification_qDebug();
    GAIAPropertyBase* getRegisterNotification_qDFU();
    GAIAPropertyBase* getRegisterNotification_core();
    GAIAPropertyBase* getRegisterNotification_genericAudio();
    GAIAPropertyBase* getRegisterNotification_userEQ();
    GAIAPropertyBase* getVersions_ModelId();
    GAIAPropertyBase* getRegisterNotification_versions();
    GAIAPropertyBase* getRegisterNotification_deviceManagement();
    GAIAPropertyBase* getRegisterNotification_mmi();
    GAIAPropertyBase* getRegisterNotification_transparentHearing();
    GAIAPropertyBase* getRegisterNotification_ANC();
    GAIAPropertyBase* getRegisterNotification_battery();
    GAIAPropertyBase* getRegisterNotification_Device();
    GAIAPropertyBase* getSidetoneState();
    GAIAPropertyBase* getSetting_AutoCall();
    GAIAPropertyBase* getSetting_OnHeadDetection();
    GAIAPropertyBase* getSetting_ComfortCall();
    GAIAPropertyBase* getSetting_SmartPause();
    GAIAPropertyBase* getPrimary_Side();
    GAIAPropertyBase* getBluetoothCompatibilityMode();
    GAIAPropertyBase* getVoicePrompt_Language();
    GAIAPropertyBase* getPhysicalDevice_State();
    GAIAPropertyBase* getStatistics_GetAvailableCategories();
    GAIAPropertyBase* getStatistics_GetAllStatisticsInCategory();
    GAIAPropertyBase* getStatistics_GetStatisticsValues();
    GAIAPropertyBase* getVoiceUI_Selected_Assistant();
    GAIAPropertyBase* getVoiceUI_Supported_Assistants();
    GAIAPropertyBase* getLowLatencyMode();
    GAIAPropertyBase* getDebug_GetPanicLogInfo();
    GAIAPropertyBase* getCore_DataTransferSetup();
    GAIAPropertyBase* getCore_DataTransferGet();
    GAIAPropertyBase* getCore_GetTransportInfo();
    GAIAPropertyBase* getDebug_ErasePanicLog();
    GAIAPropertyBase* getCore_Api_Version();
    GAIAPropertyBase* getCore_GetSupportedFeatures();
    GAIAPropertyBase* getCore_GetSupportedFeaturesNext();
    GAIAPropertyBase* getCore_SetTransportParameter();

signals:

    void Upgrade_GaiaConnectChanged();
    void Upgrade_GaiaDisconnectChanged();
    void Core_SerialNumberChanged();
    void Service_FactoryResetChanged();
    void Service_HWRevisionChanged();
    void Service_SystemReleaseVersionChanged();
    void Config_SetTimerChanged();
    void Config_GetTimerChanged();
    void Setting_AudioPromptModeChanged();
    void AudioPrompt_GetAudioPromptsLanguageVersionsChanged();
    void AudioPrompt_GetAvailableAudioPromptsLanguagesChanged();
    void Battery_ChargingStatusChanged();
    void Upgrade_EnableChanged();
    void UpgradeFileSizeChanged();
    void Battery_PercentChanged();
    void PairedDevicesListSizeChanged();
    void PairedDevicesMaxBTConnectionsChanged();
    void PairedDevicesOwnDeviceIndexChanged();
    void PairedDevicesConnectDeviceChanged();
    void PairedDevicesDeleteEntryChanged();
    void PairedDevicesDeleteListChanged();
    void PairedDevicesDisconnectDeviceChanged();
    void PairedDevicesGetConnectionStatusChanged();
    void PairedDevicesGetDeviceInfoChanged();
    void Sound_CodecUsedChanged();
    void FirmwareVersionsChanged();
    void Setting_AutoLockModeChanged();
    void IsDefaultMMIConfigChanged();
    void SetMMIConfigChanged();
    void SetDefaultMMIConfigChanged();
    void GetMMIConfigChanged();
    void ANC_StatusChanged();
    void ANCChanged();
    void ANC_TransparencyChanged();
    void TransparentHearingModeChanged();
    void TransparentHearing_StatusChanged();
    void TransparentHearingChanged();
    void RegisterNotification_qcoreChanged();
    void RegisterNotification_qEarbudChanged();
    void RegisterNotification_qAudioCurationChanged();
    void RegisterNotification_qVoiceUIChanged();
    void RegisterNotification_qDebugChanged();
    void RegisterNotification_qDFUChanged();
    void RegisterNotification_coreChanged();
    void RegisterNotification_genericAudioChanged();
    void RegisterNotification_userEQChanged();
    void Versions_ModelIdChanged();
    void RegisterNotification_versionsChanged();
    void RegisterNotification_deviceManagementChanged();
    void RegisterNotification_mmiChanged();
    void RegisterNotification_transparentHearingChanged();
    void RegisterNotification_ANCChanged();
    void RegisterNotification_batteryChanged();
    void RegisterNotification_DeviceChanged();
    void SidetoneStateChanged();
    void Setting_AutoCallChanged();
    void Setting_OnHeadDetectionChanged();
    void Setting_ComfortCallChanged();
    void Setting_SmartPauseChanged();
    void Primary_SideChanged();
    void BluetoothCompatibilityModeChanged();
    void VoicePrompt_LanguageChanged();
    void PhysicalDevice_StateChanged();
    void Statistics_GetAvailableCategoriesChanged();
    void Statistics_GetAllStatisticsInCategoryChanged();
    void Statistics_GetStatisticsValuesChanged();
    void VoiceUI_Selected_AssistantChanged();
    void VoiceUI_Supported_AssistantsChanged();
    void LowLatencyModeChanged();
    void Debug_GetPanicLogInfoChanged();
    void Core_DataTransferSetupChanged();
    void Core_DataTransferGetChanged();
    void Core_GetTransportInfoChanged();
    void Debug_ErasePanicLogChanged();
    void Core_Api_VersionChanged();
    void Core_GetSupportedFeaturesChanged();
    void Core_GetSupportedFeaturesNextChanged();
    void Core_SetTransportParameterChanged();

};

#endif //QBT_GAIAPROPERTYMANAGER_H
