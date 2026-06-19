import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore
import QtQuick.LocalStorage

Dialog {
    id: root
    anchors.centerIn: parent
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    focus: true
    title: "Settings"
    width: Math.min(parent ? parent.width - 96 : 760, 760)
    leftPadding: 28
    rightPadding: 28
    topPadding: 20
    bottomPadding: 16
    standardButtons: Dialog.Close
    modal: true
    Overlay.modal: Rectangle {
        color: Qt.alpha(root.palette.shadow, 0.5)
    }

    enter: Transition {
        NumberAnimation {
            from: 0.0
            property: "opacity"
            to: 1.0
        }
    }
    exit: Transition {
        NumberAnimation {
            from: 1.0
            property: "opacity"
            to: 0.0
        }
    }

    ColumnLayout{
        anchors.fill: parent
        spacing: 14

        ColumnLayout{
            spacing: 5
            Label {
                text: "Theme"
                color: root.palette.windowText
            }
            ComboBox {
                id: themeCombo
                Layout.preferredWidth: 180
                model: ["System", "Light", "Dark"]
                currentIndex: UiHelper.themeModeToIndex(UiHelper.themeMode)
                onActivated: function(index) {
                    UiHelper.setThemeMode(UiHelper.themeIndexToMode(index));
                }

                Connections {
                    target: UiHelper
                    function onThemeModeChanged() {
                        themeCombo.currentIndex = UiHelper.themeModeToIndex(UiHelper.themeMode);
                    }
                }
            }
            Label {
                text: "Choose System to follow the operating system, or force Light/Dark mode."
                Layout.leftMargin: 28
                Layout.rightMargin: 0
                Layout.fillWidth: true
                font.pointSize: 10
                color: root.palette.windowText
                wrapMode: Text.WordWrap
            }
        }


        ColumnLayout{
            spacing: 6
            Switch {
                id: autostartSwitch
                text: "Start with Windows"
                checked: appController.autostartEnabled
                onToggled: appController.autostartEnabled = checked
            }
            Label {
                text: "Launch Smart Control Desktop automatically when Windows starts. It starts minimized to the tray."
                Layout.leftMargin: 28
                Layout.fillWidth: true
                font.pointSize: 10
                color: root.palette.windowText
                wrapMode: Text.WordWrap
            }
        }

        ColumnLayout{
            spacing: 6
            Switch {
                id: traySwitch
                text: "Minimize to tray when closing"
                checked: appController.minimizeToTray
                enabled: appController.trayAvailable
                onToggled: appController.minimizeToTray = checked
            }
            Label {
                text: appController.trayAvailable
                      ? "Closing the window hides it in the system tray. Use the tray icon to restore or quit."
                      : "System tray is not available in this Windows session."
                Layout.leftMargin: 28
                Layout.fillWidth: true
                font.pointSize: 10
                color: root.palette.windowText
                wrapMode: Text.WordWrap
            }
        }

        ColumnLayout{
            spacing: 5
            Switch {
                id: debugSwitch
                text: "Debug packets"
                checked: settings.saveDebug
            }
            Label {
                text: `Save packet debug log into the <a href='file://${logFile}'>file.</a>`
                Layout.leftMargin: 28
                Layout.rightMargin: 0
                Layout.fillWidth: true
                font.pointSize: 10
                color: root.palette.windowText
                wrapMode: Text.WordWrap
                textFormat: Text.RichText
                onLinkActivated: function(url){
                    Qt.openUrlExternally(url);
                }
            }
        }
    }

    Settings {
        id: settings
        property alias saveDebug: debugSwitch.checked
    }
    DatabaseStorage {
        id: db
    }
}