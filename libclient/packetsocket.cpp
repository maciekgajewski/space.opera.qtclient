// Copyright (c) 2013 Maciej Gajewski

#include "packetsocket.h"

namespace SpaceOpera {
namespace Client {

static const int HEADER_SIZE = 15;

PacketSocket::PacketSocket(QAbstractSocket *socket, QObject* parent)
    : QObject(parent), _socket(socket), _lastReqId(0), _state(stateReadingHeader)
{
    Q_ASSERT(socket);

    connect(_socket, &QAbstractSocket::readyRead, [=](){
        this->socketReadable();
    });
}

void PacketSocket::socketReadable()
{
    switch(_state) {
        case stateReadingHeader:
            readHeader();
            break;

        case stateReadingBody:
            readBody();
            break;
    }

    if (_socket->bytesAvailable() > 0) {
        socketReadable();
    }

}

void PacketSocket::readHeader()
{
    QByteArray headerBuffer(HEADER_SIZE, 0);
    int res = _socket->read(headerBuffer.data(), HEADER_SIZE);
    if (res != HEADER_SIZE) {
        qFatal("unable to read header");
    }

    _header.Clear();
    if (!_header.ParseFromArray(headerBuffer.data(), HEADER_SIZE)) {
        qFatal("Failed to parse header");
    }

    _state = stateReadingBody;
}

void PacketSocket::readBody()
{
    QByteArray messageBuffer(_header.message_len(), 0);
    int res = _socket->read(messageBuffer.data(), _header.message_len());
    if (res != _header.message_len()) {
        qDebug() << "res=" << res;
        qDebug() << "msg len=" << _header.message_len();
        qFatal("unable to read packet");
    }

    //qDebug() << "Received message, type id: " << _header.message_type() << "req id: " << _header.request_id();

    // ok, message readed, try dispatching it
    HandlerKey key = qMakePair(_header.message_type(), _header.request_id());
    auto i = _handlers.find(key);
    if (i != _handlers.end()) {
        BaseDecoder* dec = *i;
        dec->onMessage(messageBuffer);
        if (dec->singleShot) {
            _handlers.erase(i);
        }
    } else {
        qDebug() << "Unhandled message, type id: " << _header.message_type() << "req id: " << _header.request_id();
    }

    _state = stateReadingHeader;
}

} // namespace Client
} // namespace SpaceOpera
