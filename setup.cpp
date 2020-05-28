#include "setup.h"

Setup::Setup(QObject *parent) : QObject(parent)
{
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "us-west-1";
    lambda_client = new lambdaClient(clientConfig);
}

bool Setup::writeToFile(const QString &data)
{

    QString filename = "user_data.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << data << endl;
        return true;
    }
}


void Setup::joinClassroom(QString code, QString name)
{
  _classCode = code;
  _name = name;

  if (_classCode != "" && _name != "") {
       emit filledOut(true);
       std::string n = name.toStdString();
       std::string c = code.toStdString();
       QString result;
       Aws::String awsName(n.c_str(), n.size());
       Aws::String awsCode(c.c_str(), c.size());
       bool isDone = false;

       try {
           isDone = lambda_client->joinClassroom(awsName, awsCode);
           result = QString::fromStdString(lambda_client->getLastFunctionResult());
       } catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
       }

       if(isDone && lambda_client->getLastFunctionResult() == "404") {

           emit results(false, true);
       } else {
           bool isDoneWritting = false;
           isDoneWritting = writeToFile(result);
           qDebug() << isDoneWritting;
           if (isDoneWritting) {
                emit results(true, true);
                emit doneWithSetup(true);
           }

       }


  } else {
       emit filledOut(false);
  }


}
