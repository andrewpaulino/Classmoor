#include "lambdaclient.h"

lambdaClient::lambdaClient()
{

}

joinClassroomPayload lambdaClient::joinClassroom(Aws::String name, Aws::String code)
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
        Aws::Utils::Json::JsonValue resultObj;
        Aws::IOStream& payload = result.GetPayload();
        resultObj = payload;

        Aws::String statusCode;

        joinClassroomPayload response;

        //Should Expect Normal payload;
        response.statusCode = resultObj.View().GetInt64("statusCode");
        response.bodyResponse = util.convertAWSStringToStdString(resultObj.View().GetString("statusMessage"));
        response.classSNSArn = util.convertAWSStringToStdString(resultObj.View().GetString("classSNSArn"));
        response.classConfirmationSNSArn = util.convertAWSStringToStdString(resultObj.View().GetString("classConfirmationSNSArn"));
        response.classroomId = util.convertAWSStringToStdString(resultObj.View().GetString("classroomId"));
        response.studentId = util.convertAWSStringToStdString(resultObj.View().GetString("studentId"));

        //Note: Remove in final build
        printJoinClassroomPayload(response);

        return response;
    } else {
        throw std::runtime_error("Unable to connect to lambda");
    }

}

intitalizeClassroomPayload lambdaClient::intializeUser(Aws::String studentId, Aws::String classmoorId)
{
    Aws::String functionName = "classmoor-api-prod";


    Aws::Lambda::Model::InvokeRequest invokeRequest;
    invokeRequest.SetFunctionName(functionName);
    invokeRequest.SetInvocationType(Aws::Lambda::Model::InvocationType::RequestResponse);
    invokeRequest.SetLogType(Aws::Lambda::Model::LogType::Tail);
    std::shared_ptr<Aws::IOStream> payload = Aws::MakeShared<Aws::StringStream>("body");

    Aws::Utils::Json::JsonValue bodyObject;
    bodyObject.WithString("clientPath", "intitalizeStudent");
    bodyObject.WithString("classroomId", classmoorId);
    bodyObject.WithString("studentId", studentId);

    Aws::Utils::Json::JsonValue jsonPayload;
    jsonPayload.WithObject("body", bodyObject);


    *payload << jsonPayload.View().WriteReadable();

    invokeRequest.SetBody(payload);
    invokeRequest.SetContentType("application/javascript");

    auto outcome = Invoke(invokeRequest);

    if (outcome.IsSuccess()) {
        auto &result = outcome.GetResult();
        Aws::Utils::Json::JsonValue resultObj;
        Aws::IOStream& payload = result.GetPayload();
        resultObj = payload;

        Aws::String statusCode;

        intitalizeClassroomPayload response;

        //Should Expect Normal payload;
        try {

            response.statusCode = resultObj.View().GetInteger("statusCode");
            response.bodyResponse = util.convertAWSStringToStdString(resultObj.View().GetString("statusMessage"));
            response.isClasstime = resultObj.View().GetBool("isClasstime");
            response.isCheckedIn =  resultObj.View().GetBool("isClasscheck");
            response.lastClasstime = util.convertAWSStringToStdString(resultObj.View().GetString("lastClasstime"));
            response.lastCheckin = util.convertAWSStringToStdString(resultObj.View().GetString("lastCheckedIn"));
            response.timeRemaining = resultObj.View().GetInteger("timeRemaining");

        } catch (std::exception e) {
            qDebug() << e.what() << endl;
        }
        //Note: Remove in final build
        printIntitalizeClassroomPayload(response);

        return response;
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

        Aws::Utils::Json::JsonValue resultObj;
        Aws::IOStream& payload = result.GetPayload();
        resultObj = payload;

        normalPayload response;

        //Should Expect Normal payload;
        response.statusCode = resultObj.View().GetInteger("statusCode");
        response.bodyResponse = util.convertAWSStringToStdString(resultObj.View().GetString("statusMessage"));

        //Note: Remove in final build
        printPayload(response);
        return true;
    } else {
        throw std::runtime_error("Unable to connect to lambda");
    }

}

