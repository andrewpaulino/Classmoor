#include "snsclient.h"

void SnsClient::checkConnection() {
    //Should Be class SNS development
    Aws::String topic_arn = "arn:aws:sns:us-west-1:958123219673:Classmoor-dave-class";

    Aws::SNS::Model::GetTopicAttributesRequest gta_req;
    gta_req.SetTopicArn(topic_arn);

    auto gta_out = GetTopicAttributes(gta_req);

    if (gta_out.IsSuccess()) {
      std::cout << "SNS Client Connected to US-West-1" << std::endl;
    } else {
        throw std::runtime_error("Unable to connect to SDK");
    }

}

SnsClient::~SnsClient() {

}
