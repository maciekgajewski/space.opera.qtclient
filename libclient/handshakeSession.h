// Copyright (c) 2013 Maciej Gajewski

#ifndef SPACEOPERA_CLIENT_SESSION_H
#define SPACEOPERA_CLIENT_SESSION_H

#include "client.h"

#include <QObject>

namespace spaceopera {
class hello_reply;
class get_universes_reply;
}

namespace SpaceOpera {
namespace Client {

class PacketSocket;

class HandshakeSession : public QObject
{
    Q_OBJECT

    Q_PROPERTY(SpaceOpera::Client::Client* client READ client WRITE setClient)

public:
    explicit HandshakeSession(QObject *parent = 0);
    
signals:
    
    void authenticated();
    void sessionError(const QString& errorText);
    void universesReceived(const QStringList& univereses);

public slots:

    void authenticate(const QString& username, const QString& password);
    void requestUniverses();

public:

    void setClient(Client* c) { _client = c; }
    Client* client() const { return _client; }

private:

    template<typename ReplyType, typename RequestType>
    void sendRequest(const RequestType& req, void (HandshakeSession::*reqHandler)(const ReplyType&) );

    PacketSocket& packetSocket() const;

private: // reply handlers

    void onHelloReply(const spaceopera::hello_reply& reply);
    void onUniverses(const spaceopera::get_universes_reply& rep);

    Client* _client;
    
};

} // namespace Client
} // namespace SpaceOpera

#endif // SPACEOPERA_CLIENT_SESSION_H
