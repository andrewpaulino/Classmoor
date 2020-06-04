import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import com.classmoor.modules 1.0

Item {

    id: classtimeInterface
    visible: true
    width: 1310
    height: 768

    ClasstimeUI {
        id: classtime
        anchors.fill: parent
        background: Rectangle {
            color:"#F5F5F5"
        }
    }

}
