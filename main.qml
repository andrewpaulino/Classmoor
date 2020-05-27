import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: window
    visible: true
    width: 1920
    color: "#F5F5F5"
    height: 1080
    title: qsTr("Stack")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        background: Rectangle {
            color: "#F5F5F5"

        }

        Label {
            id: classs
            text: "Classmoor"

            anchors.left: parent.left
            anchors.right: parent.left
            anchors.top: parent.top

            anchors.leftMargin: 40
            anchors.topMargin: 20
            anchors.rightMargin: 23

            color: "#000000"
            font.bold: true
            font.pixelSize: Qt.application.font.pixelSize * 4

        }

    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Page 1")
                width: parent.width
                onClicked: {
                    stackView.push("Page1Form.ui.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Page 2")
                width: parent.width
                onClicked: {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView

        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
    }
}
