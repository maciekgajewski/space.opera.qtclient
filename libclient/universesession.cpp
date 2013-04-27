// Copyright (c) 2013 Maciej Gajewski

#include "universeSession.h"

#include "packetsocket.h"

#include "../protocol_cpp/protocol.pb.h"


namespace SpaceOpera {
namespace Client {

DEFINE_SEND_REQUEST(UniverseSession)

UniverseSession::UniverseSession(QObject *parent) : BaseSession(parent)
{
}

void UniverseSession::changeTimeScale(double newTimeScale)
{
    spaceopera::universe_control req;
    req.set_new_time_scale(newTimeScale);

    sendRequest(req, &UniverseSession::onUniverseControlReply);
}

void UniverseSession::onUniverseStateFeed(const spaceopera::universe_state_feed& feed)
{
    emit universeStateChanged(feed.current_time(), feed.time_scale());
}

void UniverseSession::onUniverseControlReply(const spaceopera::universe_control_reply& reply)
{
    if (reply.ok()) {
        qDebug("UniverseSession::onUniverseControlReply: ok");
    } else {
        QString err(QStringLiteral("Unknwon error"));
        if (reply.has_message()) {
            err = QString::fromStdString(reply.message());
        }
        emit sessionError(err);
    }
}

void UniverseSession::onClientSet()
{
    subscribeFeed(&UniverseSession::onUniverseStateFeed);
}

} // namespace Client
} // namespace SpaceOpera
