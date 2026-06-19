import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import btuicontrols
import gaiaV3

Page {
    id: devicePage
    background: Rectangle { color: UiHelper.windowColor }

    readonly property int pagePadding: width < 860 ? 16 : 24
    readonly property int contentMaxWidth: 1180
    readonly property bool twoColumns: width >= 980

    ScrollView {
        id: scrollView
        anchors.fill: parent
        clip: true
        contentWidth: availableWidth
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        Item {
            width: scrollView.availableWidth
            implicitHeight: contentColumn.implicitHeight + devicePage.pagePadding * 2

            ColumnLayout {
                id: contentColumn
                width: Math.min(parent.width - devicePage.pagePadding * 2, devicePage.contentMaxWidth)
                x: Math.max(devicePage.pagePadding, (parent.width - width) / 2)
                y: devicePage.pagePadding
                spacing: 18

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 18
                    visible: devicePage.twoColumns
                    Layout.alignment: Qt.AlignTop

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignTop
                        spacing: 18

                        DeviceHeaderBar {
                            Layout.fillWidth: true
                        }

                        DeviceInfoCard {
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                        }

                        OnHeadSettingsCard {
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                        }

                        ConnectedDevicesCard {
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignTop
                        spacing: 18

                        ANCCard2 {
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                        }

                        CallSettingsCard {
                            Layout.fillWidth: true
                            Layout.preferredHeight: implicitHeight
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 18
                    visible: !devicePage.twoColumns

                    DeviceHeaderBar {
                        Layout.fillWidth: true
                    }

                    DeviceInfoCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: implicitHeight
                    }

                    ANCCard2 {
                        Layout.fillWidth: true
                        Layout.preferredHeight: implicitHeight
                    }

                    OnHeadSettingsCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: implicitHeight
                    }

                    CallSettingsCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: implicitHeight
                    }

                    ConnectedDevicesCard {
                        Layout.fillWidth: true
                        Layout.preferredHeight: implicitHeight
                    }
                }
            }
        }
    }

    component DeviceHeaderBar: Rectangle {
        implicitHeight: 86
        radius: 20
        color: UiHelper.cardColor
        border.color: UiHelper.borderColor
        clip: true

        RowLayout {
            anchors.fill: parent
            anchors.margins: 18
            spacing: 14

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4

                Label {
                    text: GAIARfcommClient.deviceName !== "" ? GAIARfcommClient.deviceName : "Sennheiser headset"
                    font.pixelSize: 26
                    font.bold: true
                    color: UiHelper.textColor
                    elide: Text.ElideRight
                    Layout.fillWidth: true
                }

                Label {
                    text: GAIARfcommClient.deviceAddress !== "" ? GAIARfcommClient.deviceAddress : "Windows RFCOMM control channel"
                    font.pixelSize: 13
                    color: UiHelper.mutedTextColor
                    elide: Text.ElideRight
                    Layout.fillWidth: true
                }
            }

            Rectangle {
                Layout.preferredWidth: connectedLabel.implicitWidth + 24
                Layout.preferredHeight: 32
                Layout.alignment: Qt.AlignVCenter
                radius: 16
                color: GAIARfcommClient.isConnected ? UiHelper.connectedBadgeColor : UiHelper.offlineBadgeColor

                Label {
                    id: connectedLabel
                    anchors.centerIn: parent
                    text: GAIARfcommClient.isConnected ? "Connected" : "Disconnected"
                    font.pixelSize: 12
                    font.bold: true
                    color: GAIARfcommClient.isConnected ? UiHelper.connectedBadgeTextColor : UiHelper.badgeTextColor
                }
            }
        }
    }
}
