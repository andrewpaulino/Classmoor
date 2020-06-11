#ifndef MODULES_H
#define MODULES_H

#include <QObject>
#include "lambdaclient.h"
#include <QFileInfo>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <iostream>
#include <QDebug>
#include <QQmlContext>
#include <QDir>
#include <QProcess>
#include "linkedlist.h"
#include "utilityfunctions.h"
#include <QVariant>
#include "sqsclient.h"
#include <QCoreApplication>
#include <QFuture>
#include <QFutureWatcher>
#include <QList>
#include <QtConcurrent>
#include <QDateTime>
#include <QTimer>

class Modules : public QObject
{
    Q_OBJECT
public:
    explicit Modules(QObject *parent = nullptr);
    ~Modules();
    void runIntialization();
private:
    QFutureWatcher<void> watcher;
    QFuture<void> future;
    UtilityFunctions util;
    lambdaClient* lambda_client;
    userCredentials creds;
    intitalizeClassroomPayload intialLoad;
    void intalizeState();
    bool readFromFile();
    SqsClient* sqs_client;
    void runMessageUpdates();
    void startPolling( );
    void activateTimer();
    int timeInSeconds = 0;
    void waitForClosingPollOnThread();
    QTimer* activeTimer;
signals:
    void changeState(QVariant stateSetting, QVariant classCheck_message, QVariant classTime_message, int timeInSec);
    void newMessage(QString m);
    void updateTimer(int timeInSec);
public slots:
    void intialize();
    void updateTime();
    void recievedMessage(QString m);
    void handleCheckin();


};

#endif // MODULES_H
