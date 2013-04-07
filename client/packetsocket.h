// Copyright (c) 2013 Maciej Gajewski

#ifndef SPACEOPERA_CLIENT_PACKETSOCKET_H
#define SPACEOPERA_CLIENT_PACKETSOCKET_H

#include "messageIds.h"

#include "../protocol_cpp/protocol.pb.h"

#include <QAbstractSocket>

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
    template<typename RequestType, typename ReplyType, typename HandlerType /*call-deduced*/>
    void SendReuest(const RequestType& request, const HandlerType& handler);

private:

    // decodre type
    struct BaseDecoder
    {
        virtual OnMessage(const QByteArray& data) = 0;
    };

    // send a message - fire and forget
    template<typename MessageType>
    void Send(const MessageType& message, int reqId);

    // register handler for msgtype/reqid combination
    template<typename MessageType, typename HandlerType /*call-deduced*/>
    void RegisterHandler(int reqId, const HandlerType& handler);


    QAbstractSocket* _socket;
};


template<typename MessageType>
void PacketSocket::Send(const MessageType& message, int reqId)
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
    _socket->write(buffer);
}


} // namespace Client
} // namespace SpaceOpera

#endif // SPACEOPERA_CLIENT_PACKETSOCKET_H
