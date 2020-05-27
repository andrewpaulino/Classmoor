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

class Setup : public QObject
{
    Q_OBJECT
public:
    explicit Setup(QObject *parent = nullptr);
    Setup(QQmlApplicationEngine* e, lambdaClient* lambda);
private:
    QQmlApplicationEngine* engine;
    lambdaClient* _lambda;
//    bool nameFieldFilled;
//    bool classCodeFieldFilled;
    bool isButtonDisabled = true;
    QString _name;
    QString _classCode;

signals:
    bool filledOut(bool isValid);

public slots:
    void joinClassroom(QString code, QString name);

//    void isClassCodeField(QString val);
//    void isNameCodeField(QString val);

};

#endif // SETUP_H
