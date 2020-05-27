#ifndef SNSCLIENT_H
#define SNSCLIENT_H

#include <aws/core/Aws.h>
#include <aws/sns/SNSClient.h>
#include <aws/sns/model/GetTopicAttributesRequest.h>
#include <aws/sns/model/GetTopicAttributesResult.h>
#include <aws/sns/model/ListTopicsRequest.h>
#include <aws/sns/model/ListTopicsResult.h>
#include <stdexcept>
//#include <string>
//#include <iostream>



class SnsClient : public Aws::SNS::SNSClient  {
public:
    SnsClient(Aws::Client::ClientConfiguration config) : Aws::SNS::SNSClient(config) {
        //do nothing
    };
    ~SnsClient();
    void checkConnection();
};

#endif // SNSCLIENT_H
