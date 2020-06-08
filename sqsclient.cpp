#include "sqsclient.h"

SqsClient::SqsClient(QObject *parent) : QObject(parent)
{

}

void SqsClient::startPolling(Aws::String queueUrl)
{
    sqsUrl = queueUrl;
    future = QtConcurrent::run(this, &SqsClient::start);

}

SqsClient::~SqsClient()
{
    qDebug() << "Cancelling Polling Thread" << endl;
    future.cancel();
}

void SqsClient::closePolling()
{
    closeThread = true;
    if(future.isRunning()) {
        qDebug() << "Clean Exit";
        future.waitForFinished();
    }
    qDebug() << future.isFinished() << endl;
}


void SqsClient::start() {
    Aws::String queue_url = sqsUrl;
    Aws::SQS::Model::ReceiveMessageRequest rm_req;
    Aws::SQS::Model::SetQueueAttributesRequest request;
    rm_req.SetQueueUrl( queue_url );
    rm_req.SetMaxNumberOfMessages(1);
    request.SetQueueUrl(queue_url);
    Aws::String poll_time = "400";
    request.AddAttributes(Aws::SQS::Model::QueueAttributeName::ReceiveMessageWaitTimeSeconds, "10");
    auto outcome = SetQueueAttributes(request);
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

        auto rm_out = ReceiveMessage(rm_req);


        if (!rm_out.IsSuccess())
        {
            std::cout << "Error receiving message from queue " << queue_url << ": "
                      << rm_out.GetError().GetMessage() << std::endl;
            return;
        }


        const auto& messages = rm_out.GetResult().GetMessages();


        if (closeThread) {
            break;
        }
        if (messages.size() == 0)
        {

            std::cout << "No messages received from queue " << queue_url <<
                         std::endl;
        } else {
            const auto& message = messages[0];


            Aws::String d = message.GetMessageId();
            Aws::String a = message.GetBody();

            Aws::Utils::Json::JsonValue bodyObject(message.GetBody());


            util.convertStdStringToQString( util.convertAWSStringToStdString(bodyObject.View().GetString("Message")));

            emit newMessage( util.convertStdStringToQString( util.convertAWSStringToStdString(a)) );

            Aws::SQS::Model::DeleteMessageRequest dm_req;
            dm_req.SetQueueUrl(queue_url);
            dm_req.SetReceiptHandle(message.GetReceiptHandle());

            auto dm_out = DeleteMessage(dm_req);
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



    } while (closeThread == false);

    return;


}

void SqsClient::sendMessage(Aws::String url, Aws::String message)
{

    Aws::SQS::Model::SendMessageRequest sm_req;
    sm_req.SetQueueUrl(url);
    sm_req.SetMessageBody(message);

    auto sm_out = SendMessage(sm_req);
    if (sm_out.IsSuccess())
    {
        std::cout << "Successfully sent message to " << url <<
                     std::endl;
    }
    else
    {
        std::cout << "Error sending message to " << url << ": " <<
                     sm_out.GetError().GetMessage() << std::endl;
    }
}

void SqsClient::purgeQueue(Aws::String url)
{
    Aws::SQS::Model::PurgeQueueRequest pq_req;
    pq_req.SetQueueUrl(url);

    auto pq_out = PurgeQueue(pq_req);
    if (pq_out.IsSuccess())
    {
        std::cout << "Successfully purged queue " << std::endl;
    }
    else
    {
        std::cout << "Error purging queue " << pq_out.GetError().GetMessage()
                  << std::endl;
    }
}
