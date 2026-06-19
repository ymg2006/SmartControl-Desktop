import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Rectangle {
    id: root
    width: 350
    implicitHeight: cardRow.implicitHeight + 20
    height: implicitHeight
    radius: 18
    color: root.palette.base
    border.color: root.isConnected ? UiHelper.highlightColor : root.palette.mid
    border.width: root.isConnected ? 2 : 1
    clip: true
    opacity: root.isOnline ? 1.0 : 0.62

    required property string name
    required property string address
    required property bool isOnline
    required property bool isConnected
    required property bool isRemembered
    required property string uuid

    property bool showAutoOpenSwitch: false
    property bool autoOpenEnabled: false

    signal activated()
    signal autoOpenToggled(bool enabled)

    MouseArea {
        anchors.fill: parent
        anchors.rightMargin: root.showAutoOpenSwitch ? 154 : 0
        cursorShape: root.address !== "" ? Qt.PointingHandCursor : Qt.ForbiddenCursor
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton
        onClicked: {
            if (root.address !== "")
                root.activated();
        }
        onEntered: root.border.color = UiHelper.highlightColor
        onExited: root.border.color = root.isConnected ? UiHelper.highlightColor : root.palette.mid
    }

    RowLayout {
        id: cardRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 14
        anchors.rightMargin: 14
        spacing: 12

        Rectangle {
            Layout.preferredWidth: 42
            Layout.preferredHeight: 42
            radius: 21
            color: UiHelper.iconBackgroundColor

            Image {
                id: headphones
                anchors.centerIn: parent
                width: 26
                height: 26
                source: "qrc:/icons/headphones.svg"
                fillMode: Image.PreserveAspectFit
            }

            Colorize {
                anchors.fill: headphones
                source: headphones
                hue: 0.0
                saturation: 0
                lightness: UiHelper.isDarkTheme ? 1 : -1
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4

            Label {
                text: root.name !== "" ? root.name : "Unnamed device"
                font.bold: true
                font.pixelSize: 17
                color: root.palette.windowText
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Label {
                text: root.address !== "" ? root.address : "Address required"
                font.pixelSize: 12
                color: UiHelper.mutedTextColor
                elide: Text.ElideRight
                Layout.fillWidth: true
            }
        }

        Switch {
            id: autoOpenSwitch
            visible: root.showAutoOpenSwitch
            enabled: root.address !== ""
            checked: root.autoOpenEnabled
            text: "Auto-open"
            font.pixelSize: 12
            Layout.preferredWidth: visible ? 132 : 0
            Layout.preferredHeight: 34
            onToggled: root.autoOpenToggled(checked)
        }

        Rectangle {
            Layout.preferredWidth: statusLabel.implicitWidth + 18
            Layout.preferredHeight: 28
            radius: 14
            color: root.isConnected ? UiHelper.connectedBadgeColor : (root.isOnline ? UiHelper.onlineBadgeColor : UiHelper.offlineBadgeColor)

            Label {
                id: statusLabel
                anchors.centerIn: parent
                text: root.isConnected ? "Connected" : (root.isOnline ? "Available" : (root.isRemembered ? "Paired" : "Saved"))
                font.pixelSize: 11
                font.bold: true
                color: root.isConnected ? UiHelper.connectedBadgeTextColor : UiHelper.badgeTextColor
            }
        }
    }
}
