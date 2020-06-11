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
#include <QDebug>
#include <QString>
#include "utilityfunctions.h"



class lambdaClient : public Aws::Lambda::LambdaClient {
public:
    lambdaClient();
    lambdaClient(Aws::Client::ClientConfiguration config) : Aws::Lambda::LambdaClient(config) {
    };
    joinClassroomPayload joinClassroom(Aws::String name, Aws::String code);
    intitalizeClassroomPayload intializeUser(Aws::String studentId, Aws::String classmoorId);
    classCheckPayload checkInStudent(Aws::String student_id, Aws::String classroom_id);
    clastimeUpdatePayload updateClasstime(Aws::String classtimeId, Aws::String classroomId);
    classaskResponsePayload postQuestion(Aws::String questionText, bool isAnon, Aws::String classtimeId, userCredentials creds);
    bool leaveClasstime(Aws::String studentId, Aws::String classtimeId, Aws::String classroomId, Aws::String tempSQSUrl);
    bool checkConnection();
    intitalizeClasstimePayload getClasstimeDetails( userCredentials v );
    std::string getLastFunctionResult();

private:
    std::string lastFunctionResult;
    UtilityFunctions util;

    //Debug Functions
    void printPayload(normalPayload v);
    void printIntitalizeClassroomPayload(intitalizeClassroomPayload v);
    void printJoinClassroomPayload(joinClassroomPayload v);
    void printClassCheckPayload(classCheckPayload v);
    void printClassTimePayload(intitalizeClasstimePayload v);
    void printClassTimeUpdatePayload(clastimeUpdatePayload v);
};

#endif // LAMBDACLIENT_H
