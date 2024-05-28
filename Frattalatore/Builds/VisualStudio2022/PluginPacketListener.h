#include <iostream>
#include <cstring>

#if defined(__BORLANDC__) // workaround for BCB4 release build intrinsics bug
namespace std {
    using ::__strcmp__;  // avoid error: E2316 '__strcmp__' is not a member of 'std'.
}
#endif

#include "osc/osc/OscReceivedElements.h"
#include "osc/osc/OscPacketListener.h"
#include "osc/ip/UdpSocket.h"

#define PORT 7000
#define ADDRESS "127.0.0.1"
#define HOSTNAME "localhost"

class PluginPacketListener : public osc::OscPacketListener {
protected:
    virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);
};