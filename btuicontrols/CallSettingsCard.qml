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

    CallSettingsCardHelper { id: helper }

    Image {
        id: linkIcon
        source: "qrc:/icons/phone.badge.waveform.svg"
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
                id: switchAutoAnswer
                checked: helper.autoCallEnabled
                text: "Auto Answer Calls"
                onClicked: helper.autoCallEnabled = switchAutoAnswer.checked
            }

            Label {
                Layout.leftMargin: 50
                text: "Automatically answers an incoming call when you put on your headphones."
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
                id: switchComfortCall
                checked: helper.autoCallEnabled
                text: "Comfort Call"
                onClicked: helper.autoCallEnabled = switchComfortCall.checked
            }

            Label {
                Layout.leftMargin: 50
                text: "Gives phone calls a more natural sound experience."
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
                font.pointSize: 10
                color: root.palette.windowText
            }
        }
    }
}
