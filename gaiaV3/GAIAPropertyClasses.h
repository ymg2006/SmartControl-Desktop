#ifndef QBT_GAIAPROPERTYCLASSES_H
#define QBT_GAIAPROPERTYCLASSES_H

#include "GAIAPropertyBase.h"
#include "gaiaV3_export.h"
#include <QObject>
#include <QtQmlIntegration>


class GAIA_V3_EXPORT Upgrade_Abort: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_Abort(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_CommitCfm: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_CommitCfm(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_ErrorConfirmation: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_ErrorConfirmation(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_GaiaConnect: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_GaiaConnect(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_GaiaData: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_GaiaData(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_GaiaDisconnect: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_GaiaDisconnect(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_GaiaIsValidationDone: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_GaiaIsValidationDone(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_GaiaStart: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_GaiaStart(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_GaiaStartData: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_GaiaStartData(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_GaiaSync: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_GaiaSync(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_ProceedToCommit: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_ProceedToCommit(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_TransferComplete_Trigger: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_TransferComplete_Trigger(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Core_SerialNumber: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Core_SerialNumber(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Service_FactoryReset: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Service_FactoryReset(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Service_HWRevision: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Service_HWRevision(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Service_SystemReleaseVersion: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Service_SystemReleaseVersion(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Config_SetTimer: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Config_SetTimer(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Config_GetTimer: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Config_GetTimer(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Setting_AudioPromptMode: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Setting_AudioPromptMode(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT AudioPrompt_GetAudioPromptsLanguageVersions: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AudioPrompt_GetAudioPromptsLanguageVersions(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT AudioPrompt_GetAvailableAudioPromptsLanguages: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AudioPrompt_GetAvailableAudioPromptsLanguages(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Battery_ChargingStatus: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Battery_ChargingStatus(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Upgrade_Enable: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Upgrade_Enable(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT UpgradeFileSize: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit UpgradeFileSize(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Battery_Percent: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Battery_Percent(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PairedDevicesListSize: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PairedDevicesListSize(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PairedDevicesMaxBTConnections: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PairedDevicesMaxBTConnections(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PairedDevicesOwnDeviceIndex: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PairedDevicesOwnDeviceIndex(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PairedDevicesConnectDevice: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PairedDevicesConnectDevice(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PairedDevicesDeleteEntry: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PairedDevicesDeleteEntry(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PairedDevicesDeleteList: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PairedDevicesDeleteList(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PairedDevicesDisconnectDevice: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PairedDevicesDisconnectDevice(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PairedDevicesGetConnectionStatus: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PairedDevicesGetConnectionStatus(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PairedDevicesGetDeviceInfo: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PairedDevicesGetDeviceInfo(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Sound_CodecUsed: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Sound_CodecUsed(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT FirmwareVersions: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit FirmwareVersions(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Setting_AutoLockMode: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Setting_AutoLockMode(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT IsDefaultMMIConfig: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit IsDefaultMMIConfig(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT SetMMIConfig: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit SetMMIConfig(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT SetDefaultMMIConfig: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit SetDefaultMMIConfig(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT GetMMIConfig: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit GetMMIConfig(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT ANC_Status: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ANC_Status(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT ANC: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ANC(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT ANC_Transparency: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ANC_Transparency(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT TransparentHearingMode: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit TransparentHearingMode(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT TransparentHearing_Status: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit TransparentHearing_Status(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT TransparentHearing: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit TransparentHearing(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_qcore: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_qcore(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_qEarbud: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_qEarbud(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_qAudioCuration: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_qAudioCuration(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_qVoiceUI: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_qVoiceUI(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_qDebug: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_qDebug(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_qDFU: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_qDFU(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_core: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_core(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_genericAudio: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_genericAudio(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_userEQ: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_userEQ(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Versions_ModelId: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Versions_ModelId(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_versions: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_versions(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_deviceManagement: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_deviceManagement(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_mmi: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_mmi(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_transparentHearing: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_transparentHearing(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_ANC: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_ANC(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_battery: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_battery(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT RegisterNotification_Device: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit RegisterNotification_Device(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT SidetoneState: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit SidetoneState(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Setting_AutoCall: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Setting_AutoCall(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Setting_OnHeadDetection: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Setting_OnHeadDetection(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Setting_ComfortCall: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Setting_ComfortCall(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Setting_SmartPause: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Setting_SmartPause(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Primary_Side: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Primary_Side(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT BluetoothCompatibilityMode: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit BluetoothCompatibilityMode(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT VoicePrompt_Language: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit VoicePrompt_Language(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT PhysicalDevice_State: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PhysicalDevice_State(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Statistics_GetAvailableCategories: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Statistics_GetAvailableCategories(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Statistics_GetAllStatisticsInCategory: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Statistics_GetAllStatisticsInCategory(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Statistics_GetStatisticsValues: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Statistics_GetStatisticsValues(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT VoiceUI_Selected_Assistant: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit VoiceUI_Selected_Assistant(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT VoiceUI_Supported_Assistants: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit VoiceUI_Supported_Assistants(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT LowLatencyMode: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit LowLatencyMode(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Debug_GetPanicLogInfo: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Debug_GetPanicLogInfo(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Core_DataTransferSetup: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Core_DataTransferSetup(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Core_DataTransferGet: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Core_DataTransferGet(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Core_GetTransportInfo: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Core_GetTransportInfo(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Debug_ErasePanicLog: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Debug_ErasePanicLog(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Core_Api_Version: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Core_Api_Version(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Core_GetSupportedFeatures: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Core_GetSupportedFeatures(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Core_GetSupportedFeaturesNext: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Core_GetSupportedFeaturesNext(QObject *parent = nullptr);
};

class GAIA_V3_EXPORT Core_SetTransportParameter: public GAIAPropertyBase {
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Core_SetTransportParameter(QObject *parent = nullptr);
};

#endif
