#include "setup.h"

Setup::Setup(QObject *parent) : QObject(parent)
{
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "us-west-1";
    lambda_client = new lambdaClient(clientConfig);
}

bool Setup::writeToFile(joinClassroomPayload v)
{

    QString filename = "user_data.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << util.convertStdStringToQString(v.studentId) << endl << util.convertStdStringToQString(v.classroomId) << endl << util.convertStdStringToQString(v.classQueueUrl);
        return true;
    }
    return false;
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
           joinClassroomPayload res = lambda_client->joinClassroom(awsName, awsCode);
           if (isDone && res.statusCode == 404) {
               emit results(false, true);
           } else {
               bool isDoneWritting = false;
               isDoneWritting = writeToFile(res);

               if (isDoneWritting) {
                    emit results(true, true);

                    emit doneWithSetup(true);
               }

           }

       } catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
       }



  } else {
       emit filledOut(false);
  }


}

void Setup::restartApplication()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
