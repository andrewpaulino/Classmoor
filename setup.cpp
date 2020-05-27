#include "setup.h"

Setup::Setup(QObject *parent) : QObject(parent)
{

}

Setup::Setup(QQmlApplicationEngine *e, lambdaClient* lambda)
{
    _lambda = lambda;
    engine = e;


}

void Setup::joinClassroom(QString code, QString name)
{
  _classCode = code;
  _name = name;

  if (_classCode != "" && _name != "") {
                qDebug() << "true";
       emit filledOut(true);
  } else {
                qDebug() << "false";
       emit filledOut(false);
  }


}
