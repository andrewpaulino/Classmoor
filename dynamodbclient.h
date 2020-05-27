#ifndef DYNAMODBCLIENTS_H
#define DYNAMODBCLIENTS_H
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/ListTablesRequest.h>
#include <aws/dynamodb/model/ListTablesResult.h>

#include <stdexcept>

class DynamoDBClients
{
public:
    DynamoDBClients();
    void checkConnection();
};

#endif // DYNAMODBCLIENTS_H
