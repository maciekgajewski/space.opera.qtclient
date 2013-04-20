qt5_add_Resources(RESOURCES
    resources.qrc
)

add_executable(uiclient
        ${RESOURCES}
	main.cpp
)

qt5_use_modules(uiclient Network Declarative Quick)

target_link_libraries(uiclient
        libclient
	protocol_cpp

	protobuf
)
