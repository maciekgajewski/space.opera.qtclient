// Copyright (c) 2013 Maciej Gajewski

// every QML project starts by defining oit's own button :)
import QtQuick 2.0

Rectangle {

    // public props
    width: 100
    property alias text: buttontext.text

    // singal
    signal clicked

    //privaste props

    color: "wheat"
    height: 24
    radius: 5

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: parent.color = "lightblue"
        onExited: parent.color = "wheat"
        onPressed: parent.color = "salmon"
        onReleased: parent.color = "wheat"

        onClicked: parent.clicked()
    }

    Text {
        id: buttontext
        anchors.fill: parent
        anchors.margins: 5
        text: "click me"
        horizontalAlignment: Text.AlignHCenter
    }
}
