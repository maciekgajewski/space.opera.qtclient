import QtQuick 2.0
import spaceopera.client 1.0

Rectangle {
    width: 200
    height: 200
    color: "lightsteelblue"

    // client
    Client {
        id: client
        onConnectionError: errortext.errorMsg = errorString
    }

    // conection status text
    Text {
        id: connectionstatus
        anchors.top: parent.top
        text: client.connected ? "connected" : "disconnected"
    }

    // error status
    Text {
        id: errortext
        anchors.top: connectionstatus.bottom

        property string errorMsg

        text: client.connected ? "---" : errorMsg
    }

    // connect button
    Rectangle {
        anchors.bottom: parent.bottom
        color: "wheat"
        height: 20
        width: 100

        MouseArea {
            anchors.fill: parent
            Text {
                id: buttontext
                anchors.fill: parent
                text: "click me to connect"
            }

            onClicked: { client.connectToHost("localhost", 7898); errortext.errorMsg = "connecting..." }

        }
    }


}
