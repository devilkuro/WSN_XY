/*
 * GlobalStatics.cpp
 *
 *  Created on: 2014Äê4ÔÂ21ÈÕ
 *      Author: Fanjing
 */

#include <GlobalStatics.h>
#include <fstream>

GlobalStatics::GlobalStatics() {
    // TODO Auto-generated constructor stub
}

GlobalStatics::~GlobalStatics() {
    // TODO Auto-generated destructor stub
}

void GlobalStatics::record(string name, int size, ...) {
    // TODO Auto-generated destructor stub
    GlobalStaticsMap::iterator it;
    GlobalStaticsUnit unit = GlobalStaticsUnit(size);
    double val;
    va_list vl;
    va_start(vl,size);
    for(int i = 0; i<size; i++){
        val = va_arg(vl,double);
        unit.setData(val,i);
    }
    va_end(vl);
    it = globalStaticsMap.find(name);
    if(it==globalStaticsMap.end()){
        GlobalStaticsList list;
        globalStaticsMap.insert(std::pair<string,GlobalStaticsList>(name,list));
    }
    globalStaticsMap[name].push_back(unit);
}

void GlobalStatics::output(string name) {
    std::fstream fs;
    fs.open (name.c_str(),std::fstream::out);
    for(GlobalStaticsMap::iterator it = globalStaticsMap.begin();it!=globalStaticsMap.end();it++){
        fs<<it->first<<std::endl;
        for(GlobalStaticsList::iterator lit = it->second.begin();lit!=it->second.end();lit++){
            fs<<lit->toString()<<std::endl;
        }
    }
    fs.close();
}
