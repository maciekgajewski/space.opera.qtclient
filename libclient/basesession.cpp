// Copyright (c) 2013 Maciej Gajewski

#include "client.h"

#include "baseSession.h"

namespace SpaceOpera {
namespace Client {

BaseSession::BaseSession(QObject *parent) :
    QObject(parent),
    _client(nullptr)
{
}

PacketSocket& BaseSession::packetSocket() const
{
    Q_ASSERT(_client);
    return _client->packetSocket();
}

}}
