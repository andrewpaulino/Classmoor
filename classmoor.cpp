#include "classmoor.h"

classmoor::classmoor(QQmlApplicationEngine* e) {

    engine = e;

    //Prequesites Checking for stable connection to database and SNS subscription and Lambda Functions
    try {
        Aws::Client::ClientConfiguration clientConfig;
        clientConfig.region = "us-west-1";

        // TODO: Only check if authenticated
//            SnsClient snsClient(clientConfig);
            DynamoClient dynamoClient(clientConfig);
            lambdaClient* lambda = new lambdaClient(clientConfig);

//            snsClient.checkConnection();
            dynamoClient.checkConnection();
            lambda->checkConnection();

            if (isFirstTimeRunning()) {
                     qmlRegisterType<Setup>("com.classmoor.setup", 1, 0, "Setup");
                engine->load(QStringLiteral("qrc:/Setup.qml"));
            } else {
                engine->load(QStringLiteral("qrc:/main.qml"));
            }

    } catch (const std::runtime_error& e) {
         std::cout << e.what() << std::endl;
    }
}


bool classmoor::isFirstTimeRunning() {


    QString pathToUserDataFile = "~/user_data.txt";
    QFileInfo check_file(pathToUserDataFile);
       if (check_file.exists() && check_file.isFile()) {
           return false;
       }
           return true;

}

void classmoor::intiateSetup() {

}

