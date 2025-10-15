//
// Created by orangetee on 10/12/25.

#ifndef PROTOCOLBASE_H
#define PROTOCOLBASE_H

#include <memory>

#include "MessageHeader.h"
#include "server_messages/EndMessage.h"
#include "server_messages/InitMessage.h"
#include "server_messages/TransMessage.h"


/**
 * Implements interaction according to the protocol, manages the connection state!
 */
class ProtocolBase {
public:
    virtual ~ProtocolBase() = default;

    // Get methods
    virtual std::unique_ptr<MessageHeader> getMessageHeader() = 0;
    virtual std::unique_ptr<InitMessage> getInitMessage(size_t length) = 0;
    virtual std::unique_ptr<TransMessage> getTransMessage(size_t length) = 0;
    virtual std::unique_ptr<EndMessage> getEndMessage(size_t length) = 0;
    virtual bool checkAckInit() = 0;
    virtual bool checkAckTrans() = 0;

    // Send methods
    virtual void sendInitMessage(InitMessage*) = 0;
    virtual void sendTransMessage(TransMessage*) = 0;
    virtual void sendEndMessage(EndMessage*) = 0;
    virtual void sendAckInit() = 0;
    virtual void sendAckTrans() = 0;
    virtual void sendStatus(bool) = 0;
};

#endif //PROTOCOLBASE_H
