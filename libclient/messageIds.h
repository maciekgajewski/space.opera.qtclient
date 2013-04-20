// Copyright (c) 2013 Maciej Gajewski

#ifndef MESSAGEIDS_H
#define MESSAGEIDS_H

#include "../protocol_cpp/protocol.pb.h"

namespace SpaceOpera {
namespace Client {

// associates message type with type id
template<typename MessageType>
int GetMessageType();

template<> inline int GetMessageType<spaceopera::hello>() { return spaceopera::mt_hello; }

template<> inline int GetMessageType<spaceopera::hello_reply>() { return spaceopera::mt_hello_reply; }

template<> inline int GetMessageType<spaceopera::get_universes>() { return spaceopera::mt_get_universes; }
template<> inline int GetMessageType<spaceopera::get_universes_reply>() { return spaceopera::mt_get_universes_reply; }

}}

#endif // MESSAGEIDS_H
