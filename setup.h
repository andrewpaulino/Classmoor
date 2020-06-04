#ifndef SETUP_H
#define SETUP_H

#include <QObject>
#include "snsclient.h"
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
#include "utilityfunctions.h"

class Setup : public QObject
{
    Q_OBJECT
public:
    explicit Setup(QObject *parent = nullptr);
    Setup(QQmlApplicationEngine* e, lambdaClient* lambda);
private:
    QQmlApplicationEngine* engine;
    lambdaClient* lambda_client;
    bool isButtonDisabled = true;
    QString _name;
    UtilityFunctions util;
    QString _classCode;
    bool writeToFile(joinClassroomPayload v);
signals:
    bool filledOut(bool isValid);
    void results(bool found, bool done);
    void doneWithSetup(bool status);

public slots:
    void joinClassroom(QString code, QString name);
    void restartApplication();

};

#endif // SETUP_H
