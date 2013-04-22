// Copyright (c) 2013 Maciej Gajewski

#include "packetsocket.h"

#include "universeSession.h"

namespace SpaceOpera {
namespace Client {

DEFINE_SEND_REQUEST(UniverseSession)

UniverseSession::UniverseSession(QObject *parent) : BaseSession(parent)
{
}

void UniverseSession::changeTimeScale(double newTimeScale)
{
    // TODO
}

} // namespace Client
} // namespace SpaceOpera
