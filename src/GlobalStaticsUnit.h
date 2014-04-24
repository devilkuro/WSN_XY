/*
 * GlobalStaticsUnit.h
 *
 *  Created on: 2014Äê4ÔÂ21ÈÕ
 *      Author: Fanjing
 */

#ifndef GLOBALSTATICSUNIT_H_
#define GLOBALSTATICSUNIT_H_

#include <string>
using namespace std;
/*
 *
 */
class GlobalStaticsUnit {
public:
    GlobalStaticsUnit(int size);
    virtual ~GlobalStaticsUnit();
public:
    double getData(int index) const;
    void setData(double data, int index);
    int getSize() const;
    string toString();

private:
    int size;       // read only, it must be set at initialize phase.
    double *data;   // statics data
};

#endif /* GLOBALSTATICSUNIT_H_ */
