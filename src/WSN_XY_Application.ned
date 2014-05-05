//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package wsn_xy;


import org.mixim.base.modules.IBaseApplLayer;


simple WSN_XY_Application like IBaseApplLayer
{
    parameters:
        @class(WSN_XY_Application);
        bool coreDebug = default(false); //debug switch for base class (TestApplLayer)
    	bool debug      = default(false); // debug switch
    	int headerLength @unit("bit"); // length of the application message header (in bits)
    	double initialRelayEnergy @unit("J") = default(82J);
    	double deadRelayEnergy @unit("J") = default(0J);
    	double initialSensorEnergy @unit("J") = default(50J);
    	double deadSensorEnergy @unit("J") = default(0J);
    	double sensorInterval @unit("s") = default(30s);
    	double terminateDelay @unit("s") = default(15s);
    	int statisticsInterval = default(1);
    gates:
    	input lowerLayerIn; // from network layer
        output lowerLayerOut; // to network layer
        input lowerControlIn; // control from network layer
        output lowerControlOut; // control to network layer
}
