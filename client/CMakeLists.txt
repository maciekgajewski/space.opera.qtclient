add_library(client STATIC
	client.cpp client.h
	packetsocket.cpp packetsocket.h
)

qt5_use_modules(client
	Network
)
