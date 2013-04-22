// Copyright (c) 2013 Maciej Gajewski

#ifndef SPACEOPERA_CLIENT_PACKETSOCKET_H
#define SPACEOPERA_CLIENT_PACKETSOCKET_H

#include "messageIds.h"

#include "../protocol_cpp/protocol.pb.h"

#include <QAbstractSocket>
#include <QHash>
#include <QPair>

namespace SpaceOpera {
namespace Client {

// wraps the socket and the protobuf decoder.
// Allows for registering handlers for responses and asycn notifications
class PacketSocket : public QObject
{
    Q_OBJECT
public:
    PacketSocket(QAbstractSocket* socket, QObject* parent = nullptr);

    // sends requests, awaits reply of specific type/req id
    template<typename ReplyType, typename RequestType /*may be call-deduced*/, typename HandlerType /*call-deduced*/>
    void sendRequest(const RequestType& request, const HandlerType& handler);

private:

    // type-erased decoder type
    struct BaseDecoder
    {
        virtual void onMessage(const QByteArray& data) = 0;
        bool singleShot;
    };

    // concrete decoder type
    template <typename MessageType, typename HandlerType>
    struct Decoder : public BaseDecoder
    {
        Decoder(const HandlerType& handler) : _handler(handler) { }

        virtual void onMessage(const QByteArray& data)
        {
            MessageType msg;
            if (!msg.ParseFromArray(data.data(), data.size())) {
                qFatal("Error parsing message");
            }
            _handler(msg);
        }

    private:
        HandlerType _handler;
    };

    // handler key
    typedef QPair<int, int> HandlerKey; // msg type, req id

    enum State {
        stateReadingHeader,
        stateReadingBody
    };

    QHash<HandlerKey, BaseDecoder*> _handlers;

    // send a message - fire and forget
    template<typename MessageType>
    void send(const MessageType& message, int reqId);

    // register handler for msgtype/reqid combination
    template<typename MessageType, typename HandlerType /*call-deduced*/>
    void registerHandler(int reqId, const HandlerType& handler, bool singleShot);

    void socketReadable();
    void readHeader();
    void readBody();

    QAbstractSocket* _socket;
    int _lastReqId;
    State _state;
    spaceopera::header _header;
};


template<typename MessageType>
void PacketSocket::send(const MessageType& message, int reqId)
{
    spaceopera::header header;

    int msgSize = message.ByteSize();
    int msgType = GetMessageType<MessageType>();

    header.set_message_len(msgSize);
    header.set_message_type(msgType);
    header.set_request_id(reqId);
    int headerSize = header.ByteSize();

    // serialize
    QByteArray buffer(headerSize + msgSize, 0);
    header.SerializeToArray(static_cast<void*>(buffer.data()), headerSize);
    message.SerializePartialToArray(static_cast<void*>(buffer.data()+headerSize), msgSize);

    // send
    int res = _socket->write(buffer);

    if (res != buffer.size())
    {
        qFatal("wrting message failed");
        // TODO handle it better
    }
}

template<typename MessageType, typename HandlerType /*call-deduced*/>
void PacketSocket::registerHandler(int reqId, const HandlerType& handler, bool singleShot)
{
    auto h = new Decoder<MessageType, HandlerType>(handler);
    h->singleShot = singleShot;

    HandlerKey key = qMakePair(GetMessageType<MessageType>(), reqId);

    if (_handlers.contains(key)) {
        qFatal("handler already registered");
    }

    //qDebug() << "Registered handler: msg type: "<< key.first << "req id: " << key.second;

    _handlers.insert(key, h);
}

template<typename ReplyType, typename RequestType, typename HandlerType /*call-deduced*/>
void PacketSocket::sendRequest(const RequestType& request, const HandlerType& handler)
{
    registerHandler<ReplyType>(_lastReqId, handler, true);
    send(request, _lastReqId);
    _lastReqId++;
}


} // namespace Client
} // namespace SpaceOpera

#endif // SPACEOPERA_CLIENT_PACKETSOCKET_H
