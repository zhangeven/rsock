//
// Created by System Administrator on 1/19/18.
//

#ifndef RSOCK_IAPPCONN_H
#define RSOCK_IAPPCONN_H

#include <rscomm.h>
#include "IGroup.h"
#include "../bean/EncHead.h"
#include "../src/service/INetObserver.h"

class INetGroup;

class INetConn;

class INetConnKeepAlive;

class IReset;

struct ConnInfo;

class IAppGroup : public IGroup {
public:
    IAppGroup(const std::string &groupId, INetGroup *fakeNetGroup, IConn *btm);

    int Init() override;

    int Close() override;

    int Send(ssize_t nread, const rbuf_t &rbuf) override;

    int Input(ssize_t nread, const rbuf_t &rbuf) override;

    INetGroup *GetNetGroup() const { return mFakeNetGroup; }

    void Flush(uint64_t now) override;

    INetGroup *NetGroup() { return mFakeNetGroup; }

    /*
     * return true if this rst/fin information is processed by this group
     */
    bool ProcessTcpFinOrRst(const TcpInfo &info);

//    bool OnUdpRst(const ConnInfo &info) override;

    bool Alive() override;

    virtual int SendConvRst(uint32_t conv);

    virtual int doSendCmd(uint8_t cmd, ssize_t nread, const rbuf_t &rbuf);

    // todo: refactor mhead and this method
    virtual int SendNetConnReset(ssize_t nread, const rbuf_t &rbuf, IntKeyType keyOfConnToReset);

protected:
    EncHead mHead;  // todo: refactor mhead. error prone

private:
    IReset *mResetHelper = nullptr;
    INetConnKeepAlive *mKeepAlive = nullptr;
    INetGroup *mFakeNetGroup = nullptr;
};


#endif //RSOCK_IAPPCONN_H
