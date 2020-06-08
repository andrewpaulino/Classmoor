import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import com.classmoor.classmoor 1.0
import com.classmoor.modules 1.0
import QtGraphicalEffects 1.0
import QtWebView 1.1

Page {
    id: page
    width: 1310
    height: 768
    property alias leaveButton: leaveButton
    property alias leaveButtonMouseArea: leaveButtonMouseArea
    property alias participants: participants
    property alias lessonHeader: lessonHeader
    property alias timeText: timeText
    //FIX LOADING
//    property bool isDoneLoading: true
    contentWidth: 4
    title: qsTr("Classtime")
    background: Rectangle {
        color: "#F5F5F5"
    }


    SequentialAnimation {
        id: animation
        running: true
        loops: Animation.Infinite

        ScaleAnimator {
            id: aniShrink
            target: connected
            from: 1
            to: 0.9
            duration: 1000
            running: true
        }
        ScaleAnimator {
            id: aniGrow
            target: connected
            from: 0.9
            to: 1
            duration: 1000
            running: true
        }
    }

    ScrollView {
        id: scrollView1
        anchors.fill: parent
        clip: true
        contentHeight: parent.height + 300

        RowLayout {
            id: rowLayout0
            x: 30
            y: 0
            height: 163
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 30
            spacing: 0
            RowLayout {
                id: rowLayout10
                width: 400
                height: 100
                Layout.leftMargin: 0
                spacing: 10


                RowLayout {
                    id: subLayout0
                    spacing: 0
                    Text {
                        id: element10
                        width: 169
                        height: 85
                        text: qsTr("Class")
                        font.bold: true
                        font.family: "Lato"
                        font.pixelSize: 40
                    }
                    Text {
                        id: element30
                        width: 169
                        height: 85
                        color: "#2f6ba7"
                        text: qsTr("Time")
                        font.bold: true
                        font.family: "Lato"
                        font.pixelSize: 40
                    }
                }




                Rectangle {
                    id: connected
                    width: 93
                    height: 25
                    color: "#71f495"
                    radius: 6
                    Text {
                        id: element2
                        color: "#015819"
                        text: qsTr("Connected")
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "Lato"
                        font.letterSpacing: 1.2
                        font.weight: Font.Medium
                        font.bold: false
                        font.pixelSize: 11
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    border.width: 0
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                }
            }

            Button {
                id: leaveButton
                width: 400
                height: 30
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                text: qsTr("Join Classroom")
                bottomPadding: 10
                topPadding: 10
                Layout.margins: 0

                contentItem: Text {
                    id: element10322
                    color: leaveButton.down ? "#e6f0ff" : "white"
                    text: "Leave"
                    opacity: enabled ? 1.0 : 0.3
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    font.family: "Lato"
                    verticalAlignment: Text.AlignVCenter
                    font.weight: Font.Medium
                    font.pointSize: 11
                }
                padding: 30
                Layout.fillHeight: false
                background: Rectangle {
                    id: backgroundRect23122
                    color:  "#f65466"
                    radius: 6
                }
                font.family: "Lato"
                Layout.fillWidth: false
                flat: false
                font.pointSize: 20

                MouseArea {
                    id: leaveButtonMouseArea
                    height: 40
                    anchors.bottomMargin: 0
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                }


                Connections {
                    target: leaveButtonMouseArea
                    onEntered: {
                        backgroundRect23122.color = "#e2717e"
                    }
                    onExited: {
                        backgroundRect23122.color = "#f65466"
                    }
                }
            }




        }


        RowLayout {
            id: rowLayout1
            spacing: 0
            anchors.bottom: columnLayout.top
            anchors.bottomMargin: 0
            anchors.top: rowLayout0.bottom
            anchors.topMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 40

            ColumnLayout {
                id: questionColumn
                width: 698
                height: 179
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillWidth: false
                spacing: 17.3
                Layout.fillHeight: true
                visible: true

                RowLayout {
                    id: subLayout1
                    Text {
                        id: element4
                        width: 169
                        height: 85
                        text: qsTr("Class")
                        font.family: "Lato"
                        font.bold: true
                        font.pixelSize: 30
                    }

                    Text {
                        id: element5
                        width: 169
                        height: 85
                        color: "#018d8d"
                        text: qsTr("Ask")
                        font.family: "Lato"
                        font.bold: true
                        font.pixelSize: 30
                    }
                    spacing: 0
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                }

                ColumnLayout {
                    id: askQuestionInfoColumn
                    width: 100
                    height: 100

                    Text {
                        id: questionBody
                        text: qsTr("You can ask your question anonymously or not, and it will give them a push notification instantaneously")
                        Layout.fillWidth: false
                        wrapMode: Text.WordWrap
                        font.pixelSize: 12
                    }



                }

                RowLayout {
                    id: questionActionRow
                    width: 698
                    height: 100
                    spacing: 30
                    Layout.fillWidth: true

                    ColumnLayout {
                        id: questionAnonColumn
                        width: 100
                        height: 100

                        Label {
                            id: anonymousSwitch
                            color: "#47360b"
                            text: qsTr("ANONYMOUS")
                            font.bold: false
                            font.weight: Font.Medium
                            font.pointSize: 9
                            font.family: "Lato"
                        }

                        Switch {
                            id: anonSwitch
                            text: qsTr("")
                        }
                    }

                    ColumnLayout {
                        id: questionFieldColumn
                        width: 171
                        height: 100
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.fillWidth: true

                        Label {
                            id: anonymousSwitch1
                            color: "#47360b"
                            text: qsTr("YOUR QUESTION")
                            font.pointSize: 9
                            font.weight: Font.Normal
                            font.family: "Lato"
                            font.letterSpacing: 1.2
                        }

                        RowLayout {
                            id: textFieldRow
                            width: 100
                            height: 100
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            TextField {
                                id: textField
                                height: 50
                                font.pointSize: 11
                                Layout.fillHeight: false
                                rightPadding: 16
                                Layout.fillWidth: true
                                placeholderText: qsTr("Can you explain that?")
                            }
                            Button {
                                id: askButton
                                width: 400
                                height: 30
                                text: qsTr("Join Classroom")
                                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                                contentItem: Text {
                                    id: element103
                                    color: askButton.down ? "#e6f0ff" : "white"
                                    text: "Ask"
                                    opacity: enabled ? 1.0 : 0.3
                                    font.bold: true
                                    horizontalAlignment: Text.AlignHCenter
                                    elide: Text.ElideRight
                                    font.family: "Lato"
                                    verticalAlignment: Text.AlignVCenter
                                    font.weight: Font.Medium
                                    font.pointSize: 11
                                }
                                padding: 11
                                Layout.fillHeight: false
                                background: Rectangle {
                                    id: backgroundRect2
                                    color:  "#7131bf"
                                    radius: 6
                                }
                                font.family: "Lato"
                                Layout.fillWidth: true
                                flat: false
                                font.pointSize: 20

                                MouseArea {
                                    id: askButtonMouseArea
                                    height: 40
                                    anchors.bottomMargin: 0
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }


                                Connections {
                                    target: askButtonMouseArea
                                    onEntered: {
                                        backgroundRect2.color = "#7b38cf"
                                    }
                                    onExited: {
                                        backgroundRect2.color = "#7131bf"
                                    }
                                }
                            }
                        }

                    }
                }









            }

            ColumnLayout {
                id: columnLayout1
                width: 100
                height: 100
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop


                RowLayout {
                    id: subLayout3
                    Text {
                        id: element9
                        width: 169
                        height: 85
                        text: qsTr("Class")
                        font.family: "Lato"
                        font.bold: true
                        font.pixelSize: 30
                    }

                    Text {
                        id: element11
                        width: 169
                        height: 85
                        color: "#e3061d"
                        text: qsTr("Test")
                        font.family: "Lato"
                        font.bold: true
                        font.pixelSize: 30
                    }
                    spacing: 0
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                }

                Text {
                    id: element6
                    width: 169
                    height: 85
                    color: "#88838d"
                    text: qsTr("No assigned test or avaliable ")
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    font.family: "Lato"
                    font.bold: true
                    font.pixelSize: 20
                }
            }


        }






        ColumnLayout {
            id: columnLayout
            x: 40
            y: 468
            height: 398
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 40
            RowLayout {
                id: subLayout
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                spacing: 0
                Text {
                    id: element1
                    width: 169
                    height: 85
                    text: qsTr("Class")
                    font.bold: true
                    font.family: "Lato"
                    font.pixelSize: 30
                }

                Text {
                    id: element3
                    width: 169
                    height: 85
                    color: "#7131bf"
                    text: qsTr("Viewer")
                    font.bold: true
                    font.family: "Lato"
                    font.pixelSize: 30
                }
            }

            Item {
                id: element
                width: 700
                height: 200
                Layout.fillHeight: true
                Layout.fillWidth: false

                WebView {
                    id: webView
                    x: 0
                    y: 0
                    clip: true
                    anchors.bottomMargin: -229
                    anchors.fill: parent
                    url: "https://pmy914l2kq.csb.app/"
                }


            }
        }

    }

    ColumnLayout {
        id: columnLayout4
        x: 512
        y: 367
        anchors.horizontalCenter: parent.horizontalCenter
        width: 100
        height: 100

        BusyIndicator {
            id: busyIndicator
            visible: false
        }

        Text {
            id: element8
            text: qsTr("Text")
            visible: false
            font.pixelSize: 12
        }


    }





    Rectangle {
        id: rectangle
        x: 82
        y: 718
        width: 763
        height: 50
        color: "#2c2f33"
        radius: 6
        border.width: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        RowLayout {
            id: footer
            anchors.rightMargin: 10
            anchors.leftMargin: 20
            anchors.fill: parent
            spacing: 25

            ColumnLayout {
                id: columnLayout3
                width: 100
                height: 100

                Text {
                    id: element12
                    width: 169
                    height: 85
                    color: "#99aab5"
                    text: qsTr("LESSON")
                    font.letterSpacing: 1.2
                    font.weight: Font.Normal
                    font.family: "Lato"
                    font.bold: false
                    font.pixelSize: 12
                }

                Text {
                    id: lessonHeader
                    width: 169
                    height: 85
                    color: "#ffffff"
                    text: qsTr("Reading Activities 1.8")
                    font.family: "Lato"
                    font.letterSpacing: 0.5
                    font.weight: Font.Bold
                    font.bold: true
                    font.pixelSize: 12
                }
            }

            ColumnLayout {
                id: columnLayout5
                width: 100
                height: 100

                Text {
                    id: element13
                    width: 169
                    height: 85
                    color: "#99aab5"
                    text: qsTr("TIME ELAPSED")
                    font.family: "Lato"
                    font.letterSpacing: 1.2
                    font.weight: Font.Normal
                    font.bold: false
                    font.pixelSize: 12
                }

                Text {
                    id: timeText
                    width: 169
                    height: 85
                    color: "#ffffff"
                    text: qsTr("3 Hours and 30 Minutes and 20 seconds")
                    font.family: "Lato"
                    font.letterSpacing: 0.5
                    font.weight: Font.Bold
                    font.bold: true
                    font.pixelSize: 12
                }
            }

            ColumnLayout {
                id: columnLayout6
                width: 100
                height: 100

                Text {
                    id: element14
                    width: 169
                    height: 85
                    color: "#99aab5"
                    text: qsTr("PARTICIPANTS")
                    font.family: "Lato"
                    font.letterSpacing: 1.2
                    font.weight: Font.Normal
                    font.bold: false
                    font.pixelSize: 12
                }

                Text {
                    id: participants
                    width: 169
                    height: 85
                    color: "#ffffff"
                    text: qsTr("30 Participants")
                    font.family: "Lato"
                    font.letterSpacing: 0.5
                    font.weight: Font.Bold
                    font.bold: true
                    font.pixelSize: 12
                }
            }
        }
    }






    states: [
        State {
            name: "LoadingApp"
            when: !isDoneLoading

            PropertyChanges {
                target: busyIndicator
                x: 583
                y: 249
                width: 145
                height: 118
                visible: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            PropertyChanges {
                target: element8
                x: 462
                y: 466
                color: "#4f4a4a"
                text: qsTr("Loading classtime")
                visible: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true
                font.family: "Lato"
                font.pixelSize: 30
            }

            PropertyChanges {
                target: columnLayout4
                y: 312
                width: 370
                height: 191
                anchors.horizontalCenterOffset: 0
            }
        },
        State {
            name: "State1"
        }
    ]
}

/*##^##
Designer {
    D{i:0;customId:"";formeditorZoom:0.6600000262260437}D{i:9;anchors_height:200;anchors_width:200;invisible:true}
D{i:10;invisible:true}D{i:8;anchors_height:200;anchors_width:200;invisible:true}D{i:11;invisible:true}
D{i:17;anchors_height:200;anchors_width:100;anchors_x:36;anchors_y:242}D{i:13;invisible:true}
D{i:6;anchors_height:163;anchors_width:1920;anchors_x:0;anchors_y:0}D{i:22;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:20;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}D{i:24;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:23;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}D{i:27;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:28;anchors_height:200;anchors_width:200;anchors_x:36;anchors_y:118}D{i:26;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:30;anchors_height:200;anchors_width:100;anchors_x:83;anchors_y:367}D{i:32;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:37;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}D{i:31;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:29;anchors_height:200;anchors_width:100;anchors_x:83;anchors_y:242}D{i:25;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:19;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}D{i:40;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:41;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}D{i:39;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:42;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}D{i:38;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:18;anchors_height:200;anchors_width:100;anchors_x:36;anchors_y:242}D{i:45;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:46;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}D{i:44;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}
D{i:48;anchors_height:200;anchors_width:200;anchors_x:36;anchors_y:118}D{i:47;anchors_x:36}
D{i:43;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118}D{i:5;anchors_height:163;anchors_width:1920;anchors_x:0;anchors_y:0}
D{i:50;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118;invisible:true}
D{i:51;invisible:true}D{i:49;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118;invisible:true}
D{i:55;anchors_height:163;anchors_width:1920;anchors_x:0;anchors_y:0}D{i:56;anchors_height:163;anchors_width:1920;anchors_x:0;anchors_y:0}
D{i:54;anchors_height:100;anchors_width:100;anchors_x:312;anchors_y:214}D{i:58;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118;invisible:true}
D{i:59;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118;invisible:true}
D{i:57;anchors_height:163;anchors_width:1920;anchors_x:0;anchors_y:0}D{i:61;invisible:true}
D{i:62;invisible:true}D{i:60;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:118;invisible:true}
D{i:53;anchors_height:100;anchors_width:100;anchors_x:312;anchors_y:214}D{i:52;anchors_height:100;anchors_width:100;anchors_x:312;anchors_y:214;invisible:true}
D{i:63;invisible:true}
}
##^##*/

