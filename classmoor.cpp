#include "classmoor.h"

Classmoor::Classmoor(QQmlApplicationEngine* e) {

    engine = e;

    //Prequesites Checking for stable connection to database and SNS subscription and Lambda Functions
    try {
        Aws::Client::ClientConfiguration clientConfig;
        clientConfig.region = "us-west-1";

        // TODO: Only check if authenticated
            if (!isFirstTimeRunning()) {
                //Read TOPIC ARN and pass to snsClient
                //SnsClient snsClient(clientConfig, topicArn);
                //snsClient.checkConnection();
            }

            DynamoClient dynamoClient(clientConfig);
            lambdaClient lambda = lambdaClient(clientConfig);


            dynamoClient.checkConnection();

            bool isLambdaGood = false;
            isLambdaGood = lambda.checkConnection();

            qDebug() << isFirstTimeRunning();
            if (isFirstTimeRunning()) {
                qmlRegisterType<Setup>("com.classmoor.setup", 1, 0, "Setup");
                qmlRegisterType<Classmoor>("com.classmoor.classmoor", 1, 0, "Classmoor");
                engine->load(QStringLiteral("qrc:/Setup.qml"));

            } else {
                engine->load(QStringLiteral("qrc:/main.qml"));
            }

    } catch (const std::runtime_error& e) {
         std::cout << e.what() << std::endl;
    }
}


bool Classmoor::isFirstTimeRunning() {


    QString pathToUserDataFile = "user_data.txt";
    QFileInfo check_file(pathToUserDataFile);
       if (check_file.exists()) {
           return false;
       }
           return true;

}

void Classmoor::checkIfSetupIsCompleted(bool check)
{
    if (check) {
        engine->load(QStringLiteral("qrc:/main.qml"));
    }
}

void Classmoor::intiateSetup() {

}