intitalizeClasstimePayload lambdaClient::getClasstimeDetails(userCredentials v)
{
    Aws::String functionName = "classmoor-api-prod";


    Aws::Lambda::Model::InvokeRequest invokeRequest;
    invokeRequest.SetFunctionName(functionName);
    invokeRequest.SetInvocationType(Aws::Lambda::Model::InvocationType::RequestResponse);
    invokeRequest.SetLogType(Aws::Lambda::Model::LogType::Tail);
    std::shared_ptr<Aws::IOStream> payload = Aws::MakeShared<Aws::StringStream>("body");

    Aws::Utils::Json::JsonValue bodyObject;
    bodyObject.WithString("clientPath", "joinClasstime");
    bodyObject.WithString("studentId", v.studentId);
    bodyObject.WithString("classroomId", v.classroomId);

    Aws::Utils::Json::JsonValue jsonPayload;
    jsonPayload.WithObject("body", bodyObject);


    *payload << jsonPayload.View().WriteReadable();

    invokeRequest.SetBody(payload);
    invokeRequest.SetContentType("application/javascript");

    auto outcome = Invoke(invokeRequest);

    if (outcome.IsSuccess()) {
        auto &result = outcome.GetResult();
        Aws::Utils::Json::JsonValue resultObj;
        Aws::IOStream& payload = result.GetPayload();
        resultObj = payload;

        Aws::String statusCode;

        intitalizeClasstimePayload response;

        //Should Expect Normal payload;
        response.statusCode = resultObj.View().GetInteger("statusCode");
        response.bodyResponse = util.convertAWSStringToStdString(resultObj.View().GetString("statusMessage"));
        response.timeElapsed = resultObj.View().GetInteger("timeStarted");
        response.classtimeSQSUrl = util.convertAWSStringToStdString(resultObj.View().GetString("classtimeSQSUrl"));
        response.classtimeLessonResource = util.convertAWSStringToStdString(resultObj.View().GetString("classtimeLessonResource"));
        response.classtimeLessonHeader = util.convertAWSStringToStdString(resultObj.View().GetString("classtimeLessonHeader"));
        response.classtimeId = util.convertAWSStringToStdString(resultObj.View().GetString("classtimeId"));
        response.numOfParticipants = resultObj.View().GetInteger("numOfParticipants");

        //Note: Remove in final build
        printClassTimePayload(response);

        return response;
    } else {
        throw std::runtime_error("Unable to connect to lambda");
    }
}

std::string lambdaClient::getLastFunctionResult()
{
    return lastFunctionResult;
}

classCheckPayload lambdaClient::checkInStudent(Aws::String student_id, Aws::String classroom_id)
{
    Aws::String functionName = "classmoor-api-prod";


    Aws::Lambda::Model::InvokeRequest invokeRequest;
    invokeRequest.SetFunctionName(functionName);
    invokeRequest.SetInvocationType(Aws::Lambda::Model::InvocationType::RequestResponse);
    invokeRequest.SetLogType(Aws::Lambda::Model::LogType::Tail);
    std::shared_ptr<Aws::IOStream> payload = Aws::MakeShared<Aws::StringStream>("body");

    Aws::Utils::Json::JsonValue bodyObject;
    bodyObject.WithString("clientPath", "checkInStudent");
    bodyObject.WithString("studentId", student_id);
    bodyObject.WithString("classroomId", classroom_id);

    Aws::Utils::Json::JsonValue jsonPayload;
    jsonPayload.WithObject("body", bodyObject);


    *payload << jsonPayload.View().WriteReadable();

    invokeRequest.SetBody(payload);
    invokeRequest.SetContentType("application/javascript");

    auto outcome = Invoke(invokeRequest);

    if (outcome.IsSuccess()) {
        auto &result = outcome.GetResult();
        Aws::Utils::Json::JsonValue resultObj;
        Aws::IOStream& payload = result.GetPayload();
        resultObj = payload;

        Aws::String statusCode;

        classCheckPayload response;

        //Should Expect Normal payload;
        response.statusCode = resultObj.View().GetInteger("statusCode");
        response.bodyResponse = util.convertAWSStringToStdString(resultObj.View().GetString("statusMessage"));
        response.classCheckMessage = util.convertAWSStringToStdString(resultObj.View().GetString("classCheckMessage"));

        //Note: Remove in final build
        printClassCheckPayload(response);

        return response;
    } else {
        throw std::runtime_error("Unable to connect to lambda");
    }
}

