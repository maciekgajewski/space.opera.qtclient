// Copyright (c) 2013 Maciej Gajewski
import QtQuick 2.0
import spaceopera.client 1.0

Rectangle {
    width: 800
    height: 600
    color: "lightsteelblue"

    // client
    Client {
        id: client
        onConnectionError: errortext.errorMsg = errorString
        onConnected: handshakeSession.authenticate('user', 'password')
    }

    HandshakeSession {
        id: handshakeSession
        client: client

        onSessionError: errortext.errorMsg = errorString
        onAuthenticated: { errortext.errorMsg = 'authetticated'; requestUniverses() }
        onUniversesReceived: { connectToUniverse("default"); console.log('universes received'); }
        onConnectedToUniverse:errortext.errorMsg = 'connected to universe'
    }

    UniverseSession {
        id: universeSession
        client: client

        onSessionError: errortext.errorMsg = errorString
        onUniverseStateChanged: universeState.text = "time scale: " + currentTimeScale + ", current time: " + currentTime
    }

    Column {
        width: 150
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        // conection status text
        Text {
            id: connectionstatus
            text: client.connected ? "connected" : "disconnected"
        }

        // error status
        Text {
            id: errortext
            property string errorMsg

            text: client.connected ? "---" : errorMsg
        }

        // connect button

        TextButton {
            width: 100
            text: "Connect"
            onClicked: { client.connectToHost("localhost", 7898); errortext.errorMsg = "connecting..." }
        }

        // universe status
        Text {
            id: universeState
            text: "---"
        }

        // universe control

        TextButton {
            text: "time: stop"
            onClicked : universeSession.changeTimeScale(0)
        }
        TextButton {
            text: "time: x1"
            onClicked : universeSession.changeTimeScale(1)
        }
        TextButton {
            text: "time: x10"
            onClicked : universeSession.changeTimeScale(10)
        }
    }


}
