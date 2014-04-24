//***************************************************************************
// * file:        ConstSpeedMobility.cc
// *
// * author:      Steffen Sroka
// *
// * copyright:   (C) 2004 Telecommunication Networks Group (TKN) at
// *              Technische Universitaet Berlin, Germany.
// *
// *              This program is free software; you can redistribute it
// *              and/or modify it under the terms of the GNU General Public
// *              License as published by the Free Software Foundation; either
// *              version 2 of the License, or (at your option) any later
// *              version.
// *              For further information see file COPYING
// *              in the top level directory
// ***************************************************************************
// * part of:     framework implementation developed by tkn
// **************************************************************************/

package wsn_xy.mobility;

import inet.mobility.models.MovingMobilityBase;


//
// Controls all movement related things of a host
//
// ~ConstSpeedMobility does not use one of the standard mobility approaches.
// The user can define a velocity for each Host and an update interval. If
// the velocity is greater than zero (i.e. the Host is not stationary) the
// ~ConstSpeedMobility module calculates a random target position for the Host.
// Every update interval ~ConstSpeedMobility calculates the new position on its
// way to the target position and updates the display. Once the target position
// is reached ~ConstSpeedMobility calculates a new target position.
//
// This component has been taken over from Mobility Framework 1.0a5.
//
// @author Steffen Sroka, Marc Loebbers, Daniel Willkomm
//
simple WSN_XY_Mobility extends MovingMobilityBase
{
    parameters:
        double speed @unit(mps) = default(0); // speed of the host
        double initialX @unit(m) = default(uniform(constraintAreaMinX, constraintAreaMaxX));
        double initialY @unit(m) = default(uniform(constraintAreaMinY, constraintAreaMaxY));
        double initialZ @unit(m) = default(uniform(constraintAreaMinZ, constraintAreaMaxZ));
        bool initFromDisplayString = default(true);
        int hexagonSize = default(5); // the size of the hexagon
        double radius @unit(m) = default(20m); // the raidus of each hexagon
        @class(WSN_XY_Mobility);
}
