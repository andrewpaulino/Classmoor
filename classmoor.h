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


class classmoor : public QObject
{
    Q_OBJECT

public:
    classmoor();
    classmoor(QObject *parent) : QObject(parent) {}
    classmoor(QQmlApplicationEngine* e);
    void intiateSetup();
    QQmlApplicationEngine getEngine();
private:
    bool isFirstTimeRunning();
    QQmlApplicationEngine* engine;
signals:

public slots:
};

#endif // CLASSMOOR_H
