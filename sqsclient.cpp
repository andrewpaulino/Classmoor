#include "sqsclient.h"

SqsClient::SqsClient(QObject *parent) : QObject(parent)
{

}

void SqsClient::startPolling(Aws::String queueUrl)
{
    sqsUrl = queueUrl;

    future = QtConcurrent::run(this, &SqsClient::start);
    watcher.setFuture(future);
}

SqsClient::~SqsClient()
{
    watcher.waitForFinished();
    qDebug() << "SQS: Cancelling Polling Thread" << endl;
}

void SqsClient::closePolling()
{
    qDebug() << "SQS: Closing Polls" << endl;
    closeThread = true;
    watcher.waitForFinished();
    qDebug() << "SQS: Is Thread Still Running? " << watcher.isFinished() << endl;
}


bool SqsClient::start() {
    if (closeThread) {
        return true;
    }
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
        std::cout << "SQS: Successfully updated long polling time for queue " <<
                     queue_url << " to " << poll_time << std::endl;
    }
    else
    {
        std::cout << "SQS: Error updating long polling time for queue " <<
                     queue_url << ": " << outcome.GetError().GetMessage() <<
                     std::endl;
    }


    do {
        if (closeThread) {
            break;
        }
        auto rm_out = ReceiveMessage(rm_req);


        if (!rm_out.IsSuccess())
        {
            std::cout << "SQS: Error receiving message from queue " << queue_url << ": "
                      << rm_out.GetError().GetMessage() << std::endl;
            return false;
        }


        const auto& messages = rm_out.GetResult().GetMessages();



        if (messages.size() == 0)
        {
        } else {
            const auto& message = messages[0];


            Aws::String d = message.GetMessageId();
            Aws::String a = message.GetBody();

            Aws::Utils::Json::JsonValue bodyObject(message.GetBody());

            // Emits message to signal
            emit newMessage( util.convertStdStringToQString( util.convertAWSStringToStdString(bodyObject.View().GetString("Message"))));

            Aws::SQS::Model::DeleteMessageRequest dm_req;
            dm_req.SetQueueUrl(queue_url);
            dm_req.SetReceiptHandle(message.GetReceiptHandle());

            auto dm_out = DeleteMessage(dm_req);
            if (dm_out.IsSuccess())
            {
               qDebug() << "Message Deleted" << endl;
               // Delete each message from QUEUE.
             }
            else
            {
                std::cout << "Error deleting message " << message.GetMessageId() <<
                             " from queue " << queue_url << ": " <<
                             dm_out.GetError().GetMessage() << std::endl;
            }
        }



    } while (closeThread == false);

    return true;


}

void SqsClient::sendMessage(Aws::String url, Aws::String message)
{
    // This is to send a message to confirmation SQS Queue
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
    // We purge the queue so we don't get unnessecary
    // Updates from either classtime or automated
    // Updates
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
