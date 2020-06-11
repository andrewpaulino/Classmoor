import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import com.classmoor.classtime 1.0

Item {

    id: classtimeInterface
    visible: true
    width: 1310
    height: 768

    Classtime {
        id: classtime
        onUpdateTimer: {

            // {seconds} => {hours}::{minutes}::{seconds}
            let tempTime = timeInSeconds;
            let hours, minutes, seconds;

            hours = Math.floor( tempTime/3600 );
            tempTime = tempTime%3600;

            minutes = Math.floor( tempTime/60 );
            tempTime = tempTime % 60;
            seconds = tempTime;


            classtimeUi.timeText.text = hours + " Hours and " + minutes + " minutes and " + seconds + " seconds";
        }
        onUpdateComponents: {

            classtimeUi.participants.text = numOfParticipants;
            classtimeUi.lessonHeader.text = lessonHeader;
            classtimeUi.webView.url = lessonResource;

        }
        onEndClasstime: {
            stackView.push('Modules.qml');
        }

        onMessageSentConfirmed: {
            classtimeUi.messageSent = true;

        }
        onMessageSentFailed: {
            classtimeUi.messageFailed = true;


        }
    }

    ClasstimeUI {
        id: classtimeUi
        anchors.fill: parent
        background: Rectangle {
            color:"#F5F5F5"
        }
        leaveButtonMouseArea.onPressed: {
            stackView.push("Modules.qml");
            classtime.leaveClasstime();
        }
        askButtonMouseArea.onPressed: {
            if (classtimeUi.questionField.text !== "") {
                classtimeUi.noInputInQuestionField = false;
                classtime.postQuestion(questionField.text, classtimeUi.anonSwitch.position == 0.0 ? false : true);
            } else {
                classtimeUi.noInputInQuestionField = true;
            }


        }

    }

    Component.onCompleted: classtime.retrieveClasstimeDetails();

}
