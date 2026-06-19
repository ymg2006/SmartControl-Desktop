import QtQuick.Controls
import QtQuick
import btuicontrols
import gaiaV3

import QtCore
import QtQuick.Layouts

import QtQuick

ApplicationWindow {
    id: mainWindow
    width: 1080
    height: 720
    minimumWidth: 720
    minimumHeight: 520
    title: "Smart Control Desktop"
    visible: !appController.startMinimized
    color: palette.window

    onClosing: function(close) {
        if (appController.minimizeToTray && appController.trayAvailable && !appController.quitting) {
            close.accepted = false;
            mainWindow.hide();
            appController.showTrayMessageOnce();
        }
    }

    palette.window: UiHelper.windowColor
    palette.windowText: UiHelper.textColor
    palette.base: UiHelper.cardColor
    palette.alternateBase: UiHelper.alternateBaseColor
    palette.text: UiHelper.textColor
    palette.button: UiHelper.buttonColor
    palette.buttonText: UiHelper.textColor
    palette.highlight: UiHelper.highlightColor
    palette.highlightedText: UiHelper.highlightedTextColor
    palette.mid: UiHelper.borderColor
    palette.shadow: UiHelper.shadowColor

    header: ToolBar {
        height: 44
        background: Rectangle { color: UiHelper.cardColor }
        RowLayout {
            anchors.fill: parent
            spacing: 5
            ToolButton {
                flat: true
                visible: stackView.currentIndex > 0;
                icon.source: "qrc:/icons/arrow.left.svg"
                icon.color: mainWindow.palette.windowText
                onClicked: stackView.currentIndex -= 1;
            }
            Item {
                Layout.fillWidth: true
            }
            ToolButton {
                flat: true
                text: UiHelper.isDarkTheme ? "☀ Light" : "☾ Dark"
                onClicked: UiHelper.toggleTheme();
                ToolTip.visible: hovered
                ToolTip.text: UiHelper.isDarkTheme ? "Switch to light theme" : "Switch to dark theme"
            }
            ToolButton {
                flat: true
                icon.source: "qrc:/icons/gearshape.svg"
                icon.color: mainWindow.palette.windowText
                onClicked: settingsDialog.open();
            }
            ToolButton {
                flat: true
                icon.source: "qrc:/icons/questionmark.circle.svg"
                icon.color: mainWindow.palette.windowText
                onClicked: aboutDialog.open();
            }
        }
    }


    Connections {
        target: appController
        function onShowWindowRequested() {
            mainWindow.show();
            mainWindow.raise();
            mainWindow.requestActivate();
        }
    }

    Connections {
        target: GAIARfcommClient
        function onIsConnectedChanged(){
            stackView.currentIndex = GAIARfcommClient.isConnected ? 1 : 0;
        }
    }

    StackLayout {
        id: stackView

        anchors.fill: parent

        currentIndex: GAIARfcommClient.isConnected ? 1 : 0

        onCurrentIndexChanged: {
            pageLoader.source = stackView.currentIndex === 1 ? "qrc:/qt/qml/btuicontrols/DevicePage.qml" : "";
        }

        DeviceListPage{
            id: deviceListPage
        }
        Loader {
            id: pageLoader
        }
    }

    AboutDialog {
        id: aboutDialog
    }
    SettingsDialog {
        id: settingsDialog
        onClosed: {
            deviceListPage.loadDevices();
        }
    }

    Settings {
        property alias x: mainWindow.x
        property alias y: mainWindow.y
        property alias width: mainWindow.width
        property alias height: mainWindow.height
    }

    Component.onCompleted: {
        if (appController.startMinimized)
            appController.showTrayMessageOnce();
        if (mainWindow.width < mainWindow.minimumWidth)
            mainWindow.width = mainWindow.minimumWidth;
        if (mainWindow.height < mainWindow.minimumHeight)
            mainWindow.height = mainWindow.minimumHeight;
        pageLoader.source = stackView.currentIndex === 1 ? "qrc:/qt/qml/btuicontrols/DevicePage.qml" : "";
    }
}