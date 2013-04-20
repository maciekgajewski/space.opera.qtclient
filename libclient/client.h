// Copyright (c) 2013 Maciej Gajewski
#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QAbstractSocket>

class QTcpSocket;

namespace SpaceOpera {
namespace Client {

class PacketSocket;

// General connection controller
// could be split into smalle 'sessions', just as the server part is? could be? huh?
class Client : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ isConnected NOTIFY connectionStateChanged)

public:
    explicit Client(QObject* parent = nullptr);

signals:

    void connectionStateChanged();
    void connectionError(const QString& errorString);

public slots:

    void connectToHost(const QString& hostName, quint16 port);
    void disconnect();


public: // state querying

    bool isConnected() const;

private:

    void networkConnected();
    void networkError(QAbstractSocket::SocketError socketError);

    QTcpSocket* _tcpSocket;
    PacketSocket* _packetSocket;
    bool _connected;
};


}
}

#endif // CLIENT_H
