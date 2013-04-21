add_library(libclient STATIC
    client.cpp client.h
    packetsocket.cpp packetsocket.h
    session.cpp session.h
)

qt5_use_modules(libclient
	Network
)
