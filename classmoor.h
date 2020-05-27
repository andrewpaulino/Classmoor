#ifndef CLASSMOOR_H
#define CLASSMOOR_H

#include "snsclient.h"
#include "dynamoclient.h"
#include "lambdaclient.h"
#include <QFileInfo>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <iostream>
#include <QQmlContext>
#include "setup.h"
class classmoor {
public:
    classmoor();
    classmoor(QQmlApplicationEngine* e);
    void intiateSetup();
    QQmlApplicationEngine getEngine();
private:
    bool isFirstTimeRunning();
    QQmlApplicationEngine* engine;
};

#endif // CLASSMOOR_H
