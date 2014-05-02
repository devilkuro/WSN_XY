#ifndef TEST_APPLICATION_H
#define WSN_XY_APPLICATION_H

#include <vector>
#include <omnetpp.h>

#include "MiXiMDefs.h"
#include "BaseApplLayer.h"
#include "SimpleAddress.h"
#include "GlobalStatics.h"

class  WSN_XY_Application : public BaseApplLayer {
private:
	/** @brief Copy constructor is not allowed.
	 */
    WSN_XY_Application(const WSN_XY_Application&);
	/** @brief Assignment operator is not allowed.
	 */
    WSN_XY_Application& operator=(const WSN_XY_Application&);

public:
    WSN_XY_Application()
		: BaseApplLayer()
		, dataOut(-1)
		, dataIn(-1)
		, ctrlOut(-1)
		, ctrlIn(-1)
		, nodeAddr()
		, dstAddr()
		, debug(false), stats(false), trace(false)
		, isTransmitting(false)
        ,alpha(0),beta0(0),beta1(0),beta2(0),beta3(0)
        ,radius(0),dist(0)
        ,initialRelayEnergy(0),deadRelayEnergy(0)
        ,i(0),j(0),u(0),v(0),N(0)
        ,relayNodeSize(0)
        ,relayNodeEnergy(NULL)
        ,sensorTimer(NULL)
	{}

    virtual ~WSN_XY_Application();

    virtual void initialize(int stage);
    virtual void handleSelfMsg(cMessage* msg);
    virtual void handleLowerMsg(cMessage* msg);
    virtual void handleLowerControl(cMessage* msg);
    virtual void finish();
public:
    enum  WSN_XY_MessageKinds {
        /** @brief Schedules sending of a new message.*/
        SEND_PACKET_TIMER = LAST_BASE_APPL_MESSAGE_KIND,
        /** @brief The kind for a packet send by this layer.*/
        WSN_XY_SENSOR_TIMER,
        WSN_XY_PACKET,
        /** @brief Sub classing layers shoudl begin their own kinds at this value.*/
        LAST_WSN_XY_MESSAGE_KIND
    };
    enum WSN_XY_EN_TYPE {
        SENSOR_ENERGY,
        TRANSMIT_ENERGY,
        OTHER
    };

protected:

    // gates
    int dataOut;
    int dataIn;
    int ctrlOut;
    int ctrlIn;

    // timers

    // module parameters
    LAddress::L3Type nodeAddr;
    LAddress::L3Type dstAddr;
    bool debug, stats, trace;
    bool isTransmitting;

    //static id

    // constants

    // state variables
private:
    //private functions
    void sendSensorData(cMessage* msg);
    void transimitSensorData(cMessage* msg);
    void consumeSensorEnergy();
    void consumeTransmitEnergy(double distance);
private:
    //experimental parameters
    double alpha;
    double beta0,beta1,beta2,beta3;
    double radius;
    double dist;

    double initialRelayEnergy; // initial energy of the relay node
    double deadRelayEnergy; // death threshold of the relay node
    double initialSensorEnergy; // initial energy of the sensor node
    double deadSensorEnergy; // death threshold of the sensor node
    //private members
    int i,j,u,v,N; //level,id in level,section,offset,total level.
    int relayNodeSize; //number of the relay nodes
    double *relayNodeEnergy; // energy array of the relay nodes
    int activatedRelayNode; // the index number of current relay node
    cMessage *sensorTimer; // sensor timer msg

    //static id
    static int nodeId; // node id
    static int recordId; // record id
    static GlobalStatics globalStatics; // the statics class
};

#endif // WSN_XY_APPLICATION_H

