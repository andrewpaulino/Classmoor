#include "dynamoclient.h"

DynamoClient::DynamoClient()
{

}

void DynamoClient::checkConnection() {
    Aws::DynamoDB::Model::ListTablesRequest ltr;
    ltr.SetLimit(50);

    const Aws::DynamoDB::Model::ListTablesOutcome& lto = ListTables(ltr);

    if (!lto.IsSuccess()){
        throw std::runtime_error("Unable to connect to DynamoDB");
    }

    std::cout << "DynamoDB Client Connected to US-West-1" << std::endl;

}
