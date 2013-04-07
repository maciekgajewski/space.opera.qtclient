// Copyright (c) 2013 Maciej Gajewski

#include "packetsocket.h"

namespace SpaceOpera {
namespace Client {

PacketSocket::PacketSocket(QAbstractSocket *socket, QObject* parent)
    : QObject(parent), _socket(socket)
{
}

} // namespace Client
} // namespace SpaceOpera
