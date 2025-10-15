//
// Created by orangetee on 10/12/25.
//

#ifndef PROTOCOLV1BASE_H
#define PROTOCOLV1BASE_H

#include "../ProtocolBase.h"

#include <memory>

#include "../../net/ConnectionState.h"
#include "../../server/ClientStats.h"

class ProtocolV1Base : public ProtocolBase {
public:
    ProtocolV1Base(int socket, std::shared_ptr<ConnectionState> connection_state, std::shared_ptr<ClientStats> client_stats);

    ~ProtocolV1Base() override;

    std::unique_ptr<MessageHeader> getMessageHeader() override;

    std::unique_ptr<InitMessage> getInitMessage(size_t length) override;

    std::unique_ptr<TransMessage> getTransMessage(size_t length) override;

    std::unique_ptr<EndMessage> getEndMessage(size_t length) override;

    void sendInitMessage(InitMessage *) override;

    bool checkAckInit() override;

    bool checkAckTrans() override;

    void sendTransMessage(TransMessage *) override;

    void sendEndMessage(EndMessage *) override;

    void sendAckInit() override;

    void sendAckTrans() override;

    void sendStatus(bool) override;

private:
    // Data
    int socket_;
    std::shared_ptr<ConnectionState> connection_state_;
    std::shared_ptr<ClientStats> client_stats_;

    // Methods
    bool recv_all_(uint8_t* buffer, size_t length);
    bool send_all_(uint8_t* buffer, size_t length);


};



#endif //PROTOCOLV1BASE_H
