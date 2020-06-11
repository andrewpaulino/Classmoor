import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import com.classmoor.modules 1.0

//Application window makes it responsive
Item {
    id: modulesQml
    visible: true
    width: 1310
    height: 768


    ModulesForm {
        id: modulesForm
        anchors.fill: parent
        background: Rectangle {
            color:"#F5F5F5"
        }
        checkInMouseArea.onPressed: {
            backgroundRect.color = "#550bb3"
            modules.handleCheckin();
        }
        joinClasstimeButton.onClicked:  {
            isClasstime = true;
            modulesForm.isDoneLoading = false;
            modulesForm.isStateOne = false;
            modulesForm.isStateTwo = false;
            modulesForm.isStateThree = false;
            modulesForm.isStateFour = false;

            if (!isDoneLoading) {
                stackView.push("ClasstimeInterface.qml");
            }
        }
    }


    Modules {
        id: modules
        onUpdateTimer: {
            let tempTime = timeInSec;
            let hours, minutes, seconds;

            hours = Math.floor( tempTime/3600 );
            tempTime = tempTime%3600;

            minutes = Math.floor( tempTime/60 );
            tempTime = tempTime % 60;
            seconds = tempTime;

            if (minutes < 10) {
                minutes = "0" + minutes;
            }

            if (hours < 10) {
                hours = "0" + hours;
            }
            if (seconds < 10) {
                seconds = "0" + seconds;
            }
            modulesForm.time.text = hours + ":" + minutes + ":" + seconds;
        }
        onChangeState: {

            modulesForm.lastCheckInMessage.text = classCheck_message;
            modulesForm.lastClasstimeMessage.text = classTime_message;

            switch (stateSetting) {
            case 1:
                modulesForm.isDoneLoading = true;
                modulesForm.isStateOne = true;
                modulesForm.isStateTwo = false;
                modulesForm.isStateThree = false;
                modulesForm.isStateFour = false;
                break;
            case 2:
                modulesForm.isDoneLoading = true;
                modulesForm.isStateTwo = true;
                modulesForm.isStateOne = false;
                modulesForm.isStateThree = false
                modulesForm.isStateFour = false

                break;
            case 3:
                modulesForm.isDoneLoading = true;
                modulesForm.isStateThree = true;
                modulesForm.isStateOne = false;
                modulesForm.isStateTwo = false
                modulesForm.isStateFour = false
                break;
            case 4:
                modulesForm.isDoneLoading = true;
                modulesForm.isStateFour = true;
                modulesForm.isStateOne = false;
                modulesForm.isStateTwo = false
                modulesForm.isStateThree = false
                break;
            case 5:
                modulesForm.isDoneLoading = true;
                modulesForm.isStateFour = false;
                modulesForm.isStateOne = false;
                modulesForm.isStateTwo = false
                modulesForm.isStateThree = false
                break;
            default:
                modulesForm.isDoneLoading = false;
            }
        }
    }



    Component.onCompleted: modules.intialize();


}
