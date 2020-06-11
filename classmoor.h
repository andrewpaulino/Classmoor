#ifndef CLASSMOOR_H
#define CLASSMOOR_H

#include <QObject>
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
    bool isFirstTimeRunning();

signals:

public slots:

};

#endif // CLASSMOOR_H
