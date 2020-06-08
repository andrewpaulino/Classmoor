#ifndef CLASSTIME_H
#define CLASSTIME_H
#include <QObject>
#include "dynamoclient.h"
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

class Classtime : public QObject
{
    Q_OBJECT
public:
    explicit Classtime(QObject *parent = nullptr);
    ~Classtime();
private:
    DynamoClient* dynamo_client;
    UtilityFunctions util;
    lambdaClient* lambda_client;
    userCredentials creds;
    bool readFromFile();
    void intalizeState();
    intitalizeClasstimePayload intialLoad;
    SqsClient* sqs_client;
    void activateTimer();
    int timeInSeconds = 0;
    QTimer* activeTimer;

    clastimeUpdatePayload runUpdateThreadedFunction(Aws::String classtimeId, Aws::String classroomId );
signals:
    void updateComponents(QString lessonHeader, QString lessonResource, int numOfParticipants);
    void updateTimer(int timeInSeconds);
public slots:
    void retrieveClasstimeDetails();
    void updateTime();
    void leaveClasstime();
    void recievedMessage(QString m);
};

#endif // CLASSTIME_H
