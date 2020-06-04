import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import com.classmoor.classmoor 1.0
import com.classmoor.modules 1.0
import QtGraphicalEffects 1.0

Page {
    id: page
    width: 1310
    height: 768
    property alias joinClasstimeButton: joinClasstimeButton
    property alias checkInMouseArea: checkInMouseArea
    property alias checkInButton: checkInButton
    property alias time: time
    property alias lastClasstimeMessage: lastClasstimeMessage
    property alias lastCheckInMessage: lastCheckInMessage
    state: "LoadingApp"
    property alias backgroundRect: backgroundRect
    contentWidth: 4
    title: qsTr("Classtime")
    background: Rectangle {
        color: "#F5F5F5"
    }
    property bool isDoneLoading: false
    property bool isStateOne: false
    property bool isStateTwo: false
    property bool isStateThree: false
    property bool isStateFour: false



    SequentialAnimation {
        id: animation
        running: false
        loops: Animation.Infinite

        ScaleAnimator {
            id: aniShrink
            target: rectangle
            from: 1
            to: 0.9
            duration: 1000
            running: true
        }
        ScaleAnimator {
            id: aniGrow
            target: rectangle
            from: 0.9
            to: 1
            duration: 1000
            running: true
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

    RowLayout {
        id: rowLayout
        x: 448
        y: 196
        width: 991
        height: 404
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: classTime
            width: 448
            height: 324
            color: "#ffffff"
            radius: 12
            border.width: 0
            visible: false
            Layout.fillWidth: false
        }

        DropShadow {
            id: dropShadow1
            width: 448
            height: 324
            horizontalOffset: 0
            verticalOffset: 3
            radius: 13.0
            visible: true
            samples: 17
            color: "#c4bbbb"
            source: classTime

            ColumnLayout {
                id: columnLayout
                x: 15
                y: 8
                width: 417
                height: 308
                anchors.horizontalCenter: parent.horizontalCenter

                RowLayout {
                    id: rowLayout1
                    width: 417
                    height: 100
                    Layout.minimumWidth: 417
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    spacing: 110
                    Layout.margins: 0
                    Layout.rightMargin: 0
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                    ColumnLayout {
                        id: columnLayout1
                        width: 100
                        height: 100

                        RowLayout {
                            id: rowLayout2
                            width: 100
                            height: 100
                            spacing: 0

                            Text {
                                id: element4
                                color: "#303030"
                                text: qsTr("Class")
                                Layout.topMargin: 15
                                Layout.leftMargin: 0
                                font.letterSpacing: 1.2
                                Layout.margins: 0
                                font.family: "Lato"
                                font.weight: Font.DemiBold
                                font.pixelSize: 30
                            }

                            Text {
                                id: element
                                color: "#2f6ba7"
                                text: qsTr("Time")
                                Layout.leftMargin: 0
                                Layout.topMargin: 15
                                Layout.margins: 0
                                font.letterSpacing: 1.2
                                font.weight: Font.DemiBold
                                font.family: "Lato"
                                font.pixelSize: 30
                            }
                        }

                        RowLayout {
                            id: rowLayout3
                            width: 100
                            height: 100

                            Image {
                                id: image
                                Layout.leftMargin: 0
                                Layout.topMargin: 0
                                Layout.margins: 0
                                sourceSize.height: 13
                                sourceSize.width: 13
                                fillMode: Image.PreserveAspectFit
                                source: "time.svg"
                            }

                            Text {
                                id: lastClasstimeMessage
                                color: "#534f4f"
                                text: qsTr("Last Class was 1 day ago")
                                Layout.leftMargin: 0
                                Layout.topMargin: 0
                                Layout.margins: 0
                                font.weight: Font.Thin
                                font.family: "Lato"
                                font.pixelSize: 12
                            }
                        }
                    }

                    Rectangle {
                        id: rectangle
                        width: 93
                        height: 25
                        color: "#c83b4c"
                        radius: 6
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        border.width: 0

                        Text {
                            id: element2
                            color: "#580101"
                            text: qsTr("Offline")
                            font.weight: Font.Medium
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.letterSpacing: 1.2
                            font.bold: false
                            font.family: "Lato"
                            font.pixelSize: 11
                        }



                    }

                }

                Rectangle {
                    id: rectangle1
                    width: 200
                    height: 1
                    color: "#2f6ba7"
                    Layout.fillWidth: true
                }

                RowLayout {
                    id: rowLayout5
                    width: 447

                    height: 100
                    Layout.fillWidth: true

                    Text {
                        id: element3
                        color: "#5e5555"
                        Layout.preferredWidth: 204
                        text: qsTr("Classtime, provides a realtime program to help allivate issues that make come up with doing online zoom sessions or teams sessiosn")
                        Layout.leftMargin: 0
                        font.family: "Lato"
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        wrapMode: Text.WordWrap
                        Layout.fillHeight: false
                        font.pixelSize: 13
                    }

                    Image {
                        id: image1
                        x: 0
                        y: 0
                        width: 190
                        sourceSize.height: 150
                        sourceSize.width: 204
                        fillMode: Image.PreserveAspectFit
                        source: "classtimereal.svg"
                    }
                }

                Button {
                    id: joinClasstimeButton
                    text: qsTr("Join Classroom")
                    enabled: false
                    font.pointSize: 20
                    font.family: "Lato"
                    flat: false
                    padding: 14
                    width: 400
                    height: 50
                    Layout.fillHeight: false
                    Layout.fillWidth: true

                    contentItem: Text {
                        font.bold: true
                        font.family: "Lato"
                        font.pointSize: 11
                        font.weight: Font.Medium
                        opacity: enabled ? 1.0 : 0.3
                        color: joinClasstimeButton.down ? "#e6f0ff" : "white"
                        text: "Join Classtime"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        color: joinClasstimeButton.down ? "#4d94ff" : "#2F6BA7"
                        radius: 6
                    }
                }
            }
        }
        Rectangle {
            id: classCheck
            width: 448
            height: 324
            color: "#ffffff"
            radius: 12
            visible: false
            border.width: 0
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillWidth: false
        }

        DropShadow {
            id: dropShadow
            width: 448
            height: 324
            horizontalOffset: 0
            verticalOffset: 3
            radius: 13.0
            visible: true
            samples: 17
            color: "#c4bbbb"
            source: classCheck

            ColumnLayout {
                id: columnLayout2
                x: 558
                y: 7
                width: 417
                height: 308
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                RowLayout {
                    id: rowLayout7
                    width: 417
                    height: 100
                    spacing: 110
                    Layout.fillHeight: false
                    Layout.margins: 0
                    Layout.fillWidth: true
                    Layout.rightMargin: 0
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    Layout.minimumWidth: 417

                    ColumnLayout {
                        id: columnLayout3
                        width: 100
                        height: 100
                        RowLayout {
                            id: rowLayout4
                            width: 100
                            height: 100
                            spacing: 0
                            Text {
                                id: element5
                                color: "#303030"
                                text: qsTr("Class")
                                Layout.leftMargin: 0
                                Layout.topMargin: 15
                                font.letterSpacing: 1.2
                                Layout.margins: 0
                                font.family: "Lato"
                                font.pixelSize: 30
                                font.weight: Font.DemiBold
                            }

                            Text {
                                id: element6
                                color: "#7131bf"
                                text: qsTr("Check")
                                Layout.topMargin: 15
                                Layout.leftMargin: 0
                                font.letterSpacing: 1.2
                                Layout.margins: 0
                                font.family: "Lato"
                                font.weight: Font.DemiBold
                                font.pixelSize: 30
                            }
                        }

                        RowLayout {
                            id: rowLayout6
                            width: 100
                            height: 100
                            Image {
                                id: image2
                                Layout.topMargin: 0
                                Layout.leftMargin: 0
                                Layout.margins: 0
                                fillMode: Image.PreserveAspectFit
                                sourceSize.width: 13
                                source: "time.svg"
                                sourceSize.height: 13
                            }

                            Text {
                                id: lastCheckInMessage
                                color: "#534f4f"
                                text: qsTr("Last check in was 1 day ago")
                                Layout.topMargin: 0
                                Layout.leftMargin: 0
                                Layout.margins: 0
                                font.family: "Lato"
                                font.weight: Font.Thin
                                font.pixelSize: 12
                            }
                        }
                    }

                    ColumnLayout {
                        id: columnLayout5
                        width: 100
                        height: 100

                        Label {
                            id: label
                            text: qsTr("Label")
                        }


                        ColumnLayout {
                            id: columnLayout6
                            width: 100
                            height: 100

                            RowLayout {
                                id: rowLayout9
                                width: 100
                                height: 100

                                Text {
                                    id: time
                                    color: "#580101"
                                    text: qsTr("Offline")
                                    font.weight: Font.Medium
//                                    anchors.horizontalCenter: parent.horizontalCenter
                                    font.family: "Lato"
                                    font.letterSpacing: 1.2
                                    font.bold: false
                                    font.pixelSize: 11
//                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }


                        }


                    }

                }

                Rectangle {
                    id: rectangle3
                    width: 200
                    height: 1
                    color: "#7131bf"
                    border.width: 1
                    Layout.fillWidth: true
                }

                RowLayout {
                    id: rowLayout8
                    width: 447
                    height: 100
                    Layout.fillWidth: true
                    Text {
                        id: element9
                        color: "#5e5555"
                        text: qsTr("Classtime, provides a realtime program to help allivate issues that make come up with doing online zoom sessions or teams sessiosn")
                        Layout.leftMargin: 0
                        wrapMode: Text.WordWrap
                        Layout.fillHeight: false
                        font.family: "Lato"
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Layout.preferredWidth: 204
                        font.pixelSize: 13
                    }

                    Image {
                        id: image3
                        x: 0
                        y: 0
                        width: 190
                        fillMode: Image.PreserveAspectFit
                        sourceSize.width: 204
                        source: "cal.svg"
                        sourceSize.height: 150
                    }
                }


                Button {
                    id: checkInButton
                    width: 400
                    height: 50
                    text: qsTr("Join Classroom")
                    contentItem: Text {
                        id: element10
                        color: checkInButton.down ? "#e6f0ff" : "white"
                        text: "Check In"
                        opacity: enabled ? 1.0 : 0.3
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideRight
                        font.family: "Lato"
                        verticalAlignment: Text.AlignVCenter
                        font.weight: Font.Medium
                        font.pointSize: 11
                    }
                    padding: 14
                    Layout.fillHeight: false
                    background: Rectangle {
                        id: backgroundRect
                        color:  "#7131bf"
                        radius: 6
                    }
                    font.family: "Lato"
                    Layout.fillWidth: true
                    flat: false
                    font.pointSize: 20

                    MouseArea {
                        id: checkInMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                    }


                    Connections {
                        target: checkInMouseArea
                        onEntered: {
                            backgroundRect.color = "#7b38cf"
                        }
                        onExited: {
                            backgroundRect.color = "#7131bf"
                        }
                    }
                }
                Text {
                    id: element11
                    text: qsTr("Text")
                    visible: false
                    font.pixelSize: 12
                }
            }
        }
    }



    states: [
        State {
            name: "LoadingApp"
            when: isDoneLoading === false
            PropertyChanges {
                target: dropShadow
                visible: false
            }

            PropertyChanges {
                target: dropShadow1
                visible: false
            }

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
                text: qsTr("Text")
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
        }
    ]
}

/*##^##
Designer {
    D{i:0;customId:"";formeditorZoom:0.75}D{i:6;invisible:true}D{i:7;invisible:true}D{i:5;invisible:true}
D{i:27;invisible:true}D{i:28;anchors_height:300;anchors_width:350;anchors_x:355;anchors_y:0;invisible:true}
D{i:26;anchors_height:300;anchors_width:350;anchors_x:355;anchors_y:0;invisible:true}
D{i:29;anchors_height:300;anchors_width:350;anchors_x:355;anchors_y:0;invisible:true}
D{i:48;anchors_height:100;anchors_width:100}D{i:50;anchors_height:100;anchors_width:100}
D{i:52;anchors_height:100;anchors_width:100}D{i:49;anchors_height:100;anchors_width:100}
D{i:31;anchors_height:300;anchors_width:350;anchors_x:355;anchors_y:0;invisible:true}
D{i:30;invisible:true}D{i:8;anchors_height:298;anchors_width:407;anchors_x:8;anchors_y:8}
}
##^##*/

