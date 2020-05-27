#ifndef DYNAMOCLIENT_H
#define DYNAMOCLIENT_H
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/ListTablesRequest.h>
#include <aws/dynamodb/model/ListTablesResult.h>

#include <stdexcept>


class DynamoClient : public  Aws::DynamoDB::DynamoDBClient {
public:
    DynamoClient();
    DynamoClient(Aws::Client::ClientConfiguration config) : Aws::DynamoDB::DynamoDBClient(config) {
        //do nothing
    };
    void checkConnection();
};

#endif // DYNAMOCLIENT_H
