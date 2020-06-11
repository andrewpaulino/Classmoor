import QtQuick 2.14
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import com.classmoor.setup 1.0
import Qt.labs.calendar 1.0

Page {
    id: page
    width: 1024
    height: 768
    spacing: 2
    focusPolicy: Qt.ClickFocus
    font.bold: false
    font.weight: Font.Medium
    clip: false

    Setup {
        id: setup
    }

    property bool isFilledOut: true
    property bool isFirstTimeSubmitting: false
    property bool isDone: false
    property bool isFound: false

    Connections {
        target: setup
        onFilledOut: {
            isFilledOut = isValid
            isFirstTimeSubmitting = true
        }
        onResults: {
            isDone = done
            isFound = found
            if (isDone && isFound) {
                setup.restartApplication();
            }
        }
    }

    Rectangle {
        id: backgroundColor

        color: "#F5F5F5"
    }

    ColumnLayout {
        id: searchingForClassroom
        x: 885
        y: 464
        width: 553
        height: 296
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        BusyIndicator {
            id: busyIndicator
            visible: false
        }

        Text {
            id: header
            text: qsTr("Text")
            font.pixelSize: 12
        }

        Text {
            id: subText
            text: qsTr("Text")
            font.pixelSize: 12
        }
    }

    ColumnLayout {
        id: mainColumn
        x: 382
        y: 395
        width: 389
        height: 318
        anchors.verticalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 4.9

        Text {
            id: errorMessage
            text: qsTr("Text")
            visible: false
            font.pixelSize: 12
        }

        ColumnLayout {
            id: headerColumn
            width: 100
            height: 100

            Label {
                id: label
                color: "#3d4042"
                text: qsTr("Full Name")
                font.letterSpacing: 2
                font.weight: Font.Medium
                font.bold: false
                font.pointSize: 18
                font.family: "Lato"
            }

            TextField {
                id: nameField
                width: parent.width
                height: 59
                Layout.rowSpan: 5
                padding: 14
                font.family: "Lato"
                Layout.fillWidth: true
                background: Rectangle {
                    width: parent.width
                    height: parent.height
                    color: "#ebebeb"
                    radius: 12
                    border.color: nameField.enabled ? "transparent" : "#2F6BA7"
                    border.width: 1
                }
                placeholderText: qsTr("i.e Luke Skywalker")
                font.pointSize: 15
            }

        }

        ColumnLayout {
            id: classCodeColumn
            width: 100
            height: 100

            Label {
                id: label1
                color: "#3d4042"
                text: qsTr("Class Code")
                font.letterSpacing: 2
                font.weight: Font.Medium
                font.bold: false
                font.family: "Lato"
                font.pointSize: 18
            }

            TextField {
                id: classCodeField
                width: parent.width
                height: 68
                padding: 14
                Layout.fillHeight: false
                Layout.fillWidth: true

                background: Rectangle {
                    width: parent.width
                    height: parent.height
                    color: "#ebebeb"
                    radius: 12
                    border.color: classCodeField.enabled ? "transparent" : "#2F6BA7"
                    border.width: 1
                }
                placeholderText: qsTr("i.e CS8A")
                font.pointSize: 15
            }

        }

        Button {
            id: joinClassroomButton
            text: qsTr("Join Classroom")
            font.pointSize: 20
            font.family: "Lato"
            flat: false
            padding: 14
            Layout.fillHeight: false
            Layout.fillWidth: true

            contentItem: Text {
                text: joinClassroomButton.text
                font.bold: true
                font.family: "Lato"
                font.pointSize: 20
                font.weight: Font.Medium
                opacity: enabled ? 1.0 : 0.3
                color: joinClassroomButton.down ? "#e6f0ff" : "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                color: joinClassroomButton.down ? "#4d94ff" : "#2F6BA7"
                radius: 6
            }

            Connections {
                target: joinClassroomButton
                onClicked: setup.joinClassroom(classCodeField.text,
                                               nameField.text)
            }
        }


    }

    states: [
        State {
            name: "Searching For Classroom"
            when: isFilledOut == true && isFirstTimeSubmitting == true && isDone == false
            PropertyChanges {
                target: searchingForClassroom
                x: 724
                y: 333
                width: 460
                height: 177
                anchors.verticalCenterOffset: -157
                visible: true
            }

            PropertyChanges {
                target: busyIndicator
                width: 60
                height: 60
                Layout.fillHeight: false
                Layout.fillWidth: false
                visible: true
                font.pointSize: 71
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            PropertyChanges {
                target: mainColumn
                visible: false
            }

            PropertyChanges {
                target: header
                color: "#514c4c"
                text: qsTr("Finding Classroom")
                Layout.fillWidth: false
                font.bold: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 31
                font.family: "Lato"
            }

            PropertyChanges {
                target: subText
                color: "#5e5454"
                text: qsTr("Hold tight, we'll automatically load you in!")
                font.family: "Lato"
                font.pixelSize: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
        },
        State {
            name: "Classroom not found"
            when: isDone == true && isFound == false
            PropertyChanges {
                target: errorMessage
                x: 32
                y: 19
                width: 238
                height: 127
                color: "#e92f2f"
                text: qsTr("Classroom not found! Try Again")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                visible: true
                font.bold: true
                font.pixelSize: 21
                font.family: "Lato"
            }

            PropertyChanges {
                target: mainColumn
                x: 382
                y: 395
                width: 389
                height: 362
            }
        },
        State {
            name: "Please fill out both fields"
            when: isFilledOut == false && isFirstTimeSubmitting == false
            PropertyChanges {
                target: errorMessage
                x: 32
                y: 19
                width: 238
                height: 127
                color: "#e92f2f"
                text: qsTr("Please fill out all the fields")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 21
                font.bold: true
                Layout.fillWidth: true
                visible: true
                font.family: "Lato"
            }

            PropertyChanges {
                target: mainColumn
                x: 382
                y: 395
                width: 389
                height: 362
            }
        },
        State {
            name: "found"
            when: isDone == true && isFound == true
            PropertyChanges {
                target: searchingForClassroom
                x: 724
                y: 333
                width: 460
                height: 177
                visible: true
                anchors.verticalCenterOffset: "-157"
            }

            PropertyChanges {
                target: busyIndicator
                width: 60
                height: 60
                visible: true
                Layout.fillHeight: false
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: false
                font.pointSize: 71
            }

            PropertyChanges {
                target: mainColumn
                visible: false
            }

            PropertyChanges {
                target: header
                color: "#514c4c"
                text: qsTr("Classroom Found!")
                font.pixelSize: 31
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.family: "Lato"
                font.bold: true
                Layout.fillWidth: false
            }

            PropertyChanges {
                target: subText
                color: "#5e5454"
                text: qsTr("We are adding you right now, hold tight...")
                font.pixelSize: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.family: "Lato"
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:23;anchors_height:200;anchors_width:200;anchors_x:106;anchors_y:18}
D{i:24;anchors_height:200;anchors_width:200;anchors_x:106;anchors_y:18}D{i:22;anchors_height:200;anchors_width:200;anchors_x:106;anchors_y:18}
}
##^##*/

