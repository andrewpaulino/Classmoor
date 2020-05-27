#ifndef LAMBDACLIENT_H
#define LAMBDACLIENT_H
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



class lambdaClient : public Aws::Lambda::LambdaClient {
public:
    lambdaClient();
    lambdaClient(Aws::Client::ClientConfiguration config) : Aws::Lambda::LambdaClient(config) {
        //do nothing
    };
    void checkConnection();
private:
//   std::shared_ptr<Aws::Lambda::LambdaClient> m_client;
};

#endif // LAMBDACLIENT_H
