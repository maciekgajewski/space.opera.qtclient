#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T20:19:50
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = client
TEMPLATE = lib
CONFIG += staticlib
QMAKE_CXXFLAGS += -std=c++11

SOURCES += client.cpp \
    packetsocket.cpp

HEADERS += client.h \
    packetsocket.h \
    messageIds.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
message("Assuming protobuf is in $$protobuf_root")

INCLUDEPATH += $$protobuf_root/include
LIBS += -L$$protobuf_root/lib -lprotobuf
LIBS += -L../protocol_cpp -lprotocol_cpp
