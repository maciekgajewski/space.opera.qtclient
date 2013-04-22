// Copyright (c) 2013 Maciej Gajewski

#include "handshakeSession.h"

#include "packetsocket.h"
#include "client.h"

#include "../protocol_cpp/protocol.pb.h"

#include <QStringList>


namespace SpaceOpera {
namespace Client {

DEFINE_SEND_REQUEST(HandshakeSession)

HandshakeSession::HandshakeSession(QObject *parent) :
    BaseSession(parent)
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

    spaceopera::get_universes req;
    sendRequest(req, &HandshakeSession::onUniverses);
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
