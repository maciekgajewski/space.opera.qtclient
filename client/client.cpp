// Copyright (c) 2013 Maciej Gajewski
#include "packetsocket.h"

#include "client.h"

#include <QDebug>
#include <QTcpSocket>

namespace SpaceOpera {
namespace Client {


Client::Client(QObject* parent)
    : QObject(parent),
      _tcpSocket(nullptr), _packetSocket(nullptr)
{
    _tcpSocket = new QTcpSocket(this);
    _packetSocket = new PacketSocket(_tcpSocket, this);

    connect(_tcpSocket, &QTcpSocket::connected, this, &Client::networkConnected);
    connect(_tcpSocket, (void (QTcpSocket::*)(QAbstractSocket::SocketError))&QTcpSocket::error, this, &Client::networkError);

}

void Client::connectToHost(const QString& hostName, quint16 port)
{
        _tcpSocket->connectToHost(hostName, port);
}

void Client::disconnect()
{
    _tcpSocket->disconnect();
}

bool Client::isConnected() const
{
    return _tcpSocket->state() == QAbstractSocket::ConnectedState;
}

void Client::networkConnected()
{
    emit connectionStateChanged();
}

void Client::networkError(QAbstractSocket::SocketError socketError)
{
    emit connectionStateChanged();
}


}
}
