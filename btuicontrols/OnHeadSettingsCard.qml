import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Rectangle {
    id: root
    implicitWidth: 400
    implicitHeight: contentLayout.implicitHeight + 28
    radius: 20
    border.color: root.palette.mid
    clip: true
    color: root.palette.window

    OnHeadSettingsCardHelper { id: helper }

    Image {
        id: linkIcon
        source: "qrc:/icons/person.wave.2.svg"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 14
        anchors.topMargin: 14
        width: 32
        fillMode: Image.PreserveAspectFit
    }

    Colorize {
        visible: !UiHelper.isDarkTheme
        anchors.fill: linkIcon
        source: linkIcon
        hue: .0
        saturation: 0
        lightness: -1
    }

    ColumnLayout {
        id: contentLayout
        spacing: 14
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 14
        anchors.rightMargin: 58

        ColumnLayout {
            spacing: 2
            Layout.fillWidth: true

            Switch {
                id: switchOnHeadDetection
                checked: helper.onHeadEnabled
                text: "On-head detection"
                onClicked: helper.onHeadEnabled = switchOnHeadDetection.checked
            }

            Label {
                Layout.leftMargin: 50
                text: "Activate Smart Pause, hold calls automatically, power saving mode."
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
                font.pointSize: 10
                color: root.palette.windowText
            }
        }

        ColumnLayout {
            spacing: 2
            Layout.fillWidth: true

            Switch {
                id: switchSmartPause
                checked: helper.smartPauseEnabled
                text: "Smart Pause"
                onClicked: helper.smartPauseEnabled = switchSmartPause.checked
            }

            Label {
                Layout.leftMargin: 50
                text: "Halts playback when the headphones are taken off and resumes playback when they are placed back on the ears."
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
                font.pointSize: 10
                color: root.palette.windowText
            }
        }
    }
}
