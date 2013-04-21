// Copyright (c) 2013 Maciej Gajewski
#include "packetsocket.h"

#include "client.h"

#include <QDebug>
#include <QTcpSocket>
#include <QException>

namespace SpaceOpera {
namespace Client {


class ClientException : public QException
{
public:
    explicit ClientException(const QString& str) : QException(), _what(str) {}

    virtual ~ClientException() noexcept(true) {}
    virtual QException* clone() const  noexcept(true) override { return new ClientException(_what); }
    virtual const char* what() const  noexcept(true) override { return _what.toLocal8Bit(); }
private:
      QString _what;
};

Client::Client(QObject* parent)
    : QObject(parent),
      _tcpSocket(nullptr), _packetSocket(nullptr), _connected(false)
{
    _tcpSocket = new QTcpSocket(this);
    _packetSocket = new PacketSocket(_tcpSocket, this);

    connect(_tcpSocket, &QTcpSocket::connected, this, &Client::networkConnected);
    connect(_tcpSocket, &QTcpSocket::disconnected, this, &Client::networkDisconnected);
    connect(_tcpSocket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &Client::networkError);

}

void Client::connectToHost(const QString& hostName, quint16 port)
{
    qDebug() << "Client::connectToHost " << hostName << port;
    if (!_connected) {
        _tcpSocket->connectToHost(hostName, port);
    }
}

void Client::disconnect()
{
    _tcpSocket->disconnect();
}

bool Client::isConnected() const
{
    return _connected;
}

void Client::networkConnected()
{
    qDebug() << "Client::networkConnected";

    if (!_connected) {
        _connected = true;
        emit connected();
        emit connectionStateChanged();
    }
}

void Client::networkDisconnected()
{
    qDebug() << "Client::networkDisconnected";

    if (_connected) {
        _connected = false;
        emit disconnected();
        emit connectionStateChanged();
    }
}

void Client::networkError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Client::networkError" << socketError;

    if (_connected) {
        _connected = false;
        emit disconnected();
        emit connectionStateChanged();
    }
    emit connectionError(_tcpSocket->errorString());
}


}
}
