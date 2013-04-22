// Copyright (c) 2013 Maciej Gajewski

#ifndef SPACEOPERA_CLIENT_BASESESSION_H
#define SPACEOPERA_CLIENT_BASESESSION_H

#include <QObject>

namespace SpaceOpera {
namespace Client {

class PacketSocket;
class Client;

// common session logic
class BaseSession : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SpaceOpera::Client::Client* client READ client WRITE setClient)

public:
    explicit BaseSession(QObject *parent = 0);

signals:

    void sessionError(const QString& errorText);

public:

    void setClient(Client* c) { _client = c; }
    Client* client() const { return _client; }

protected:

    PacketSocket& packetSocket() const;

private:

    Client* _client;

};

#define DECLARE_SEND_REQUEST(ClassName) \
    template<typename ReplyType, typename RequestType> \
    void sendRequest(const RequestType& req, void (ClassName::*reqHandler)(const ReplyType&) )

#define DEFINE_SEND_REQUEST(ClassName) \
    template<typename ReplyType, typename RequestType>\
    void ClassName::sendRequest(const RequestType& req, void (ClassName::*reqHandler)(const ReplyType&) )\
    {\
        packetSocket().sendRequest<ReplyType>(req, [=](const ReplyType& rep) { (this->*reqHandler)(rep); });\
    }


}} // ns

#endif
