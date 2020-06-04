#ifndef CLASSMOOR_H
#define CLASSMOOR_H

#include <QObject>
#include "snsclient.h"
#include "dynamoclient.h"
#include "lambdaclient.h"
#include <QFileInfo>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <iostream>
#include <QQmlContext>
#include "setup.h"


class Classmoor : public QObject
{
    Q_OBJECT

public:
    Classmoor(){};
    Classmoor(QObject *parent) : QObject(parent) {}
    Classmoor(QQmlApplicationEngine* e);
    void intiateSetup();
    QQmlApplicationEngine getEngine();
    bool isFirstTimeRunning();
private:
    QQmlApplicationEngine* engine;
signals:

public slots:
    void checkIfSetupIsCompleted(bool check);
};

#endif // CLASSMOOR_H
