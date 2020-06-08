#include "classtime.h"

Classtime::Classtime(QObject *parent) : QObject(parent)
{
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "us-west-1";

    lambda_client = new lambdaClient(clientConfig);

    clientConfig.requestTimeoutMs = 30000000;
    sqs_client = new SqsClient(clientConfig);

    qDebug() << "Intializing Classtime";
}

void Classtime::retrieveClasstimeDetails()
{

    try {
        readFromFile();
        // Step 1: Retrieve the details for classtime
        intialLoad = lambda_client->getClasstimeDetails(creds);
        qint64 d = QDateTime::currentSecsSinceEpoch();
        timeInSeconds = d - intialLoad.timeElapsed;

        activateTimer();

        emit updateComponents( util.convertStdStringToQString(intialLoad.classtimeLessonHeader), util.convertStdStringToQString(intialLoad.classtimeLessonResource), intialLoad.numOfParticipants );

        connect(&(*sqs_client), &SqsClient::newMessage, this, &Classtime::recievedMessage, Qt::QueuedConnection);
        sqs_client->startPolling(creds.client_sqs);
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }


}

void Classtime::updateTime()
{
    timeInSeconds += 1;
    emit updateTimer(timeInSeconds);
}

void Classtime::leaveClasstime()
{
    try {
        bool result = false;
        result = lambda_client->leaveClasstime( creds.studentId, util.convertStdStringToAWSString( intialLoad.classtimeId ), creds.client_sqs);
        if (result) {

        }
    } catch (std::exception e) {
        qDebug() << e.what() << endl;
    }
}

void Classtime::recievedMessage(QString m)
{
    qDebug() << "Recieved Message: " << m << endl;
    if (m == "updateClasstime") {
        // Create new thread to handle this as it will timeout before finished as the polling will the


        Aws::String classtime_id = util.convertStdStringToAWSString( intialLoad.classtimeId);
        Aws::String classroom_id = creds.classroomId;


        QFutureWatcher<clastimeUpdatePayload> watcher;

        QFuture<clastimeUpdatePayload> future = QtConcurrent::run(this, &Classtime::runUpdateThreadedFunction, classtime_id, classroom_id);

        watcher.setFuture(future);

        watcher.waitForFinished();
        intialLoad.numOfParticipants = future.result().numOfParticipants;
        intialLoad.classtimeLessonHeader = future.result().classtimeLessonHeader;
        intialLoad.classtimeLessonResource = future.result().classtimeLessonResource;

        qDebug() << future.result().numOfParticipants;
        emit updateComponents( util.convertStdStringToQString(intialLoad.classtimeLessonHeader), util.convertStdStringToQString(intialLoad.classtimeLessonResource), intialLoad.numOfParticipants );


    } else if (m == "ping") {
        sqs_client->sendMessage( creds.confirmation_client_sqs, creds.studentId );
    }
}

clastimeUpdatePayload Classtime::runUpdateThreadedFunction( Aws::String classtimeId, Aws::String classroomId ) {
      qDebug() << "In Update Classtime" << QThread::currentThread();
    return lambda_client->updateClasstime( classtimeId, classroomId );
}

bool Classtime::readFromFile()
{
    try {
        LinkedList<QString> list;
        QFile inputFile("user_data.txt");
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


void Classtime::activateTimer()
{
    activeTimer = new QTimer(this);
    activeTimer->setInterval(1000);
    connect(activeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    activeTimer->start();
}
