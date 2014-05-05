

#include "WSN_XY_Mobility.h"
#include "FWMath.h"
#include "math.h"


Define_Module(WSN_XY_Mobility);
static int getHexagonLevel(int id);
static int getHexagonIndex(int id);

int WSN_XY_Mobility::nodeId = 0;
WSN_XY_Mobility::WSN_XY_Mobility()
{
    i=0;j=0;u=0;v=0;
    r=20;
    hexagonSize=5;
    speed = 0;
    centrePos = Coord::ZERO;
}

void WSN_XY_Mobility::initialize(int stage)
{
    LineSegmentsMobilityBase::initialize(stage);
    EV << "initializing WSN_XY_Mobility stage " << stage << endl;
    if (stage == 0)
    {
        i=getHexagonLevel(nodeId);
        j=getHexagonIndex(nodeId);
        if(i==0){
            v=0;
            u=0;
        }else{
            v=j%i;
            u=j/i;
        }
        nodeId++;
        r = par("radius");
        speed = par("speed");
        hexagonSize = par("hexagonSize");
        stationary = speed == 0;
    }
    if(stage == 1){
        centrePos.x = (constraintAreaMin.x + constraintAreaMax.x)/2;
        centrePos.y = (constraintAreaMin.y + constraintAreaMax.y)/2;
        calculatePostion();
        updateVisualRepresentation();
        EV << "initial position. x = " << lastPosition.x << " y = " << lastPosition.y << " z = " << lastPosition.z << endl;
    }
}

void WSN_XY_Mobility::setTargetPosition()
{
    targetPosition = getRandomPosition();
    Coord positionDelta = targetPosition - lastPosition;
    double distance = positionDelta.length();
    nextChange = simTime() + distance / speed;
    EV << "new target set. distance=" << distance << " xpos= " << targetPosition.x << " ypos=" << targetPosition.y << " nextChange=" << nextChange;
}

void WSN_XY_Mobility::calculatePostion() {
    EV << "nodeId = " << nodeId << endl;
    if(nodeId == 0){
        lastPosition.x = centrePos.x;
        lastPosition.y = centrePos.y;
    }else{
        lastPosition.x = centrePos.x+r*(v)*cos(u*M_PI/3)+r*(i-v)*cos((u-1)*M_PI/3);
        lastPosition.y = centrePos.y+r*(v)*sin(u*M_PI/3)+r*(i-v)*sin((u-1)*M_PI/3);
    }
}
static int getHexagonLevel(int id){
    if(id == 0)
        return 0;
    else
        return (int) (sqrt((id-1)/3.0+0.25)+0.5);
}
static int getHexagonIndex(int id){
    if(id == 0)
        return 0;
    else{
        int n = getHexagonLevel(id);
        return id-3*n*(n-1)-1;
    }
}
