#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <aws/core/Aws.h>
#include <QDebug>
#include <QString>

// Payload Definitions
typedef struct normalPayload {
    int statusCode;
    std::string bodyResponse;
} normalPayload;

typedef struct joinClassroomPayload {
    int statusCode;
    std::string classroomId;
    std::string classSNSArn;
    std::string bodyResponse;
    std::string studentId;
    std::string classConfirmationSNSArn;
} joinClassroomPayload;

typedef struct intitalizeClasstimePayload {
    int statusCode;
    std::string classtimeLessonHeader;
    int numOfParticipants;
    int timeElapsed;
    std::string classtimeSQSUrl;
    std::string classtimeId;
    std::string bodyResponse;
    std::string classtimeLessonResource;
} intitalizeClasstimePayload;

typedef struct clastimeUpdatePayload {
    std::string classtimeLessonHeader;
    int numOfParticipants;
    std::string classtimeLessonResource;
    std::string bodyResponse;
    int statusCode;
}clastimeUpdatePayload;

typedef struct intitalizeClassroomPayload {
    bool isClasstime;
    bool isCheckedIn;
    std::string bodyResponse;
    int statusCode;
    std::string lastCheckin;
    std::string lastClasstime;
    int timeRemaining;
} intitalizeClassroomPayload;

typedef struct classCheckPayload {
    std::string bodyResponse;
    int statusCode;
    std::string classCheckMessage;
} classCheckPayload;


typedef struct classaskResponsePayload {
    std::string bodyResponse;
    int statusCode;
}classaskResponsePayload;

typedef struct userCredentials {
    Aws::String client_sqs;
    Aws::String classroomId;
    Aws::String studentId;
    Aws::String confirmation_client_sqs;
} userCredentials;

class UtilityFunctions
{
public:
    UtilityFunctions();

    // String Conversation for different namespsaces (AWS, QString, std::string)
    std::string convertAWSStringToStdString (Aws::String v);
    QString convertStdStringToQString(std::string v);
    Aws::String convertStdStringToAWSString(std::string v);
    Aws::String convertQStringToAWSString(QString v);
    std::string convertQStringToStdString(QString v);
};

#endif // UTILITYFUNCTIONS_H
