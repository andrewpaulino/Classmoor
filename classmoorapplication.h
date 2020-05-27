#ifndef CLASSMOORAPPLICATION_H
#define CLASSMOORAPPLICATION_H

#include <QObject>

class ClassmoorApplication : public QObject
{
    Q_OBJECT
public:
    explicit ClassmoorApplication(QObject *parent = nullptr);

signals:

};

#endif // CLASSMOORAPPLICATION_H
