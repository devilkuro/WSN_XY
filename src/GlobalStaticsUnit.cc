/*
 * GlobalStaticsUnit.cpp
 *
 *  Created on: 2014Äê4ÔÂ21ÈÕ
 *      Author: Fanjing
 */

#include <GlobalStaticsUnit.h>
#include <sstream>

GlobalStaticsUnit::GlobalStaticsUnit(int size) {
    // TODO Auto-generated constructor stub
    this->size = size;
    data = new double[size];
}

GlobalStaticsUnit::~GlobalStaticsUnit() {
    // TODO Auto-generated destructor stub
    size = 0;
    delete(data);
    data = NULL;
}

double GlobalStaticsUnit::getData(int index) const {
    if(index<0||index>=size)
        return -1;
    return data[index];
}

void GlobalStaticsUnit::setData(double data, int index) {
    if(index>=0&&index<size)
    this->data[index] = data;
}


int GlobalStaticsUnit::getSize() const {
    return size;
}

string GlobalStaticsUnit::toString() {
    stringstream ss;

    for(int i = 0;i<size;i++){
        if(i!=0)
            ss<<",";
        ss<<data[i];
    }
    return ss.str();
}
