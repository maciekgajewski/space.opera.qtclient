// Copyright (c) 2013 Maciej Gajewski

#include "handshakeSession.h"

#include "packetsocket.h"
#include "client.h"

#include "../protocol_cpp/protocol.pb.h"

#include <QStringList>


namespace SpaceOpera {
namespace Client {

HandshakeSession::HandshakeSession(QObject *parent) :
    QObject(parent), _client(nullptr)
{
}

void HandshakeSession::authenticate(const QString& username, const QString& password)
{
    qDebug("Session::authenticate");

    spaceopera::hello hello;
    hello.set_user_name(username.toLocal8Bit());
    hello.set_password(password.toLocal8Bit());

    sendRequest(hello, &HandshakeSession::onHelloReply);
}

void HandshakeSession::requestUniverses()
{
    qDebug("Session::requestUniverses");
    Q_ASSERT(_client);

    spaceopera::get_universes req;
    sendRequest(req, &HandshakeSession::onUniverses);
}

PacketSocket& HandshakeSession::packetSocket() const
{
    Q_ASSERT(_client);
    return _client->packetSocket();
}

template<typename ReplyType, typename RequestType>
void HandshakeSession::sendRequest(const RequestType& req, void (HandshakeSession::*reqHandler)(const ReplyType&) )
{
    packetSocket().sendRequest<ReplyType>(req, [=](const ReplyType& rep) { (this->*reqHandler)(rep); });
}

void HandshakeSession::onHelloReply(const spaceopera::hello_reply& reply)
{
    if (reply.ok()) {
        qDebug("Session::onHelloReply: ok");
        emit authenticated();
    } else {
        QString err(QStringLiteral("Unknwon error"));
        if (reply.has_message()) {
            err = QString::fromStdString(reply.message());
        }
        emit sessionError(err);
    }
}

void HandshakeSession::onUniverses(const spaceopera::get_universes_reply& rep)
{
    qDebug("Session::onUniverses");
    QStringList universes;
    for(const std::string& u : rep.universe_name()) {
        universes.push_back(QString::fromStdString(u));
    }

    emit universesReceived(universes);
}

} // namespace Client
} // namespace SpaceOpera
