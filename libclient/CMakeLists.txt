add_library(libclient STATIC
    baseSession.cpp baseSession.h
    client.cpp client.h
    packetsocket.cpp packetsocket.h
    handshakeSession.cpp handshakeSession.h
    universeSession.cpp universeSession.h
)

qt5_use_modules(libclient
	Network
)
