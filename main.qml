import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import com.classmoor.modules 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1310
    height: 768
    color: "#F5F5F5"
    title: qsTr("Classmoor")
    maximumHeight : 768
    maximumWidth : 1310


    header: Rectangle {
        color: "#F5F5F5"
        y: 917
        RowLayout {
            id: rowLayout
            width: 1920
            height: 163
            anchors.left: parent.left
            anchors.leftMargin: 40
            spacing: 0


            RowLayout {
                id: rowLayout1
                width: 400
                height: 100
                Layout.leftMargin: 0
                spacing: 0

                Text {
                    id: element1
                    width: 169
                    height: 85
                    text: qsTr("Class")
                    font.bold: true
                    font.family: "Lato"
                    font.pixelSize: 50
                }

                Text {
                    id: element3
                    width: 169
                    height: 85
                    color: "#2f6ba7"
                    text: qsTr("moor")
                    font.bold: true
                    font.family: "Lato"
                    font.pixelSize: 50
                }


            }
        }

    }

    StackView {
        id: stackView
        width: 1310
        height: 768
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        initialItem: Item {
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
                    //                    modules.joinClasstime();
                    //            console.log("here")
                    stackView.push("ClasstimeInterface.qml");
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
                    default:
                        modulesForm.isDoneLoading = false;
                    }
                    console.log(modulesForm.isDoneLoading)
                }
            }



            Component.onCompleted: modules.intialize();


        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33000001311302185}D{i:6;anchors_height:768;anchors_width:1310}
}
##^##*/
