#include "modules.h"

Modules::Modules(QObject *parent) : QObject(parent) {
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "us-west-1";

    lambda_client = new lambdaClient(clientConfig);

    clientConfig.requestTimeoutMs = 30000000;
    sqs_client = new SqsClient(clientConfig);

    qDebug() << "Intializing Modules";

}

Modules::~Modules()
{
    qDebug() << "DESTROYING MODULES" << endl;
    sqs_client->closePolling();
}


void Modules::runIntialization()
{
    // Check If we can connect to classmoor services...
    if (lambda_client->checkConnection()) {

        try {
            // Read UserData, and save it to the class credentials.
            readFromFile();

            // Retrieve user information, and save it to the class.
            intialLoad = lambda_client->intializeUser(creds.studentId, creds.classroomId);

            // Purge the Queue, so when application starts over; we will recieve new updates.
            sqs_client->purgeQueue(  creds.client_sqs );

            // Convert time for timer
            timeInSeconds = intialLoad.timeRemaining;

            // Activate timer and start countdown for checkin feature
            activateTimer();

            // Intialize States and views
            intalizeState();

            // Connect Signal and slots of application to each other.
            connect(&(*sqs_client), &SqsClient::newMessage, this, &Modules::recievedMessage, Qt::QueuedConnection);

            //Start polling to the classmoor Class SNS and then run on seperate thread.
            sqs_client->startPolling(creds.client_sqs);
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }





}

void Modules::intalizeState()
{

    // Initializing States For View Port
    if (intialLoad.isClasstime && intialLoad.isCheckedIn) {
        qDebug() << "ClassTime Is in session and you should be eligible to check in" << endl;
        emit changeState(1, util.convertStdStringToQString(intialLoad.lastCheckin),  util.convertStdStringToQString(intialLoad.lastClasstime), intialLoad.timeRemaining);
    } else if (intialLoad.isClasstime && !intialLoad.isCheckedIn) {
        qDebug() << "ClassTime Is in session and you should be NOT eligible to check in" << endl;
        emit changeState(2, util.convertStdStringToQString(intialLoad.lastCheckin),  util.convertStdStringToQString(intialLoad.lastClasstime), intialLoad.timeRemaining);
    } else if (!intialLoad.isClasstime && intialLoad.isCheckedIn) {
        qDebug() << "ClassTime Is NOT session and you should be eligible to check in" << endl;
        emit changeState(3, util.convertStdStringToQString(intialLoad.lastCheckin),  util.convertStdStringToQString(intialLoad.lastClasstime), intialLoad.timeRemaining);
    } else if (!intialLoad.isClasstime && !intialLoad.isCheckedIn){
        qDebug() << "ClassTime Is NOT session and you should be NOT BE ELIGIBLE check in" << endl;
        emit changeState(4, util.convertStdStringToQString(intialLoad.lastCheckin),  util.convertStdStringToQString(intialLoad.lastClasstime), intialLoad.timeRemaining);
    }

}

void Modules::activateTimer()
{
    // Intialized a timer from qt Library
    activeTimer = new QTimer(this);
    activeTimer->setInterval(1000);

    // Connect SIGNAL to SLOT
    // When timeout is reached, then time will be updated through class
    connect(activeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    activeTimer->start();
}



bool Modules::readFromFile()
{
    try {
        LinkedList<QString> list;
        QFile inputFile("user_data.txt");
        QFileInfo fi("user_data.txt");
        qDebug() << fi.path() << endl;
        if (inputFile.open(QIODevice::ReadOnly))
        {
            QTextStream in(&inputFile);
            while (!in.atEnd())
            {
                list.push(in.readLine());
            }
            inputFile.close();
        }

        creds.classroomId = util.convertQStringToAWSString( list[2]);
        creds.client_sqs = util.convertQStringToAWSString(list[3]);
        creds.confirmation_client_sqs = util.convertQStringToAWSString(list[4]);
        creds.studentId = util.convertQStringToAWSString(list[1]);

        return true;
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
        return false;
    }

}

void Modules::runMessageUpdates()
{
    try {
        intialLoad = lambda_client->intializeUser(creds.studentId, creds.classroomId);
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

}

void Modules::intialize()
{
    runIntialization();
}

//void Modules::joinClasstime()
//{

//    //Create new thread to wait for closing
//    future = QtConcurrent::run(this, &Modules::waitForClosingPollOnThread);

//    watcher.setFuture(future);

//    watcher.waitForFinished();

//    //    delete sqs_client;
//}

void Modules::updateTime()
{

    timeInSeconds -= 1;
    emit updateTimer(timeInSeconds);
}


void Modules::recievedMessage(QString m)
{
    qDebug() << "Recieved Message IN Modules Polling:" << m << endl;
    if (m == "newClasstime" && intialLoad.isCheckedIn) {
        emit changeState(1, util.convertStdStringToQString(intialLoad.lastCheckin),  util.convertStdStringToQString(intialLoad.lastClasstime), 32323);
    } else if (m == "newClasstime" && !intialLoad.isCheckedIn) {
         emit changeState(2, util.convertStdStringToQString(intialLoad.lastCheckin),  util.convertStdStringToQString(intialLoad.lastClasstime), 32323);
    }else if (m == "ping") {
        sqs_client->sendMessage( creds.confirmation_client_sqs, creds.studentId );
    }
}

void Modules::handleCheckin()
{
    // Handle Checkin
    // Step 1: Hit Lambda Function with Update
    classCheckPayload response;
    try {
        qDebug() << "Handling Checkin";
        response =  lambda_client->checkInStudent(creds.studentId, creds.classroomId);
        intialLoad.isCheckedIn = false;
        intialLoad.lastCheckin = response.classCheckMessage;
        intalizeState();
        activeTimer->stop();
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

}
