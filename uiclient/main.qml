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
    }

    Column {
        width: 150
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        // conection status text
        Text {
            id: connectionstatus
            //anchors.top: parent.top
            text: client.connected ? "connected" : "disconnected"
        }

        // error status
        Text {
            id: errortext
            //anchors.top: connectionstatus.bottom

            property string errorMsg

            text: client.connected ? "---" : errorMsg
        }

        // connect button

        TextButton {
            //anchors.bottom: parent.bottom
            width: 100
            text: "Connect"
            onClicked: { client.connectToHost("localhost", 7898); errortext.errorMsg = "connecting..." }
        }
    }


}
