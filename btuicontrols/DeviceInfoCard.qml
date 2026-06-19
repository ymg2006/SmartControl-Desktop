import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import gaiaV3

Rectangle {
    id: deviceInfoRoot
    implicitWidth: 400
    implicitHeight: Math.max(156, infoContent.implicitHeight + 44)
    radius: 20
    color: deviceInfoRoot.palette.window
    border.color: deviceInfoRoot.palette.mid
    clip: true

    property alias batteryPercent: deviceInfoHelper.batteryPercent
    readonly property bool hasBatteryPercent: deviceInfoHelper.batteryPercent >= 0

    DeviceInfoCardHelper { id: deviceInfoHelper }

    Item {
        id: batteryBadge
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 18
        anchors.topMargin: 18
        width: 76
        height: 34
        z: 10

        readonly property int displayPercent: Math.max(0, Math.min(100, Math.round(deviceInfoHelper.batteryPercent)))
        readonly property real fillRatio: deviceInfoRoot.hasBatteryPercent ? displayPercent / 100.0 : 0.0

        Rectangle {
            id: batteryBody
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: 66
            height: 30
            radius: 7
            color: UiHelper.isDarkTheme ? "#242424" : "#f1f1f1"
            border.width: 2
            border.color: UiHelper.isDarkTheme ? "#747474" : "#1f1f1f"
            clip: true

            Rectangle {
                x: 4
                y: 4
                width: Math.max(0, (batteryBody.width - 8) * batteryBadge.fillRatio)
                height: batteryBody.height - 8
                radius: 4
                color: UiHelper.isDarkTheme ? "#3a3a3a" : "#2c2c2c"
                visible: deviceInfoRoot.hasBatteryPercent
            }

            Label {
                anchors.fill: parent
                anchors.margins: 2
                text: deviceInfoRoot.hasBatteryPercent ? batteryBadge.displayPercent + "%" : "--"
                color: UiHelper.isDarkTheme ? "#f2f2f2" : "#ffffff"
                font.pixelSize: 10
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            anchors.left: batteryBody.right
            anchors.leftMargin: 2
            anchors.verticalCenter: batteryBody.verticalCenter
            width: 5
            height: 14
            radius: 2
            color: UiHelper.isDarkTheme ? "#242424" : "#f1f1f1"
            border.width: 2
            border.color: UiHelper.isDarkTheme ? "#747474" : "#1f1f1f"
        }
    }

    RowLayout {
        id: infoContent
        anchors.fill: parent
        anchors.margins: 22
        anchors.rightMargin: 108
        spacing: 20

        Rectangle {
            Layout.preferredWidth: 112
            Layout.preferredHeight: 112
            Layout.alignment: Qt.AlignVCenter
            radius: 20
            color: "transparent"

            Image {
                anchors.fill: parent
                source: "qrc:/icons/m4.png"
                sourceSize.width: 112
                sourceSize.height: 112
                fillMode: Image.PreserveAspectFit
            }
        }

        ColumnLayout {
            id: detailsColumn
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            spacing: 8

            Label {
                text: qsTr("Version: ") + (deviceInfoHelper.releaseVersion !== "" ? deviceInfoHelper.releaseVersion : "—")
                color: deviceInfoRoot.palette.windowText
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Model: ") + (deviceInfoHelper.modelId !== "" ? deviceInfoHelper.modelId : "—")
                color: deviceInfoRoot.palette.windowText
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Serial: ") + (deviceInfoHelper.serialNumber !== "" ? deviceInfoHelper.serialNumber : "—")
                color: deviceInfoRoot.palette.windowText
                wrapMode: Text.WrapAnywhere
                Layout.fillWidth: true
            }
        }
    }
}
