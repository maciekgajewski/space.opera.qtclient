#-------------------------------------------------
#
# Project created by QtCreator 2013-04-06T20:00:07
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = textclient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

message("Assuming protobuf is in $$protobuf_root")

INCLUDEPATH += $$protobuf_root/include
LIBS += -L$$protobuf_root/lib -lprotobuf
LIBS += -L../protocol_cpp -lprotocol_cpp
