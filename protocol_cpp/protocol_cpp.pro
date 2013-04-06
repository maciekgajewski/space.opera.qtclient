#-------------------------------------------------
#
# Project created by QtCreator 2013-04-06T19:59:06
#
#-------------------------------------------------

QT       -= core gui

TARGET = protocol_cpp
TEMPLATE = lib
CONFIG += staticlib

SOURCES = protocol.pb.cc
HEADERS = protocol.pb.h

message("Assuming protobuf is in $$protobuf_root")

INCLUDEPATH += $$protobuf_root/include
LIBS += -L$$protobuf_root/lib -lprotobuf

# this is fucking insane
# serously...
# qmake brings out the worst nightmares...

# porotobuf handling
#unix: {
#    isEmpty(protobuf_root) {
#        protobuf_root=/usr
#    }
#}
#message("Looking for protobuf in $$protobuf_root")
#unix {
#    protoc=$$protobuf_root/bin/protoc
#}
#win32 {
#    protoc=$$protobuf_root/bin/protoc.exe
#}

#message("protoc $$protoc")
#!exists($$protoc) {
#    error("unable to find $$ptotoc")
#}

#INCLUDEPATH += $$protobuf_root/include
#LIBS += -L$$protobuf_root/libs -lprotobuf

#PROTOCOL_DIR=../protocol
#PROTOCOL_FILES=protocol.proto

#CPP_FILES = $$PROTOCOL_FILES
#CPP_FILES ~= s/\.proto$/.pb.cpp

#H_FILES = $$PROTOCOL_FILES
#H_FILES ~= s/\.proto$/.pb.h

#message("cpp files: $$CPP_FILES")
#message("h files: $$H_FILES")

#for(protofile, PROTOCOL_FILES) {
#    base=basename(protofile)
#    cpp_file=$${base}.pb.cpp
#    h_file=$${base}.pb.h


#}
#eval("$${x}.f=7") {
#    message("t.f=$$t.f")
#}

