#ifndef SQSCLIENT_H
#define SQSCLIENT_H
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/ReceiveMessageRequest.h>
#include <aws/sqs/model/ReceiveMessageResult.h>
#include <aws/sqs/model/SetQueueAttributesRequest.h>
#include <aws/sqs/model/DeleteMessageRequest.h>
#include <iostream>
#include <QObject>
#include <QDebug>
#include "utilityfunctions.h"
#include <QFuture>
#include <QFutureWatcher>
#include <QList>
#include <QtConcurrent>
#include <aws/sqs/model/SendMessageRequest.h>
#include <aws/sqs/model/SendMessageResult.h>
#include <fstream>


#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/core/utils/logging/DefaultLogSystem.h>
#include <aws/core/utils/logging/AWSLogging.h>
#include <aws/core/utils/HashingUtils.h>
#include <aws/lambda/LambdaClient.h>
#include <aws/lambda/model/CreateFunctionRequest.h>
#include <aws/lambda/model/DeleteFunctionRequest.h>
#include <aws/lambda/model/InvokeRequest.h>
#include <stdexcept>
#include <fstream>
#include <aws/sqs/model/PurgeQueueRequest.h>


class SqsClient : public QObject, public Aws::SQS::SQSClient
{
    Q_OBJECT
public:
    explicit SqsClient(QObject *parent = nullptr);
    void startPolling(Aws::String queueUrl);
    SqsClient(Aws::Client::ClientConfiguration c) : Aws::SQS::SQSClient(c){

    };
    ~SqsClient();
    void closePolling();
    void start();
    void sendMessage(Aws::String url,Aws::String message);
    void purgeQueue(Aws::String url);
private:
    QFuture<void> future;
    UtilityFunctions util;
    Aws::String sqsUrl;
    bool closeThread = false;
signals:
    void newMessage(QString m);

};

#endif // SQSCLIENT_H
