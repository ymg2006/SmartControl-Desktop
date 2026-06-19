import QtQuick.Controls
import QtQuick.Layouts
import QtCore
import QtQuick
import btuicontrols
import QtQuick.LocalStorage
import gaiaV3

Page {
    id: deviceListPage
    property alias bluetoothHandler: bluetoothHandler
    property string autoConnectingAddress: ""
    property string connectionError: ""
    property bool initialLoadInProgress: true
    property bool initialLoadCompleted: false
    property bool autoOpenAttempted: false

    background: Rectangle { color: UiHelper.windowColor }

    function sameAddress(a, b) {
        return a !== "" && b !== "" && a.toLowerCase() === b.toLowerCase();
    }

    function normalizedAddress(address) {
        return address && address !== "" ? address.toLowerCase() : "";
    }

    function autoOpenAddressList() {
        return pageSettings.autoOpenDeviceAddresses === "" ? [] : pageSettings.autoOpenDeviceAddresses.split("|").filter(function(item) { return item !== ""; });
    }

    function isAutoOpenEnabled(address) {
        const key = normalizedAddress(address);
        if (key === "")
            return false;
        return autoOpenAddressList().indexOf(key) >= 0;
    }

    function setAutoOpenEnabled(address, enabled) {
        const key = normalizedAddress(address);
        if (key === "")
            return;

        let items = autoOpenAddressList();
        const index = items.indexOf(key);
        if (enabled && index < 0)
            items.push(key);
        else if (!enabled && index >= 0)
            items.splice(index, 1);

        pageSettings.autoOpenDeviceAddresses = items.join("|");
    }

    function isClientDevice(address) {
        return GAIARfcommClient.isConnected && sameAddress(address, GAIARfcommClient.deviceAddress);
    }

    function findDeviceIndex(model, address, uuid) {
        for (let i = 0; i < model.count; i++) {
            const item = model.get(i);
            if ((uuid && item.uuid === uuid) || (address && item.address === address))
                return i;
        }
        return -1;
    }

    function removeDevice(model, address, uuid) {
        const index = findDeviceIndex(model, address, uuid);
        if (index >= 0)
            model.remove(index);
    }

    function upsertDevice(model, name, address, uuid, isOnline, isConnected, isRemembered, prepend) {
        const safeName = name && name !== "" ? name : "Sennheiser device";
        const safeAddress = address ? address : "";
        const safeUuid = uuid ? uuid : "";
        const index = findDeviceIndex(model, safeAddress, safeUuid);

        if (index >= 0) {
            model.setProperty(index, "name", safeName);
            if (safeAddress !== "")
                model.setProperty(index, "address", safeAddress);
            if (safeUuid !== "")
                model.setProperty(index, "uuid", safeUuid);
            model.setProperty(index, "isOnline", isOnline || model.get(index).isOnline);
            model.setProperty(index, "isConnected", isConnected || isClientDevice(safeAddress));
            model.setProperty(index, "isRemembered", isRemembered || model.get(index).isRemembered);
            return;
        }

        const row = {
            name: safeName,
            address: safeAddress,
            isOnline: isOnline,
            isConnected: isConnected || isClientDevice(safeAddress),
            isRemembered: isRemembered,
            uuid: safeUuid
        };

        if (prepend)
            model.insert(0, row);
        else
            model.append(row);
    }

    function saveDevice(name, address, uuid) {
        if (address === "" && uuid === "")
            return;

        db.executeWithParams('SELECT * FROM devices WHERE uuid = ? OR address = ?;', [uuid, address], (result) => {
            if (result.rows.length === 0)
                db.executeWithParams('INSERT INTO devices (name, address, uuid) VALUES (?, ?, ?);', [name, address, uuid]);
        });
    }

    function openWindowsDevice(name, address) {
        if (address === "")
            return;

        autoConnectingAddress = address;
        connectionError = "";
        GAIARfcommClient.openKnownWindowsDevice(
            name && name !== "" ? name : "Sennheiser headset",
            address
        );
    }

    function refreshWindowsDevices() {
        connectedModel.clear();
        savedModel.clear();
        autoOpenAttempted = false;
        bluetoothHandler.refreshKnownDevices();
        upsertConnectedClient();
    }

    function loadDevices() {
        initialLoadInProgress = true;
        connectedModel.clear();
        savedModel.clear();

        db.execute('SELECT * FROM devices;', (result) => {
            for (let i = 0; i < result.rows.length; i++) {
                const item = result.rows.item(i);
                upsertDevice(savedModel, item.name, item.address, item.uuid, false, isClientDevice(item.address), true, false);
            }
            refreshWindowsDevices();
            initialLoadCompleted = true;
            initialLoadInProgress = bluetoothHandler.isSearching;
        });
    }

    function beginInitialLoad() {
        initialLoadInProgress = true;
        initialLoadCompleted = false;
        initialLoadTimer.restart();
    }

    function upsertConnectedClient() {
        if (!GAIARfcommClient.isConnected || GAIARfcommClient.deviceAddress === "")
            return;

        upsertDevice(
            connectedModel,
            GAIARfcommClient.deviceName !== "" ? GAIARfcommClient.deviceName : "Connected headset",
            GAIARfcommClient.deviceAddress,
            "",
            true,
            true,
            true,
            true
        );
        removeDevice(savedModel, GAIARfcommClient.deviceAddress, "");
    }

    function maybeAutoOpenDevice(name, address, connected) {
        if (autoOpenAttempted || GAIARfcommClient.isConnected)
            return;
        if (!connected || !address || address === "" || !isAutoOpenEnabled(address))
            return;

        autoOpenAttempted = true;
        openWindowsDevice(name, address);
    }

    Component.onCompleted: beginInitialLoad()

    Timer {
        id: initialLoadTimer
        interval: 1
        repeat: false
        onTriggered: loadDevices()
    }

    ScrollView {
        id: scrollView
        anchors.fill: parent
        clip: true
        contentWidth: availableWidth
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        Item {
            width: scrollView.availableWidth
            implicitHeight: contentColumn.implicitHeight + 56

            ColumnLayout {
                id: contentColumn
                width: Math.min(parent.width - 32, 860)
                x: Math.max(16, (parent.width - width) / 2)
                y: 28
                spacing: 22

                Rectangle {
                    Layout.fillWidth: true
                    radius: 22
                    color: UiHelper.cardColor
                    border.color: connectedModel.count > 0 ? UiHelper.highlightColor : UiHelper.borderColor
                    border.width: 1
                    implicitHeight: windowsColumn.implicitHeight + 32

                    ColumnLayout {
                        id: windowsColumn
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 12

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 4

                                Label {
                                    text: "Windows Bluetooth devices"
                                    font.pixelSize: 22
                                    font.bold: true
                                    color: UiHelper.textColor
                                    wrapMode: Text.WordWrap
                                    Layout.fillWidth: true
                                }

                                Label {
                                    text: "The app first loads headsets already paired or connected in Windows, then opens the native Windows RFCOMM control channel when you click one."
                                    color: UiHelper.mutedTextColor
                                    wrapMode: Text.WordWrap
                                    Layout.fillWidth: true
                                }
                            }

                            ToolButton {
                                id: refreshButton
                                Layout.alignment: Qt.AlignTop
                                Layout.preferredWidth: 40
                                Layout.preferredHeight: 40
                                padding: 0
                                text: ""
                                Accessible.name: "Refresh Windows devices"
                                ToolTip.visible: hovered
                                ToolTip.text: "Refresh Windows devices"
                                scale: refreshButton.down ? 0.94 : 1.0
                                background: Rectangle {
                                    anchors.fill: parent
                                    radius: width / 2
                                    color: refreshButton.down ? UiHelper.highlightColor : (refreshButton.hovered ? UiHelper.buttonHoverColor : UiHelper.alternateBaseColor)
                                    border.color: refreshButton.hovered || refreshButton.down ? UiHelper.highlightColor : UiHelper.borderColor
                                    border.width: 1
                                }
                                contentItem: Item {
                                    implicitWidth: 40
                                    implicitHeight: 40
                                    Text {
                                        anchors.centerIn: parent
                                        text: "⟳"
                                        font.pixelSize: 20
                                        color: refreshButton.down ? UiHelper.highlightedTextColor : UiHelper.textColor
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }
                                onClicked: {
                                    initialLoadInProgress = true;
                                    refreshWindowsDevices();
                                    initialLoadInProgress = bluetoothHandler.isSearching;
                                }
                            }
                        }

                        ColumnLayout {
                            Layout.fillWidth: true
                            visible: initialLoadCompleted && connectedModel.count > 0
                            spacing: 10

                            Repeater {
                                model: connectedModel
                                delegate: FoundDeviceCard {
                                    width: windowsColumn.width
                                    showAutoOpenSwitch: true
                                    autoOpenEnabled: isAutoOpenEnabled(address)
                                    onActivated: openWindowsDevice(name, address)
                                    onAutoOpenToggled: function(enabled) { setAutoOpenEnabled(address, enabled); }
                                }
                            }
                        }

                        Label {
                            visible: initialLoadCompleted && connectedModel.count === 0
                            text: "No supported Sennheiser headset was found in Windows. Pair or connect your headset in Windows Settings, then press refresh."
                            color: UiHelper.mutedTextColor
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }

                        Label {
                            visible: autoConnectingAddress !== "" && !GAIARfcommClient.isConnected
                            text: "Opening and validating the real Windows RFCOMM control channel..."
                            color: UiHelper.mutedTextColor
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }

                        Label {
                            visible: connectionError !== ""
                            text: connectionError
                            color: "#ff6b6b"
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }

                        Item {
                            Layout.fillWidth: true
                            implicitHeight: initialLoadInProgress ? loadingRow.implicitHeight + 8 : 0
                            visible: initialLoadInProgress

                            RowLayout {
                                id: loadingRow
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                spacing: 12

                                BusyIndicator {
                                    running: initialLoadInProgress
                                    width: 32
                                    height: 32
                                }

                                Label {
                                    text: initialLoadCompleted ? "Refreshing Windows device list..." : "Loading Windows device list for the first time..."
                                    color: UiHelper.mutedTextColor
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    visible: savedModel.count > 0
                    radius: 22
                    color: UiHelper.cardColor
                    border.color: UiHelper.borderColor
                    implicitHeight: savedColumn.implicitHeight + 32

                    ColumnLayout {
                        id: savedColumn
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 12

                        Label {
                            text: "Saved devices"
                            font.pixelSize: 18
                            font.bold: true
                            color: UiHelper.textColor
                        }

                        Repeater {
                            model: savedModel
                            delegate: FoundDeviceCard {
                                width: savedColumn.width
                                showAutoOpenSwitch: true
                                autoOpenEnabled: isAutoOpenEnabled(address)
                                onActivated: openWindowsDevice(name, address)
                                onAutoOpenToggled: function(enabled) { setAutoOpenEnabled(address, enabled); }
                            }
                        }
                    }
                }
            }
        }
    }

    ListModel { id: connectedModel }
    ListModel { id: savedModel }

    Connections {
        target: GAIARfcommClient
        function onIsConnectedChanged() {
            if (GAIARfcommClient.isConnected) {
                autoConnectingAddress = "";
                connectionError = "";
            }
            upsertConnectedClient();
        }
        function onConnectionFailed(message) {
            autoConnectingAddress = "";
            connectionError = message;
        }
        function onDeviceAddressChanged() { upsertConnectedClient(); }
        function onDeviceNameChanged() { upsertConnectedClient(); }
    }

    BluetoothHandler {
        id: bluetoothHandler

        onIsSearchingChanged: {
            initialLoadInProgress = bluetoothHandler.isSearching;
            if (!bluetoothHandler.isSearching)
                initialLoadCompleted = true;
        }

        onNewDeviceAdded: function(name, address, uuid, osConnected, remembered) {
            const connected = osConnected || isClientDevice(address);
            saveDevice(name, address, uuid);

            removeDevice(savedModel, address, uuid);
            upsertDevice(connectedModel, name, address, uuid, true, connected, remembered, true);
            maybeAutoOpenDevice(name, address, connected);
        }
    }

    Settings {
        id: pageSettings
        category: "startup"
        property string autoOpenDeviceAddresses: ""
    }

    DatabaseStorage { id: db }
}
