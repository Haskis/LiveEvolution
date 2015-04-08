import QtQuick 2.3
Rectangle{
    id: root
    property alias text: textItem.text

    signal clicked

    width: 100
    height: 30
    radius: 5

    color: "green"

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        id: textItem
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: "Button"
        font.pixelSize: 9
        font.bold: true

        wrapMode: Text.WordWrap
        lineHeight: 0.75
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        anchors.margins: -5
        onClicked: {
            clickAnimation.start()
            root.clicked()
        }
    }

    SequentialAnimation{
        id: clickAnimation
        running: false
        loops: 1
        NumberAnimation{
            target: root
            property: "scale"
            from: 1
            to: 1.1
            duration: 50
        }
        NumberAnimation{
            target: root
            property: "scale"
            from: 1.1
            to: 1
        }
    }

}
