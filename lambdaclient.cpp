#include "lambdaclient.h"

lambdaClient::lambdaClient()
{

}

void lambdaClient::checkConnection() {

       Aws::String functionName = "classmoor-api-prod";
       Aws::Client::ClientConfiguration clientConfig;
       clientConfig.region = "us-west-1";
       Aws::Lambda::LambdaClient m_client(clientConfig);

       Aws::Lambda::Model::InvokeRequest invokeRequest;
       invokeRequest.SetFunctionName(functionName);
       invokeRequest.SetInvocationType(Aws::Lambda::Model::InvocationType::RequestResponse);
       invokeRequest.SetLogType(Aws::Lambda::Model::LogType::Tail);
       std::shared_ptr<Aws::IOStream> payload = Aws::MakeShared<Aws::StringStream>("FunctionTest");
       Aws::Utils::Json::JsonValue jsonPayload;
       jsonPayload.WithString("test", "TestFromClient");
       *payload << jsonPayload.View().WriteReadable();
       invokeRequest.SetBody(payload);
       invokeRequest.SetContentType("application/javascript");

       auto outcome = Invoke(invokeRequest);

       if (outcome.IsSuccess()) {
           auto &result = outcome.GetResult();

           // Lambda function result (key1 value)
           Aws::IOStream& payload = result.GetPayload();
           Aws::String functionResult;
           std::getline(payload, functionResult);
           std::cout << functionResult << "\n\n";

       } else {
           throw std::runtime_error("Unable to connect to lambda");
       }
}
