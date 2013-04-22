// Copyright (c) 2013 Maciej Gajewski

#ifndef SPACEOPERA_CLIENT_HANDSHAKE_SESSION_H
#define SPACEOPERA_CLIENT_HANDSHAKE_SESSION_H

#include "client.h"

#include"baseSession.h"

#include <functional>

namespace spaceopera {
class hello_reply;
class get_universes_reply;
}

namespace SpaceOpera {
namespace Client {

class HandshakeSession : public BaseSession
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

private:

    DECLARE_SEND_REQUEST(HandshakeSession);

private: // reply handlers

    void onHelloReply(const spaceopera::hello_reply& reply);
    void onUniverses(const spaceopera::get_universes_reply& rep);
    
};

} // namespace Client
} // namespace SpaceOpera

#endif
