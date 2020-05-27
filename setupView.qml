import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: window
    visible: true
    width: 1920
    color: "#F5F5F5"
    height: 1080
    title: qsTr("Setup")

    SetupForm {
        id: setupForm
        anchors: parent.fill
    }

}
