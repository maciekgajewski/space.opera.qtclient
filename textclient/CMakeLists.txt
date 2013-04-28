add_executable(textclient
	main.cpp
)

qt5_use_modules(textclient Network)

target_link_libraries(textclient
        libclient
	protocol_cpp

	protobuf
	pthread
)
