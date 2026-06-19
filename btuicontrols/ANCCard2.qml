import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects


Rectangle {
    id: root
    implicitWidth: 400
    implicitHeight: Math.max(300, contentLayout.implicitHeight + 40)
    radius: 20
    color: root.palette.window
    border.color: root.palette.mid
    clip: true
    property real maskPosition: 0

    ANCCardHelper {
        id: helper

        onAncTransparencyChanged: function() {
            slider.value = helper.ancTransparency / 100;
            root.maskPosition = image.width * slider.value
        }
    }

    Image {
        id: cardIcon
        source: "qrc:/icons/waveform.path.badge.minus.svg"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        width: 36
        fillMode: Image.PreserveAspectFit
    }
    Colorize {
        visible: !UiHelper.isDarkTheme
        anchors.fill: cardIcon
        source: cardIcon
        hue: .0
        saturation: 0
        lightness:  -1
    }

    ColumnLayout {
        id: contentLayout
        anchors.fill: parent
        anchors.margins: 22
        spacing: 18
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2
            Switch {
                id: ancEnabledSwitch
                text: "Noise cancelation"
                checked: helper.ancEnabled

                onClicked: {
                    helper.ancEnabled = ancEnabledSwitch.checked
                }
            }
            Label {
                text: "Active noise cancellation"
                Layout.leftMargin: 50
                font.pointSize: 10
                color: root.palette.windowText

            }
        }
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 8
            Label {
                text: "Wind Noise Reduction"
                font.bold: true
            }

            Label {
                text: "Adjusts ANC to avoid unwanted noise in windy conditions"
                font.pointSize: 10
                color: root.palette.windowText

            }
            Rectangle {
                id: windModeControl
                Layout.fillWidth: true
                Layout.preferredHeight: 42
                radius: 6
                color: UiHelper.isDarkTheme ? "#242424" : "#eeeeee"
                border.width: 1
                border.color: UiHelper.isDarkTheme ? "#5c5c5c" : "#9a9a9a"
                clip: true

                property int selectedIndex: helper.antiWindValue === 1 ? 1 : (helper.antiWindValue === 2 ? 2 : 0)

                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    Repeater {
                        model: [
                            { label: "Off", value: 0 },
                            { label: "Max", value: 1 },
                            { label: "Auto", value: 2 }
                        ]

                        delegate: Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            color: windModeControl.selectedIndex === index
                                   ? (UiHelper.isDarkTheme ? "#4a4a4a" : "#d8d8d8")
                                   : "transparent"
                            border.width: 0

                            Rectangle {
                                visible: index > 0
                                width: 1
                                anchors.left: parent.left
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                color: UiHelper.isDarkTheme ? "#5c5c5c" : "#a0a0a0"
                            }

                            Label {
                                anchors.centerIn: parent
                                text: modelData.label
                                color: root.palette.windowText
                                font.pixelSize: 15
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: helper.antiWindValue = modelData.value
                            }
                        }
                    }
                }
            }

        }

        ColumnLayout {
            spacing: 2
            Layout.fillWidth: true

            Switch {
                text: "Adaptive"
                id: adaptiveSwitch
                checked: helper.adaptiveEnabled
                onClicked: {
                    helper.adaptiveEnabled = adaptiveSwitch.checked
                }
            }
            Label {
                text: "ANC automatically adapts to the environment."
                font.pointSize: 10
                Layout.leftMargin: 50
                color: root.palette.windowText

            }
        }

        ColumnLayout {
            spacing: 2
            Layout.fillWidth: true
            Rectangle {
                Layout.fillWidth: true
                // height: 30
                Layout.preferredHeight: 30
                clip: true
                color: "transparent"
                Image {
                    id: image
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 30
                    source: UiHelper.isDarkTheme ? "qrc:/icons/waveform-dark.png" : "qrc:/icons/waveform.png"
                    fillMode: Image.Stretch
                    clip: true

                }
                Image {
                    id: mask
                    anchors.left: parent.left
                    anchors.right: parent.right
                    width: image.width
                    anchors.leftMargin: root.maskPosition
                    height: 30
                    source: "qrc:/icons/mask.png"
                    fillMode: Image.Stretch
                }
                Colorize {
                    visible: UiHelper.isDarkTheme
                    anchors.fill: mask
                    source: mask
                    hue: 1.0
                    saturation: 0
                    lightness:  -0.7490196228027344
                }
            }

            Slider {
                Layout.fillWidth: true
                id: slider
                enabled: !adaptiveSwitch.checked
                value: 0.5
                onMoved: {
                    root.maskPosition = image.width * slider.value;
                    helper.ancTransparency = slider.value * 100
                }
            }
        }
    }

}
