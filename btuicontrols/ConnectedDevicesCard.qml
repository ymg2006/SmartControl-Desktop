import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Rectangle {
    id: root
    width: 420
    implicitHeight: Math.min(320, Math.max(172, contentColumn.implicitHeight + 28))
    height: implicitHeight
    radius: 20
    border.color: root.palette.mid
    clip: true
    color: root.palette.base

    ConnectedDevicesCardHelper {
        id: helper
    }

    Image {
        id: linkIcon
        source: "qrc:/icons/display.2.svg"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 14
        anchors.topMargin: 14
        width: 32
        fillMode: Image.PreserveAspectFit
    }

    Colorize {
        anchors.fill: linkIcon
        source: linkIcon
        hue: 0.0
        saturation: 0
        lightness: UiHelper.isDarkTheme ? 1 : -1
    }

    ColumnLayout {
        id: contentColumn
        anchors.fill: parent
        anchors.margins: 14
        spacing: 10

        ColumnLayout {
            Layout.fillWidth: true
            Layout.rightMargin: 42
            spacing: 4

            Label {
                text: "Connected devices"
                font.pixelSize: 20
                font.bold: true
                color: UiHelper.textColor
            }

            Label {
                text: `${helper.connectedCount} connected · ${helper.totalPaired} paired · max ${helper.maxConnections}`
                font.pixelSize: 12
                color: UiHelper.mutedTextColor
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: UiHelper.borderColor
            opacity: 0.6
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.preferredHeight: Math.min(devicesList.contentHeight, 168)
            Layout.minimumHeight: Math.min(devicesList.contentHeight, 52)
            clip: true
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AsNeeded

            ListView {
                id: devicesList
                width: parent.width
                height: parent.height
                spacing: 8
                boundsBehavior: Flickable.StopAtBounds
                model: helper.model

                delegate: Rectangle {
                    id: deviceRow
                    width: Math.max(0, devicesList.width - 4)
                    height: 48
                    radius: 11
                    color: connected ? UiHelper.connectedBadgeColor : "transparent"
                    border.color: connected ? UiHelper.highlightColor : UiHelper.borderColor
                    border.width: connected ? 1 : 0

                    required property string name
                    required property bool connected
                    required property int deviceIndex

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        anchors.rightMargin: 8
                        spacing: 8

                        Switch {
                            id: connectionSwitch
                            checked: deviceRow.connected
                            text: deviceRow.name + (deviceRow.deviceIndex === helper.ownIndex ? " (current device)" : "")
                            Layout.fillWidth: true
                            onClicked: deviceRow.connected ? helper.disconnectDevice(deviceRow.deviceIndex) : helper.connectDevice(deviceRow.deviceIndex)
                        }

                        Label {
                            visible: deviceRow.connected
                            text: "Connected"
                            color: UiHelper.connectedBadgeTextColor
                            font.pixelSize: 11
                            font.bold: true
                        }

                        Button {
                            flat: true
                            icon.source: "qrc:/icons/trash.svg"
                            icon.color: "#b50927"
                            ToolTip.visible: hovered
                            ToolTip.text: "Delete paired device"
                            onClicked: {
                                confirmDeleteDialog.deviceIndex = deviceRow.deviceIndex;
                                confirmDeleteDialog.deviceName = deviceRow.name;
                                confirmDeleteDialog.open();
                            }
                        }
                    }
                }
            }
        }
    }

    Dialog {
        id: confirmDeleteDialog
        title: "Delete device"
        property string deviceName: ""
        property int deviceIndex: -1

        width: Math.min(420, Math.max(320, root.width - 32))
        standardButtons: Dialog.Yes | Dialog.No
        modal: true
        Overlay.modal: Rectangle { color: UiHelper.overlayColor }

        enter: Transition { NumberAnimation { from: 0.0; property: "opacity"; to: 1.0 } }
        exit: Transition { NumberAnimation { from: 1.0; property: "opacity"; to: 0.0 } }

        contentItem: Item {
            implicitWidth: 360
            implicitHeight: deleteContent.implicitHeight + 24

            ColumnLayout {
                id: deleteContent
                anchors.fill: parent
                anchors.margins: 12
                spacing: 10

                Label {
                    text: `Are you sure you want to delete ${confirmDeleteDialog.deviceName}?`
                    color: UiHelper.textColor
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }
        }

        onAccepted: {
            if (confirmDeleteDialog.deviceIndex !== -1)
                helper.deleteDevice(confirmDeleteDialog.deviceIndex);
        }
        onClosed: {
            confirmDeleteDialog.deviceName = "";
            confirmDeleteDialog.deviceIndex = -1;
        }
    }
}
