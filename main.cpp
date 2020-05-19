#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <aws/core/Aws.h>

int main(int argc, char *argv[])
{


    //AWS SDK test
//    Aws::SDKOptions options;
//    Aws::InitAPI(options);
//    Aws::String test;

//    test = "AWS SDK Connected";

//    std::cout << test << std::endl;
    //END TEST

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
//        Aws::ShutdownAPI(options);
}
