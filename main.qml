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

    property bool isClasstime: false;


    StackView {
        id: stackView
        width: 1310
        height: 768
        anchors.horizontalCenter: parent.horizontalCenter
        //        anchors.verticalCenter: parent.verticalCenter
        initialItem: "Modules.qml"
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33000001311302185}D{i:6;anchors_height:768;anchors_width:1310}
}
##^##*/
