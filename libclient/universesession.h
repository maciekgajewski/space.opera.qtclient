// Copyright (c) 2013 Maciej Gajewski

#ifndef SPACEOPERA_CLIENT_UNIVERSESESSION_H
#define SPACEOPERA_CLIENT_UNIVERSESESSION_H

#include "baseSession.h"

namespace spaceopera {
    class universe_state_feed;
    class universe_control_reply;
}

namespace SpaceOpera {
namespace Client {

// universe session - startes after handshake and connection to particular universe
class UniverseSession : public BaseSession
{
    Q_OBJECT
public:
    explicit UniverseSession(QObject *parent = 0);
    
signals:
    void universeStateChanged(double currentTime, double currentTimeScale);
    
public slots:
    void changeTimeScale(double newTimeScale);

private: // state management
    virtual void onClientSet() override;

private: // comm handling
    DECLARE_SEND_REQUEST(UniverseSession);

    void onUniverseStateFeed(const spaceopera::universe_state_feed& feed);
    void onUniverseControlReply(const spaceopera::universe_control_reply& rep);



    
};

} // namespace Client
} // namespace SpaceOpera

#endif // SPACEOPERA_CLIENT_UNIVERSESESSION_H
