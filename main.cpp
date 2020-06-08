#include <QGuiApplication>
#include <iostream>
#include <QQmlApplicationEngine>
#include "classmoor.h"
#include <QQmlContext>
#include "setup.h"
#include "modules.h"
#include "classtime.h"
#include <QtWebView/QtWebView>

#include <QtCore/QUrl>
#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QGuiApplication>
#include <QStyleHints>
#include <QScreen>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtWebView/QtWebView>


int main(int argc, char *argv[])
{

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {

        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QtWebView::initialize();

        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;



        Classmoor mainExecutive;

        QUrl url;

        //Register QML Types
        qmlRegisterType<Setup>("com.classmoor.setup", 1, 0, "Setup");
        qmlRegisterType<Classmoor>("com.classmoor.classmoor", 1, 0, "Classmoor");
        qmlRegisterType<Modules>("com.classmoor.modules", 1, 0, "Modules");
        qmlRegisterType<Classtime>("com.classmoor.classtime", 1, 0, "Classtime");

        if (mainExecutive.isFirstTimeRunning()) {
            url = (QStringLiteral("qrc:/Setup.qml"));
        } else {
            url = (QStringLiteral("qrc:/main.qml"));
        }



        QObject::connect(&(engine), &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

        engine.load(url);
        qDebug() << engine.rootObjects().first()->objectName();
        return app.exec();
    }
    Aws::ShutdownAPI(options);
}
