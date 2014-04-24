#ifndef WSN_XY_MOBILITY_H
#define WSN_XY_MOBILITY_H

#include "INETDefs.h"

#include "LineSegmentsMobilityBase.h"


/**
 * @brief Moves along a line with constant speed to a randomly chosen target.
 * When the target is reached it selects randomly a new one.
 *
 * @ingroup mobility
 * @author Steffen Sroka, Marc Loebbers, Daniel Willkomm
 */
class INET_API WSN_XY_Mobility : public LineSegmentsMobilityBase
{
  protected:
    /** @brief Speed parameter. */
    double speed;
    double r;
    double hexagonSize;

  protected:
    /** @brief Initializes mobility model parameters. */
    virtual void initialize(int stage);

    /** @brief Calculate a new target position to move to. */
    virtual void setTargetPosition();

  public:
    WSN_XY_Mobility();

  private:
    //temporary functions
    void calculatePostion();
    //private members
    int i,j,u,v;
    Coord centrePos;
    static int nodeId;

};
#endif
