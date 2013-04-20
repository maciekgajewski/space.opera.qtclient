// Copyright (c) 2013 Maciej Gajewski
#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>

#include "../protocol_cpp/protocol.pb.h"
#include "../libclient/packetsocket.h"


int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    QCoreApplication a(argc, argv);
    
    // read args
    if (argc < 3) {
        qWarning() << "Usage: textclient [addr] [port]";
        return 1;
    }

    QString addr = argv[1];
    QString portStr = argv[2];
    bool ok = false;
    int port = portStr.toInt(&ok);
    if (!ok || port < 0 || port > 0xffff ){
        qWarning() << portStr << "is not a valid port number";
    }

    // connect
    QTcpSocket socket;
    socket.connectToHost(addr, port);
    if (!socket.waitForConnected(1000)) {
        qWarning() << "Unable to connect to " << addr << port << socket.errorString();
        return 1;
    }

    // send "hello" message
    spaceopera::header header;
    spaceopera::hello hello;

    hello.set_user_name("player");

    /*
    int helloSize = hello.ByteSize();

    header.set_message_len(helloSize);
    header.set_message_type(spaceopera::mt_hello);
    int headerSize = header.ByteSize();
    qDebug() << "header size: " << headerSize << "hello size: " << helloSize;

    // serialize
    QByteArray buffer(headerSize + helloSize, 0);
    header.SerializeToArray(static_cast<void*>(buffer.data()), headerSize);
    hello.SerializePartialToArray(static_cast<void*>(buffer.data()+headerSize), helloSize);

    // send
    socket.write(buffer);
    if (!socket.waitForBytesWritten(1000)) {
        qWarning() << "Error wrting data: " << socket.errorString();
    }
    */
    SpaceOpera::Client::PacketSocket packetSocket(&socket);

    packetSocket.sendRequest<spaceopera::hello_reply>(
        hello,
        [&](const spaceopera::hello_reply& reply) {
            qDebug() << "hallo reply received: ok=" << reply.ok();
            if (reply.has_message()){
                qDebug() << "hallo reply msg: " << QString::fromStdString(reply.message());
            }

            // list universes
            qDebug() << "requesting universes";
            packetSocket.sendRequest<spaceopera::get_universes_reply>(
                spaceopera::get_universes(),
                [](const spaceopera::get_universes_reply& reply) {
                    qDebug() << "universes received: ";
                    for(const std::string& universeName : reply.universe_name()) {
                        qDebug() << " * " << QString::fromStdString(universeName);
                    }
                }
            );
        });

    return a.exec();
}
