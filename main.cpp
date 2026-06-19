#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtLogging>
#include <QStandardPaths>
#include <filesystem>
#include <QDir>
#include <QSettings>
#include <QIcon>
#include <QQuickStyle>
#include "AppController.h"

using namespace Qt::Literals::StringLiterals;


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define PROJECT_VERSION_MAJOR_STR TOSTRING(PROJECT_VERSION_MAJOR)
#define PROJECT_VERSION_MINOR_STR TOSTRING(PROJECT_VERSION_MINOR)
#define PROJECT_VERSION_PATCH_STR TOSTRING(PROJECT_VERSION_PATCH)
#define PROJECT_DESCRIPTION_STR TOSTRING(PROJECT_DESCRIPTION)

QtMessageHandler originalHandler = nullptr;
std::string logPath{};

void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QSettings s;
    std::vector<std::string> aa{};
    for(const auto &i : s.allKeys()){
        aa.push_back(i.toStdString());
    }
    if (s.value("saveDebug"_L1).toBool()){
        QString message = qFormatLogMessage(type, context, msg);
        static FILE *f = fopen(logPath.c_str(), "a");
        if (f != nullptr) {
            fprintf(f, "%s\n", qPrintable(message));
            fflush(f);
        }
    }


    if (originalHandler)
        originalHandler(type, context, msg);
}

int main(int argc, char *argv[]) {

    QQuickStyle::setStyle("Fusion");
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/appicon.png"));

    QCoreApplication::setOrganizationName("SennheiserDesktopClient");
    QCoreApplication::setOrganizationDomain("local");
    QCoreApplication::setApplicationName("SennheiserDesktopClient");
    const auto p = std::filesystem::path(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation).toStdString()) / "logs";
    auto d = QDir(p);
    if (!d.exists()){
        d.mkpath("."_L1);
    }
    logPath = (p / "log.txt").string();
    qSetMessagePattern("[%{time yyyy.MM.dd hh:mm:ss}] %{message}");
    originalHandler = qInstallMessageHandler(logToFile);
    qDebug() << "-------------------START-------------------";

    const QStringList args = QCoreApplication::arguments();
    const bool startMinimized = args.contains(QStringLiteral("--minimized")) || args.contains(QStringLiteral("--tray"));
    AppController appController(startMinimized);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(
            "projectVersionMajor",
            PROJECT_VERSION_MAJOR_STR
            );
    engine.rootContext()->setContextProperty(
            "projectVersionMinor",
            PROJECT_VERSION_MINOR_STR
            );
    engine.rootContext()->setContextProperty(
            "projectVersionPatch",
            PROJECT_VERSION_PATCH_STR
            );
    engine.rootContext()->setContextProperty(
            "projectDescription",
            PROJECT_DESCRIPTION_STR
            );
    engine.rootContext()->setContextProperty(
            "projectUrl",
            PROJECT_URL
            );
    engine.rootContext()->setContextProperty(
            "logFile",
            QString::fromStdString(logPath)
            );
    engine.rootContext()->setContextProperty("appController", &appController);

    QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreationFailed,
            &app,
            []() { QCoreApplication::exit(-1); },
            Qt::QueuedConnection);
    engine.loadFromModule("btui", "Main");

    return app.exec();
}
