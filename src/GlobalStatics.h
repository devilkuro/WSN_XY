/*
 * GlobalStatics.h
 *
 *  Created on: 2014��4��21��
 *      Author: Fanjing
 */

#ifndef GLOBALSTATICS_H_
#define GLOBALSTATICS_H_

#include<map>
#include<list>
#include<string>
#include<stdarg.h>

#include"GlobalStaticsUnit.h"
/*
 *
 */
typedef std::list<GlobalStaticsUnit> GlobalStaticsList;
typedef std::map<string,GlobalStaticsList> GlobalStaticsMap;
class GlobalStatics {
public:
    GlobalStatics();
    virtual ~GlobalStatics();

public:
    void record(string name, int size, ...);
    void output(string name);
private:
     GlobalStaticsMap globalStaticsMap;

};

#endif /* GLOBALSTATICS_H_ */
