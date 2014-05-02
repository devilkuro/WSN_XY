#include "WSN_XY_Application.h"

#include <sstream>

#include "BaseMacLayer.h"
#include "NetwControlInfo.h"
#include "WSN_XY_ApplPkt_m.h"

using std::endl;

Define_Module(WSN_XY_Application);

int WSN_XY_Application::nodeId = 0;
int WSN_XY_Application::recordId = 0;
GlobalStatics WSN_XY_Application::globalStatics = GlobalStatics();

static int getHexagonLevel(int id);
static int getHexagonIndex(int id);
static int getRelayNodeSize(int i,int v,int N, double w);
static int getNextHop(int i,int j,int u,int v);

WSN_XY_Application::~WSN_XY_Application() {
    // TODO Auto-generated method stub
}

void WSN_XY_Application::initialize(int stage) {
    // TODO Auto-generated method stub
    BaseApplLayer::initialize(stage);
    if (stage == 0)
    {

        i=getHexagonLevel(nodeId);
        j=getHexagonIndex(nodeId);
        v=j%i;
        u=j/i;
        nodeId++;
        recordId++;
        sensorTimer = new cMessage("sensor timer",WSN_XY_SENSOR_TIMER);
        nodeAddr = LAddress::L3Type(nodeId);
    }else if(stage == 1){
        N=getHexagonLevel(nodeId);
        relayNodeSize = getRelayNodeSize(i,v,N,1.0);
        relayNodeEnergy = new double[relayNodeSize];
        for(int i = 0;i<relayNodeSize;i++){
            relayNodeEnergy[i] = initialRelayEnergy;
        }
    }
}

void WSN_XY_Application::handleSelfMsg(cMessage* msg) {
    // TODO Auto-generated method stub
    switch (msg->getKind())
    {
        case WSN_XY_SENSOR_TIMER:
            sendSensorData(msg);
            break;
        default:
            EV << " Unkown selfmessage! kind: " << msg->getKind() << std::endl;
            break;
    }
}

void WSN_XY_Application::handleLowerMsg(cMessage* msg) {
    // TODO Auto-generated method stub
    switch (msg->getKind())
    {
        case WSN_XY_PACKET:
            transimitSensorData(msg);
            break;
        default:
            EV << " Unkown selfmessage! kind: " << msg->getKind() << std::endl;
            break;
    }
}

void WSN_XY_Application::handleLowerControl(cMessage* msg) {
    // TODO do nothing for NOW
}

void WSN_XY_Application::finish() {
    // TODO Auto-generated method stub
    stringstream ss;
    ss<<"WSN_XY_"<<rand()<<".log";
    recordId--;
    if(recordId==0){
        globalStatics.output(ss.str());
    }
}

void WSN_XY_Application::sendSensorData(cMessage* msg) {
    // TODO Auto-generated method stub
}

void WSN_XY_Application::transimitSensorData(cMessage* msg) {
    // TODO Auto-generated method stub
    WSN_XY_ApplPkt* pkt;
    pkt = static_cast<WSN_XY_ApplPkt *>(msg);
}

inline int getHexagonLevel(int id) {
    if(id == 0)
        return 0;
    else
        return (int) (sqrt((id-1)/3.0+0.25)+0.5);
}

inline int getHexagonIndex(int id) {
    if(id == 0){
        return 0;
    }
    else{
        int n = getHexagonLevel(id);
        return id-3*n*(n-1)-1;
    }
}

inline int getRelayNodeSize(int i,int v, int N, double w) {
    if(v==0)
        return 3*(N-i+1)*(N-i)*w;
    else
        return (N-i)*w;
}

inline int getNextHop(int i, int j, int u, int v) {
    if(v!=0&&rand()>0.5){
        return 3*(i-1)*((i-1)-1)+(i-1)*u+(v-1)+1;
    }else
        return 3*(i-1)*((i-1)-1)+(i-1)*u+(v-0)+1;
}
