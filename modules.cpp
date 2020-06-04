#include "modules.h"

Modules::Modules(QObject *parent) : QObject(parent) {
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "us-west-1";

    lambda_client = new lambdaClient(clientConfig);

    clientConfig.requestTimeoutMs = 30000000;
    sqs_client = new SqsClient(clientConfig);

    qDebug() << "Intializing Modules";

}


void Modules::runIntialization()
{

    //PreReq: Check Connections
    //LAMBDA:
    lambda_client->checkConnection();
    //Step 1: Read from user data file;
    readFromFile();

    //Step 3: Subscribe to SNS Topic

    //Step 2: Pass that to lambda intializeUser;
    try {
        intialLoad = lambda_client->intializeUser(creds.studentId, creds.classmoorId);
        timeInSeconds = intialLoad.timeRemaining;
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

     activateTimer();
    //Step 2a: Configure States and possible variations
    intalizeState();
    //Step 3: Open a thread to QT to run polling
//    connect(this, &Modules::newMessage, this, &Modules::recievedMessage, Qt::QueuedConnection);
//    Aws::String msg;
    QFuture<void> future = QtConcurrent::run(this, &Modules::startPolling);



}

//void Modules::handleFinish() {

//}

void Modules::intalizeState()
{

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

void Modules::startPolling() {
    Aws::String queue_url = creds.client_sqs;
    Aws::SQS::Model::ReceiveMessageRequest rm_req;
    Aws::SQS::Model::SetQueueAttributesRequest request;
    rm_req.SetQueueUrl( queue_url );
    rm_req.SetMaxNumberOfMessages(1);
    request.SetQueueUrl(queue_url);
    Aws::String poll_time = "400";
    request.AddAttributes(Aws::SQS::Model::QueueAttributeName::ReceiveMessageWaitTimeSeconds, "20");
    auto outcome = sqs_client->SetQueueAttributes(request);
    if (outcome.IsSuccess())
    {
        std::cout << "Successfully updated long polling time for queue " <<
                     queue_url << " to " << poll_time << std::endl;
    }
    else
    {
        std::cout << "Error updating long polling time for queue " <<
                     queue_url << ": " << outcome.GetError().GetMessage() <<
                     std::endl;
    }


    do {
        qDebug() << "Starting Poll For Messages" << endl;
        auto rm_out = sqs_client->ReceiveMessage(rm_req);
        if (!rm_out.IsSuccess())
        {
            std::cout << "Error receiving message from queue " << queue_url << ": "
                      << rm_out.GetError().GetMessage() << std::endl;
            return;
        }


        qDebug() << "Repolling" << endl;
        const auto& messages = rm_out.GetResult().GetMessages();
        if (messages.size() == 0)
        {

            std::cout << "No messages received from queue " << queue_url <<
                         std::endl;


        } else {
            const auto& message = messages[0];
            Aws::String d = message.GetMessageId();

            Aws::String a = message.GetBody();
            std::cout << d << " " << a << std::endl;
            if (a == "newClasstime") {
                emit newMessage( util.convertStdStringToQString( util.convertAWSStringToStdString( a)));
            }
            Aws::SQS::Model::DeleteMessageRequest dm_req;
            dm_req.SetQueueUrl(queue_url);
            dm_req.SetReceiptHandle(message.GetReceiptHandle());

            auto dm_out = sqs_client->DeleteMessage(dm_req);
            if (dm_out.IsSuccess())
            {
                std::cout << "Successfully deleted message " << message.GetMessageId()
                          << " from queue " << queue_url << std::endl;
            }
            else
            {
                std::cout << "Error deleting message " << message.GetMessageId() <<
                             " from queue " << queue_url << ": " <<
                             dm_out.GetError().GetMessage() << std::endl;
            }
        }



    } while (true);








}

void Modules::activateTimer()
{
    activeTimer = new QTimer(this);
    activeTimer->setInterval(1000);
    connect(activeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    activeTimer->start();
}


bool Modules::readFromFile()
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

        creds.classmoorId = util.convertQStringToAWSString( list[2]);
        creds.client_sqs = util.convertQStringToAWSString(list[3]);
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
        intialLoad = lambda_client->intializeUser(creds.studentId, creds.classmoorId);
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

}

void Modules::intialize()
{
    runIntialization();
}

void Modules::updateTime()
{

    timeInSeconds -= 1;
    emit updateTimer(timeInSeconds);
}


void Modules::recievedMessage(QString m)
{
    if (m == "newClasstime" && intialLoad.isCheckedIn) {
        emit changeState(1, util.convertStdStringToQString(intialLoad.lastCheckin),  util.convertStdStringToQString(intialLoad.lastClasstime), 32323);
    }
}

void Modules::handleCheckin()
{
    // Handle Checkin
    // Step 1: Hit Lambda Function with Update
    classCheckPayload response;
    try {
        qDebug() << "Handling Checkin";
        response =  lambda_client->checkInStudent(creds.studentId, creds.classmoorId);
        intialLoad.isCheckedIn = false;
        intialLoad.lastCheckin = response.classCheckMessage;
        intalizeState();
        activeTimer->stop();
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

}