clastimeUpdatePayload lambdaClient::updateClasstime(Aws::String classtimeId, Aws::String classroomId)
{
    Aws::String functionName = "classmoor-api-prod";


    Aws::Lambda::Model::InvokeRequest invokeRequest;
    invokeRequest.SetFunctionName(functionName);
    invokeRequest.SetInvocationType(Aws::Lambda::Model::InvocationType::RequestResponse);
    invokeRequest.SetLogType(Aws::Lambda::Model::LogType::Tail);
    std::shared_ptr<Aws::IOStream> payload = Aws::MakeShared<Aws::StringStream>("body");

    Aws::Utils::Json::JsonValue bodyObject;
    bodyObject.WithString("clientPath", "updateClasstime");
    bodyObject.WithString("classtimeId", classtimeId);
    bodyObject.WithString("classroomId", classroomId);

    Aws::Utils::Json::JsonValue jsonPayload;
    jsonPayload.WithObject("body", bodyObject);


    *payload << jsonPayload.View().WriteReadable();

    invokeRequest.SetBody(payload);
    invokeRequest.SetContentType("application/javascript");

    auto outcome = Invoke(invokeRequest);

    if (outcome.IsSuccess()) {
        auto &result = outcome.GetResult();
        Aws::Utils::Json::JsonValue resultObj;
        Aws::IOStream& payload = result.GetPayload();
        resultObj = payload;

        Aws::String statusCode;

        clastimeUpdatePayload response;
        qDebug() << "INSIDE LAMBDA" << resultObj.View().GetInteger("statusCode");
        //Should Expect Normal payload;
        response.statusCode = resultObj.View().GetInteger("statusCode");
        response.bodyResponse = util.convertAWSStringToStdString(resultObj.View().GetString("statusMessage"));
        response.classtimeLessonResource = util.convertAWSStringToStdString(resultObj.View().GetString("classtimeLessonResource"));
        response.classtimeLessonHeader = util.convertAWSStringToStdString(resultObj.View().GetString("classtimeLessonHeader"));
        response.numOfParticipants = resultObj.View().GetInteger("numOfParticipants");

        //Note: Remove in final build
        printClassTimeUpdatePayload(response);

        return response;
    } else {
        throw std::runtime_error("Unable to connect to lambda");
    }
}

bool lambdaClient::leaveClasstime(Aws::String studentId, Aws::String classtimeId, Aws::String sqsUrl)
{
    Aws::String functionName = "classmoor-api-prod";


    Aws::Lambda::Model::InvokeRequest invokeRequest;
    invokeRequest.SetFunctionName(functionName);
    invokeRequest.SetInvocationType(Aws::Lambda::Model::InvocationType::RequestResponse);
    invokeRequest.SetLogType(Aws::Lambda::Model::LogType::Tail);
    std::shared_ptr<Aws::IOStream> payload = Aws::MakeShared<Aws::StringStream>("body");

    Aws::Utils::Json::JsonValue bodyObject;
    bodyObject.WithString("clientPath", "leaveClasstime");
    bodyObject.WithString("studentId", studentId);
    bodyObject.WithString("classtimeId", classtimeId);
    bodyObject.WithString("mainSQSUrl", sqsUrl);

    Aws::Utils::Json::JsonValue jsonPayload;
    jsonPayload.WithObject("body", bodyObject);


    *payload << jsonPayload.View().WriteReadable();

    invokeRequest.SetBody(payload);
    invokeRequest.SetContentType("application/javascript");

    auto outcome = Invoke(invokeRequest);

    if (outcome.IsSuccess()) {
        auto &result = outcome.GetResult();
        Aws::Utils::Json::JsonValue resultObj;
        Aws::IOStream& payload = result.GetPayload();
        resultObj = payload;

        Aws::String statusCode;

        intitalizeClasstimePayload response;

        //Should Expect Normal payload;
        if (resultObj.View().GetInteger("statusCode") == 200) {
            return true;
        }
        return false;
    } else {
        throw std::runtime_error("Unable to connect to lambda");
    }
}

