#include "WSN_XY_Application.h"

#include <sstream>

#include "BaseMacLayer.h"
#include "NetwControlInfo.h"
#include "WSN_XY_ApplPkt_m.h"

#define NETW_OFFSET 4
using std::endl;


Define_Module(WSN_XY_Application);

int WSN_XY_Application::nodeId = 0;
int WSN_XY_Application::recordId = 0;
GlobalStatistics WSN_XY_Application::globalStatics = GlobalStatistics();

static int getHexagonLevel(int id);
static int getHexagonIndex(int id);
static int getRelayNodeSize(int i,int v,int N, double w);
static int getNextHop(int i,int j,int u,int v);

WSN_XY_Application::~WSN_XY_Application() {
    // TODO Auto-generated method stub
    if(sensorTimer){
        cancelAndDelete(sensorTimer);
    }
    delete(relayNodeEnergy);
}

void WSN_XY_Application::initialize(int stage) {
    // TODO Auto-generated method stub
    BaseApplLayer::initialize(stage);
    if (stage == 0)
    {
        // initialize all experimental parameters in stage 0.
        alpha = hasPar("alpha")?par("alpha"):2;
        beta0 = hasPar("beta0")?par("beta0"):2;
        beta1 = hasPar("beta1")?par("beta1"):2;
        beta2 = hasPar("beta2")?par("beta2"):2;
        beta3 = hasPar("beta3")?par("beta3"):2;
        radius = hasPar("radius")?par("radius"):2;
        dist = hasPar("dist")?par("dist"):2;
        initialRelayEnergy = hasPar("initialRelayEnergy")?par("initialRelayEnergy"):2;
        deadRelayEnergy = hasPar("deadRelayEnergy")?par("deadRelayEnergy"):2;
        initialSensorEnergy = hasPar("initialSensorEnergy")?par("initialSensorEnergy"):2;
        deadSensorEnergy = hasPar("deadSensorEnergy")?par("deadSensorEnergy"):2;
        sensorInterval = hasPar("sensorInterval")?par("sensorInterval"):2;
        terminateDelay = hasPar("terminateDelay")?par("terminateDelay"):2;
        statisticsInterval =  hasPar("statisticsInterval")?par("statisticsInterval"):2;
        i=getHexagonLevel(nodeId);
        j=getHexagonIndex(nodeId);
        if(i!=0){
            v=j%i;
            u=j/i;
        }else{
            v = 0;
            j = 0;
        }
        nodeAddr = LAddress::L3Type(nodeId+NETW_OFFSET);
        EV<<"the app address: "<<myApplAddr()<<"\nthe node address: "<<nodeAddr<<"\nthe netwl address: "<<getNode()->getId()<<"\nthe mac address: "<<getNode()->getIndex()<<endl;
        // modify the static members
        nodeId++;
        recordId++;
    }else if(stage == 1){
        N=getHexagonLevel(nodeId);
        relayNodeSize = getRelayNodeSize(i,v,N,1.0); // FIXME the fourth argument is temporarily set to 1.0
        relayNodeEnergy = new double[relayNodeSize];
        for(int i = 0;i<relayNodeSize;i++){
            relayNodeEnergy[i] = initialRelayEnergy;
        }
        activatedRelayNode = 0;
        sensorTimer = new cMessage("sensor timer",WSN_XY_SENSOR_TIMER);
        scheduleAt(simTime()+terminateDelay*(nodeAddr-NETW_OFFSET)/(2*nodeId),sensorTimer);
        sensorNodeEnergy = initialSensorEnergy;
        statisticsTimer = statisticsInterval;
    }
}

void WSN_XY_Application::handleSelfMsg(cMessage* msg) {
    // TODO Auto-generated method stub
    switch (msg->getKind())
    {
        case WSN_XY_SENSOR_TIMER:
            sendSensorData(msg);
            break;
        case WSN_XY_TERMINATE_MSG:
            endSimulation();
            cancelAndDelete(msg);
            break;
        default:
            EV << " Unkown selfmessage! kind: " << msg->getKind() << std::endl;
            delete(msg);
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
            delete(msg);
            break;
    }
}

void WSN_XY_Application::handleLowerControl(cMessage* msg) {
    // TODO do nothing for NOW
    if(msg){
        delete(msg);
        msg = NULL;
    }
}

