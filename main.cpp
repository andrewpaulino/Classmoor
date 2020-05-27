#include <QGuiApplication>
#include <iostream>
#include <QQmlApplicationEngine>
#include "classmoor.h"
#include <QQmlContext>
#include "setup.h"
int main(int argc, char *argv[])
{

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {

        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QGuiApplication app(argc, argv);

        QQmlApplicationEngine* engine = new QQmlApplicationEngine;

        classmoor mainExecutive(engine);

        const QUrl url(QStringLiteral("qrc:/Setup.qml"));

        QObject::connect(&*(engine), &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);


        return app.exec();
    }
    Aws::ShutdownAPI(options);
}
