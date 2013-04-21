// Copyright (c) 2013 Maciej Gajewski

#include "session.h"

#include "packetsocket.h"
#include "client.h"

#include "../protocol_cpp/protocol.pb.h"

#include <QStringList>


namespace SpaceOpera {
namespace Client {

Session::Session(QObject *parent) :
    QObject(parent), _client(nullptr)
{
}

void Session::authenticate(const QString& username, const QString& password)
{
    qDebug("Session::authenticate");

    spaceopera::hello hello;
    hello.set_user_name(username.toLocal8Bit());
    hello.set_password(password.toLocal8Bit());

    sendRequest(hello, &Session::onHelloReply);
}

void Session::requestUniverses()
{
    qDebug("Session::requestUniverses");
    Q_ASSERT(_client);

    spaceopera::get_universes req;
    sendRequest(req, &Session::onUniverses);
}

PacketSocket& Session::packetSocket() const
{
    Q_ASSERT(_client);
    return _client->packetSocket();
}

template<typename ReplyType, typename RequestType>
void Session::sendRequest(const RequestType& req, void (Session::*reqHandler)(const ReplyType&) )
{
    packetSocket().sendRequest<ReplyType>(req, [=](const ReplyType& rep) { (this->*reqHandler)(rep); });
}

void Session::onHelloReply(const spaceopera::hello_reply& reply)
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

void Session::onUniverses(const spaceopera::get_universes_reply& rep)
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
