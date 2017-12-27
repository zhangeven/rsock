//
// Created by System Administrator on 12/26/17.
//

#include "SSockApp.h"
#include "../RConfig.h"
#include "SRawConn.h"
#include "../RConfig.h"

SSockApp::SSockApp(uv_loop_t *loop) : ISockApp(true, loop) {}

RCap *SSockApp::CreateCap(RConfig &conf) {
    return new RCap(conf.param.dev, conf.param.selfCapIp, conf.param.selfCapPorts, conf.param.targetCapPorts, "", conf.param.interval);
}

IRawConn *SSockApp::CreateBtmConn(RConfig &conf, libnet_t *l, uv_loop_t *loop, int datalink) {
    return new SRawConn(l, conf.param.selfCapInt, loop, conf.param.hashKey, "", conf.param.targetCapInt, datalink);
}

IConn *SSockApp::CreateBridgeConn(RConfig &conf, IRawConn *btm, uv_loop_t *loop) {
    struct sockaddr_in target = {0};
    target.sin_family = AF_INET;
    target.sin_port = htons(conf.param.targetCapPorts[0]);
    inet_aton(conf.param.targetIp.c_str(), &target.sin_addr);
    return new ServerGroupConn(conf.param.id, loop, btm, reinterpret_cast<const sockaddr *>(&target),
                               conf.param.selfCapPorts);
}