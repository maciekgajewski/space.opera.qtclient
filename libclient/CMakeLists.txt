add_library(libclient STATIC
    client.cpp client.h
    packetsocket.cpp packetsocket.h
    handshakeSession.cpp handshakeSession.h
)

qt5_use_modules(libclient
	Network
)