void lambdaClient::printPayload(normalPayload v)
{
    qDebug() << "Normal Payload Response : { \n" << "statusCode: " << v.statusCode << endl << " bodyResponse: " << util.convertStdStringToQString(v.bodyResponse) << endl << "}" << endl;
}

void lambdaClient::printIntitalizeClassroomPayload(intitalizeClassroomPayload v)
{
    qDebug() << "Normal Payload Response : { \n"
             << "statusCode: " << v.statusCode << endl
             << " bodyResponse: " << util.convertStdStringToQString(v.bodyResponse) << endl
             << " isClasstime: " << v.isClasstime << endl
             << " isCheckedIn: " << v.isCheckedIn << endl
             << " lastClasstime: " << util.convertStdStringToQString(v.lastClasstime) << endl
             << " lastCheckin: " << util.convertStdStringToQString(v.lastCheckin) << endl
             << " timeRemaing: " << v.timeRemaining << endl
             << "}" << endl;
}

void lambdaClient::printJoinClassroomPayload(joinClassroomPayload v)
{
    //    qDebug() << "Join Classroom Payload Response : { \n" << "statusCode: " << util.convertStdStringToQString(v.statusCode) << endl << " bodyResponse: " << util.convertStdStringToQString(v.bodyResponse) << endl << " ClassroomSNS: " << util.convertStdStringToQString(v.classroomSNSTopicArn) << endl  << " classroomId: " << util.convertStdStringToQString(v.classroomId) << endl << "}" << endl;
}

void lambdaClient::printClassCheckPayload(classCheckPayload v)
{
    qDebug() << "Normal Payload Response : { \n"
             << "statusCode: " << v.statusCode << endl
             << " bodyResponse: " << util.convertStdStringToQString(v.bodyResponse) << endl
             << " classCheckMessage: " << util.convertStdStringToQString(v.classCheckMessage) << endl
             << "}" << endl;
}

void lambdaClient::printClassTimePayload(intitalizeClasstimePayload v)
{
    qDebug() << "Normal Payload Response : { \n"
             << "statusCode: " << v.statusCode << endl
             << " bodyResponse: " << util.convertStdStringToQString(v.bodyResponse) << endl
             << " classtimeSQSUrl: " << util.convertStdStringToQString(v.classtimeSQSUrl) << endl
             << " classtimeLessonResource: " << util.convertStdStringToQString(v.classtimeLessonResource) << endl
             << " classtimeLessonHeader: " << util.convertStdStringToQString(v.classtimeLessonHeader) << endl
             << " numOfParticipants: " << v.numOfParticipants << endl
             << " timeElapsed: " << v.timeElapsed << endl
             << "}" << endl;
}

void lambdaClient::printClassTimeUpdatePayload(clastimeUpdatePayload v)
{
    qDebug() << "Normal Payload Response : { \n"
             << "statusCode: " << v.statusCode << endl
             << " bodyResponse: " << util.convertStdStringToQString(v.bodyResponse) << endl
             << " classtimeLessonResource: " << util.convertStdStringToQString(v.classtimeLessonResource) << endl
             << " classtimeLessonHeader: " << util.convertStdStringToQString(v.classtimeLessonHeader) << endl
             << " numOfParticipants: " << v.numOfParticipants << endl
             << "}" << endl;
}

