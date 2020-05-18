import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Page {
    id: page
    width: 1920
    height: 1080
    contentWidth: 4
    title: qsTr("Classmoor")
    background: Rectangle {
        color:"#F5F5F5"
    }

    Rectangle {
        id: rectangle1
        x: 303
        y: 449
        width: 150
        height: 70
        color: "#1f777c"
        radius: 6
        border.width: 0

        DropShadow {
            anchors.fill: rectangle1
            horizontalOffset: 0
            verticalOffset: 8
            radius: 12.0
            samples: 25
            color: "#80000000"
            source: rectangle1
        }
    }

    Rectangle {
        id: rectangle
        x: 95
        y: 449
        width: 198
        height: 71
        color: "#f5f5f5"
        radius: 6
        border.color: "#736e6e"
        border.width: 1

        TextInput {
            id: textInput
            maximumLength: 4
            x: 33
            y: 13
            width: 143
            height: 48
            color: "#393131"
            selectByMouse: true
            font.family: "Lato"
            horizontalAlignment: Text.AlignLeft
            wrapMode: Text.WrapAnywhere
            font.bold: true
            echoMode: TextInput.Normal
            cursorVisible: false
            font.pixelSize: 43
        }

        //        InnerShadow {
        //            anchors.fill: rectangle
        //            radius: 8.0
        //            samples: 16
        //            horizontalOffset: -3
        //            verticalOffset: 3
        //            color: "#b0000000"
        //            source: rectangle
        //        }
    }

    Image {
        id: image
        x: 1097
        y: 169
        width: 725
        height: 746
        source: "undraw_teaching_f1cm.svg"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: element
        x: 99
        y: 352
        color: "#1f777c"
        text: qsTr("Join with your four digit code")
        font.letterSpacing: 1.7
        font.bold: true
        font.family: "Lato"
        font.pixelSize: 41
    }

    Text {
        id: element1
        x: 96
        y: 402
        width: 378
        height: 33
        color: "#676060"
        text: qsTr("Provided by you're teacher")
        font.weight: Font.Light
        font.pixelSize: 27
    }

    Button {
        id: control
        x: 303
        y: 449
        width: 150
        height: 70
        text: qsTr("Join")
        padding: 0
        font.letterSpacing: 1.4
        font.family: "Lato"
        font.pointSize: 20
        font.capitalization: Font.AllUppercase

        contentItem: Text {
            color: "white"
            font: control.font
            opacity: enabled ? 1.0 : 0.3
            text: "Join"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            color: "#1f777c"
            opacity: enabled ? 1 : 0.3
            border.color: control.down ? "#17a81a" : "#1f777c"
            border.width: 1
            radius: 6
        }
    }

    Text {
        id: element2
        x: 96
        y: 529
        color: "#6e6767"
        text: qsTr("Dont have a code? click here")
        font.underline: true
        font.weight: Font.Thin
        font.capitalization: Font.AllUppercase
        font.family: "Lato"
        font.pixelSize: 12
    }

    FocusScope {
        id: focusScope
        x: 112
        y: 463
        width: 161
        height: 43

        MouseArea {
            id: mouseArea
            x: 70
            y: 0
            width: 100
            height: 43
        }
    }

}

/*##^##
Designer {
    D{i:0;customId:"";formeditorZoom:0.75}D{i:3;invisible:true}
}
##^##*/

