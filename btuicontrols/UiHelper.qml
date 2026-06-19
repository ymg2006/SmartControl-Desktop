pragma Singleton
import QtQuick
import QtCore

Item {
    id: uihelper

    // Values: "system", "light", "dark".
    property string themeMode: "system"

    readonly property bool isDarkTheme: themeMode === "dark" ||
                                        (themeMode === "system" && systemPalette.window.hslLightness < 0.5)

    readonly property color windowColor: isDarkTheme ? "#1e1e1e" : "#f5f5f5"
    readonly property color cardColor: isDarkTheme ? "#252525" : "#ffffff"
    readonly property color alternateBaseColor: isDarkTheme ? "#2f2f2f" : "#f0f0f0"
    readonly property color textColor: isDarkTheme ? "#eeeeee" : "#202020"
    readonly property color mutedTextColor: isDarkTheme ? "#c7c7c7" : "#505050"
    readonly property color borderColor: isDarkTheme ? "#555555" : "#c8c8c8"
    readonly property color shadowColor: isDarkTheme ? "#000000" : "#888888"
    readonly property color highlightColor: isDarkTheme ? "#3d7eff" : "#0067c0"
    readonly property color highlightedTextColor: "#ffffff"
    readonly property color buttonColor: isDarkTheme ? "#2d2d2d" : "#ffffff"
    readonly property color buttonHoverColor: isDarkTheme ? "#353535" : "#eeeeee"
    readonly property color iconBackgroundColor: isDarkTheme ? "#333333" : "#eeeeee"
    readonly property color overlayColor: isDarkTheme ? "#88000000" : "#55888888"
    readonly property color connectedBadgeColor: isDarkTheme ? "#245c35" : "#dff6e5"
    readonly property color onlineBadgeColor: isDarkTheme ? "#263f5f" : "#e0efff"
    readonly property color offlineBadgeColor: isDarkTheme ? "#3a3a3a" : "#ececec"
    readonly property color connectedBadgeTextColor: isDarkTheme ? "#dff6e5" : "#0f5f2b"
    readonly property color badgeTextColor: isDarkTheme ? "#eeeeee" : "#303030"

    function setThemeMode(mode) {
        if (mode === "light" || mode === "dark" || mode === "system")
            themeMode = mode;
    }

    function toggleTheme() {
        themeMode = isDarkTheme ? "light" : "dark";
    }

    function themeModeToIndex(mode) {
        if (mode === "light")
            return 1;
        if (mode === "dark")
            return 2;
        return 0;
    }

    function themeIndexToMode(index) {
        if (index === 1)
            return "light";
        if (index === 2)
            return "dark";
        return "system";
    }

    SystemPalette {
        id: systemPalette
    }

    Settings {
        category: "appearance"
        property alias themeMode: uihelper.themeMode
    }
}