void WSN_XY_Application::finish() {
    // TODO Auto-generated method stub
    {
        globalStatics.record("finish::sensor node remainder energy: i,j,u,v,energy", 5,
                (double) i, (double) j, (double) u, (double) v,
                (double) sensorNodeEnergy);
        globalStatics.record(
                "finish::activated relay node remainder energy: i,j,u,v,n,energy", 6,
                (double) i, (double) j, (double) u, (double) v,
                (double) activatedRelayNode,
                (double) relayNodeEnergy[activatedRelayNode]);
        for (int loop = 0; loop < relayNodeSize; loop++) {
            globalStatics.record(
                    "finish::relay node remainder energy: i,j,u,v,n,energy", 6,
                    (double) i, (double) j, (double) u, (double) v,
                    (double) loop, (double) relayNodeEnergy[loop]);
        }
    }
    recordId--;
    if(recordId==0){
        stringstream ss;
        ss<<"WSN_XY.log";
        globalStatics.output(ss.str());
    }
}

void WSN_XY_Application::sendSensorData(cMessage* msg) {
    // TODO Auto-generated method stub
    if(nodeAddr!=0+NETW_OFFSET&&consumeSensorEnergy()){
        if(--statisticsTimer<=0){
            globalStatics.record("sensor node remainder energy: i,j,u,v,energy",
                    5,(double)i,(double)j,(double)u,(double)v,(double)sensorNodeEnergy);
            globalStatics.record("activated relay node remainder energy: i,j,u,v,n,energy",
                    6,(double)i,(double)j,(double)u,(double)v,(double)activatedRelayNode,(double)relayNodeEnergy[activatedRelayNode]);
            for(int loop = 0; loop<relayNodeSize;loop++){
                globalStatics.record("relay node remainder energy: i,j,u,v,n,energy",
                        6,(double)i,(double)j,(double)u,(double)v,(double)loop,(double)relayNodeEnergy[loop]);
            }
            statisticsTimer=statisticsInterval;
        }
        EV<<"statistics out:"<<i<<","<<j<<","<<u<<","<<v<<endl;
        WSN_XY_ApplPkt *pkt = new WSN_XY_ApplPkt("sensor data", WSN_XY_PACKET);
        LAddress::L3Type dstAddr = LAddress::L3Type(getNextHop(i,j,u,v));
        pkt->setI(i);
        pkt->setJ(j);
        pkt->setU(u);
        pkt->setV(v);
        pkt->setSrcAddr(nodeAddr);
        pkt->setDestAddr(dstAddr);
        NetwControlInfo::setControlInfo(pkt,pkt->getDestAddr());
        EV<<"send sensor data, the destaination is "<<dstAddr<<"."<<endl;
        EV<<"send sensor data, the source is "<<nodeAddr<<"."<<endl;
        sendDown(pkt);
        if(msg->isScheduled()){
            cancelEvent(msg);
        }
        scheduleAt(simTime()+sensorInterval,sensorTimer);
    }
}

void WSN_XY_Application::transimitSensorData(cMessage* msg) {
    // TODO Auto-generated method stub
    WSN_XY_ApplPkt* pkt;
    pkt = static_cast<WSN_XY_ApplPkt *>(msg);
    if(nodeAddr!=0+NETW_OFFSET&&consumeTransmitEnergy(0,0)){
        WSN_XY_ApplPkt* pktdup = pkt->dup();
        LAddress::L3Type dstAddr = LAddress::L3Type(getNextHop(i,j,u,v));
        pktdup->setSrcAddr(nodeAddr);
        pktdup->setDestAddr(dstAddr);
        NetwControlInfo::setControlInfo(pktdup,pktdup->getDestAddr());
        sendDown(pktdup);
    }
    delete (pkt);
}

bool WSN_XY_Application::consumeSensorEnergy() {
    double consumedEnergy = 1.1725/10000;
    if(sensorNodeEnergy >consumedEnergy+deadSensorEnergy){
        sensorNodeEnergy-=consumedEnergy;
        return true;
    }
    else{
        scheduleAt(simTime()+terminateDelay, new cMessage("terminate msg: sensor", WSN_XY_TERMINATE_MSG));
        return false;
    }
}

bool WSN_XY_Application::consumeTransmitEnergy(double distance , int bits) {
    double consumedEnergy = 1.9225/10000;
    if(relayNodeEnergy[activatedRelayNode]>consumedEnergy+deadRelayEnergy){
        relayNodeEnergy[activatedRelayNode]-=consumedEnergy;
    }else{
        activatedRelayNode++;
        if(activatedRelayNode<relayNodeSize){
            relayNodeEnergy[activatedRelayNode]-=consumedEnergy;
        }else{
            scheduleAt(simTime()+terminateDelay, new cMessage("terminate msg: transimit", WSN_XY_TERMINATE_MSG));
            return false;
        }
    }
    return true;
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
    if(i==1)
        return 0+NETW_OFFSET;
    if(v!=0&&rand()>0.5){
        return 3*(i-1)*((i-1)-1)+(i-1)*u+(v-1)+1+NETW_OFFSET;
    }else
        return 3*(i-1)*((i-1)-1)+(i-1)*u+(v-0)+1+NETW_OFFSET;
}


