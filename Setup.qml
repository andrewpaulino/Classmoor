import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    color: "#F5F5F5"
    height: 768
    title: qsTr("Classmoor Setup")
    maximumHeight : 768
    maximumWidth : 1024

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
        initialItem: "SetupForm.ui.qml"
        anchors.fill: parent
        background: Rectangle {
            color:"#F5F5F5"
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33000001311302185}
}
##^##*/
