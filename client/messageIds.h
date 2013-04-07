// Copyright (c) 2013 Maciej Gajewski

#ifndef MESSAGEIDS_H
#define MESSAGEIDS_H

#include "../protocol_cpp/protocol.pb.h"

namespace SpaceOpera {
namespace Client {

// associates message type with type id
template<typename MessageType>
int GetMessageType();

template<>
int GetMessageType<spaceopera::hello>() { return spaceopera::mt_hello; }

template<>
int GetMessageType<spaceopera::hello_reply>() { return spaceopera::mt_hello_reply; }

}}

#endif // MESSAGEIDS_H
