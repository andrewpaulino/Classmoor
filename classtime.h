#ifndef CLASSTIME_H
#define CLASSTIME_H
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

// Classtime:
// * Concurrency + SQS Confirmation QUEUE
// * Threading with QTConcurrency
// * Signal and slots to our classtime functions
// * Watcher will then find the value and assign it

class Classtime : public QObject
{
    Q_OBJECT
public:
    explicit Classtime(QObject *parent = nullptr);
    ~Classtime();
private:

    // AWS CLIENTS
    lambdaClient* lambda_client;
    SqsClient* sqs_client;

    // Payloads
    UtilityFunctions util;
    userCredentials creds;
    intitalizeClasstimePayload intialLoad;
    clastimeUpdatePayload runUpdateThreadedFunction(Aws::String classtimeId, Aws::String classroomId );

    // General Functions
    bool readFromFile();
    void intalizeState();
    void activateTimer();
    int timeInSeconds = 0;
    QTimer* activeTimer;
signals:
    void updateComponents(QString lessonHeader, QString lessonResource, int numOfParticipants);
    void updateTimer(int timeInSeconds);

    // User Validation
    void messageSentConfirmed();
    void messageSentFailed();

    // Ending the classtime
    void endClasstime();
public slots:
    void retrieveClasstimeDetails();
    void updateTime();
    void postQuestion(QString questionText, bool isAnon);
    void leaveClasstime();
    void recievedMessage(QString m);
};

#endif // CLASSTIME_H
