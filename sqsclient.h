#ifndef SQSCLIENT_H
#define SQSCLIENT_H
#include <aws/core/Aws.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/ReceiveMessageRequest.h>
#include <aws/sqs/model/ReceiveMessageResult.h>
#include <aws/sqs/model/SetQueueAttributesRequest.h>
#include <aws/sqs/model/DeleteMessageRequest.h>
#include <iostream>

class SqsClient : public Aws::SQS::SQSClient
{
public:
    SqsClient(Aws::Client::ClientConfiguration c) : Aws::SQS::SQSClient(c){};
    SqsClient();
};

#endif // SQSCLIENT_H
