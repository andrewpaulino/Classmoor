#include "classtime.h"

Classtime::Classtime(QObject *parent) : QObject(parent)
{
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "us-west-1";

    lambda_client = new lambdaClient(clientConfig);

    // Setting Request Timeout
    clientConfig.requestTimeoutMs = 30000000;
    sqs_client = new SqsClient(clientConfig);

    qDebug() << "Intializing Classtime";
}

void Classtime::retrieveClasstimeDetails()
{

    try {

        // Read User file credentials
        readFromFile();

        // Retrieve User Data
        intialLoad = lambda_client->getClasstimeDetails(creds);
        qint64 secondsSinceMS = QDateTime::currentSecsSinceEpoch();

        // Time in seconds to count UP based on elapsed
        timeInSeconds = secondsSinceMS - intialLoad.timeElapsed;

        // Activiating Timer
        activateTimer();

        // New UI Change
        emit updateComponents( util.convertStdStringToQString(intialLoad.classtimeLessonHeader), util.convertStdStringToQString(intialLoad.classtimeLessonResource), intialLoad.numOfParticipants );

        // Handling Signal and Slots, making sure new message will be directed to -> recievedMessage
        connect(&(*sqs_client), &SqsClient::newMessage, this, &Classtime::recievedMessage, Qt::QueuedConnection);
        sqs_client->startPolling( util.convertStdStringToAWSString( intialLoad.classtimeSQSUrl));

    } catch (std::exception e) {
        qDebug() << e.what() << endl;
    }


}

void Classtime::updateTime()
{

    //Updating State
    timeInSeconds += 1;
    emit updateTimer(timeInSeconds);
}

void Classtime::postQuestion(QString questionText, bool isAnon) {

    try {
        classaskResponsePayload response;

        // Posting a question to the backend from qml file
        response = lambda_client->postQuestion( util.convertQStringToAWSString(questionText), isAnon, util.convertStdStringToAWSString( intialLoad.classtimeId), creds);

        // User validation
        if (response.statusCode == 200) {
            emit messageSentConfirmed();
        } else {
            emit messageSentFailed();
        }
    } catch  (std::exception e){
        qDebug() << e.what() << endl;
    }
}

void Classtime::leaveClasstime()
{
    try {
        bool result = false;

        // Tell backend, we are not online.
        result = lambda_client->leaveClasstime( creds.studentId, util.convertStdStringToAWSString( intialLoad.classtimeId ), creds.classroomId, util.convertStdStringToAWSString(intialLoad.classtimeSQSUrl));

    } catch (std::exception e) {
        qDebug() << e.what() << endl;
    }
}

void Classtime::recievedMessage(QString m)
{
    // Our Slot from, SQSClient class.
    qDebug() << "Classtime: New Message " << m << endl;
    if (m == "updateClasstime") {

        // Getting Credentials
        Aws::String classtime_id = util.convertStdStringToAWSString( intialLoad.classtimeId);
        Aws::String classroom_id = creds.classroomId;


        // Watcher for future values
        QFutureWatcher<clastimeUpdatePayload> watcher;

        // Multi-threaded Process, handling using concurrency based.
        // Putting thread in different thread pool so non-blocking process
        // can continue.
        QFuture<clastimeUpdatePayload> future = QtConcurrent::run(this, &Classtime::runUpdateThreadedFunction, classtime_id, classroom_id);
        watcher.setFuture(future);
        watcher.waitForFinished();

        // Retriving values from our watcher after completed function
        // This is meant for a handshake between our serverless lambda's and
        // our databases.
        // Note: Lambda Could timeout, 15 second timeout
        intialLoad.numOfParticipants = future.result().numOfParticipants;
        intialLoad.classtimeLessonHeader = future.result().classtimeLessonHeader;
        intialLoad.classtimeLessonResource = future.result().classtimeLessonResource;

        // Awaiting Future of Lambda Handshake between SQS and confirmation SQS Queue.
        emit updateComponents( util.convertStdStringToQString(intialLoad.classtimeLessonHeader), util.convertStdStringToQString(intialLoad.classtimeLessonResource), intialLoad.numOfParticipants );
    } else if (m == "ping") {

        // Once we recieve Ping we send back in different thread
        sqs_client->sendMessage( creds.confirmation_client_sqs, creds.studentId );
    } else if (m == "endClasstime") {
        // Close polling & Clean up
        sqs_client->closePolling();

        // Leave Stack View
        emit endClasstime();
    }
}

clastimeUpdatePayload Classtime::runUpdateThreadedFunction( Aws::String classtimeId, Aws::String classroomId ) {
    qDebug() << "Classtime: Threading, await for updating from AWS Lambda non-blocking" << QThread::currentThread();
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
                // Read Line
                list.push(in.readLine());
            }
            inputFile.close();
        }

        // Extracting from linked List
        // - ClassroomId
        // - Client SQS
        // - Confirmation Client SQS
        // - StudentId

        creds.classroomId = util.convertQStringToAWSString( list[2]);
        creds.client_sqs = util.convertQStringToAWSString(list[3]);
        creds.confirmation_client_sqs = util.convertQStringToAWSString(list[4]);
        creds.studentId = util.convertQStringToAWSString(list[1]);

        return true;
    } catch (std::exception e) {
        qDebug() << e.what() << endl;
        return false;
    }

}

Classtime::~Classtime()
{
    qDebug() << "Classtime: Exiting Polling" << endl;
    sqs_client->closePolling();
}


void Classtime::activateTimer()
{

    // Initializing QT Timer
    activeTimer = new QTimer(this);
    activeTimer->setInterval(1000);
    connect(activeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    activeTimer->start();
}
