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

#ifndef WSN_XY_CONNECTIONMANAGER_H_
#define WSN_XY_CONNECTIONMANAGER_H_

#include <ConnectionManager.h>

class WSN_XY_ConnectionManager: public ConnectionManager {
public:
    WSN_XY_ConnectionManager();
    virtual ~WSN_XY_ConnectionManager();

public:
    double calcInterfDist();
};

#endif /* WSN_XY_CONNECTIONMANAGER_H_ */
