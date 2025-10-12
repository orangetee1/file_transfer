//
// Created by orangetee on 10/12/25.
//

#ifndef PROTOCOLUSAGE_H
#define PROTOCOLUSAGE_H

#include <memory>

#include "messages/EndMessage.h"
#include "messages/Header.h"
#include "messages/InitMessage.h"
#include "messages/SpeedMessage.h"
#include "messages/TransMessage.h"

class ProtocolUsage {
public:
    virtual ~ProtocolUsage() = default;

    // Get methods
    virtual std::unique_ptr<Header> getHeader() = 0;
    virtual std::unique_ptr<InitMessage> getInit() = 0;
    virtual std::unique_ptr<TransMessage> getTrans() = 0;
    virtual std::unique_ptr<EndMessage> getEnd() = 0;
    virtual std::unique_ptr<SpeedMessage> getSpeed() = 0;
    virtual bool getAckInit() = 0;
    virtual bool getAckTrans() = 0;

    // Send methods
    virtual void sendHeader(Header*) = 0;
    virtual void sendInit(InitMessage*) = 0;
    virtual void sendTrans(TransMessage*) = 0;
    virtual void sendEnd(EndMessage*) = 0;
    virtual void sendSpeed(SpeedMessage*) = 0;
    virtual void sendAckInit() = 0;
    virtual void sendAckTrans() = 0;
};



#endif //PROTOCOLUSAGE_H
