#include "lambdaclient.h"

lambdaClient::lambdaClient()
{

}

bool lambdaClient::joinClassroom(Aws::String name, Aws::String code)
{

    Aws::String functionName = "classmoor-api-prod";


    Aws::Lambda::Model::InvokeRequest invokeRequest;
    invokeRequest.SetFunctionName(functionName);
    invokeRequest.SetInvocationType(Aws::Lambda::Model::InvocationType::RequestResponse);
    invokeRequest.SetLogType(Aws::Lambda::Model::LogType::Tail);
    std::shared_ptr<Aws::IOStream> payload = Aws::MakeShared<Aws::StringStream>("body");

    Aws::Utils::Json::JsonValue bodyObject;
    bodyObject.WithString("clientPath", "joinClassroom");
    bodyObject.WithString("classCode", code);
    bodyObject.WithString("studentName", name);

    Aws::Utils::Json::JsonValue jsonPayload;
    jsonPayload.WithObject("body", bodyObject);


    *payload << jsonPayload.View().WriteReadable();

    invokeRequest.SetBody(payload);
    invokeRequest.SetContentType("application/javascript");

    auto outcome = Invoke(invokeRequest);

    if (outcome.IsSuccess()) {
        auto &result = outcome.GetResult();
        Aws::IOStream& payload = result.GetPayload();
        Aws::String functionResult;
        std::getline(payload, functionResult);
        std::string _lastFunctionResult(functionResult.c_str(), functionResult.size());

        lastFunctionResult = _lastFunctionResult;

        QString temp = QString::fromStdString(lastFunctionResult);
        qDebug() << temp;



        return true;
    } else {
        throw std::runtime_error("Unable to connect to lambda");
    }

}

bool lambdaClient::checkConnection() {

       Aws::String functionName = "classmoor-api-prod";

       Aws::Lambda::Model::InvokeRequest invokeRequest;
       invokeRequest.SetFunctionName(functionName);
       invokeRequest.SetInvocationType(Aws::Lambda::Model::InvocationType::RequestResponse);
       invokeRequest.SetLogType(Aws::Lambda::Model::LogType::Tail);
       std::shared_ptr<Aws::IOStream> payload = Aws::MakeShared<Aws::StringStream>("FunctionTest");

       Aws::Utils::Json::JsonValue bodyObject;
       bodyObject.WithString("clientPath", "testConnection");
       Aws::Utils::Json::JsonValue jsonPayload;
       jsonPayload.WithObject("body", bodyObject);

       *payload << jsonPayload.View().WriteReadable();
       invokeRequest.SetBody(payload);
       invokeRequest.SetContentType("application/javascript");

       auto outcome = Invoke(invokeRequest);

       if (outcome.IsSuccess()) {
           auto &result = outcome.GetResult();

           Aws::IOStream& payload = result.GetPayload();
           Aws::String functionResult;
           std::getline(payload, functionResult);
           std::string _lastFunctionResult(functionResult.c_str(), functionResult.size());

           lastFunctionResult = _lastFunctionResult;

           QString temp = QString::fromStdString(lastFunctionResult);
           qDebug() << temp;

           return true;
       } else {
           throw std::runtime_error("Unable to connect to lambda");
       }

}

std::string lambdaClient::getLastFunctionResult()
{
    return lastFunctionResult;
}
