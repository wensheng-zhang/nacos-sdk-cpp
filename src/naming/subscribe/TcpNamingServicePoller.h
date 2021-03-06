//
// Created by liuhanyu on 2020/9/26.
//

#ifndef NACOS_SDK_CPP_TCPNAMINGSERVICEPOLLER_H
#define NACOS_SDK_CPP_TCPNAMINGSERVICEPOLLER_H

#include <map>
#include "src/thread/Thread.h"
#include "src/naming/NamingProxy.h"
#include "EventDispatcher.h"
#include "src/factory/ObjectConfigData.h"

namespace nacos{
struct PollingData
{
    NacosString serviceName;
    NacosString groupName;
    NacosString clusters;
};

class TcpNamingServicePoller
{
private:
    Thread *_pollingThread = NULL;
    int _pollingInterval;//In ms
    bool _started;
    ObjectConfigData *_objectConfigData;

    TcpNamingServicePoller();

    static void *pollingThreadFunc(void *parm);

    RWLock rwLock;
    std::map<NacosString, PollingData> pollingList;
    std::map<NacosString, ServiceInfo> serviceInfoList;
public:
    TcpNamingServicePoller(ObjectConfigData *objectConfigData);
    bool addPollItem(const NacosString &serviceName, const NacosString &groupName, const NacosString &clusters);
    bool removePollItem(const NacosString &serviceName, const NacosString &groupName, const NacosString &clusters);
    void start();
    void stop();
    ~TcpNamingServicePoller();

};
}//namespace nacos

#endif //NACOS_SDK_CPP_TCPNAMINGSERVICEPOLLER_H
