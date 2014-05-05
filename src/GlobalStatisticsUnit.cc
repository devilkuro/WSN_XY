/*
 * GlobalStaticsUnit.cc
 *
 *  Created on: 1405051354
 *      Author: Fanjing
 */

#include "GlobalStatisticsUnit.h"
#include <sstream>
#include <iostream>

GlobalStatisticsUnit::GlobalStatisticsUnit(int size) {
    // TODO Auto-generated constructor stub
    this->size = size;
    data = new double[size];
    std::cout << "getAddr:"  << this->data << std::endl;
}

GlobalStatisticsUnit::~GlobalStatisticsUnit() {
    // TODO Auto-generated destructor stub

    std::cout << "delAddr:"  << this->data << std::endl;
    size = 0;
    delete(data);
    data = NULL;
}

double GlobalStatisticsUnit::getData(int index) const {
    if(index<0||index>=size)
        return -1;
    return data[index];
}

void GlobalStatisticsUnit::setData(double data, int index) {
    if (index >= 0 && index < size) {
        std::cout << "setData:" << index << "," << data << std::endl;
        this->data[index] = data;
        std::cout << "getData:" << index << "," << this->data[index] << std::endl;

    }
}


int GlobalStatisticsUnit::getSize() const {
    return size;
}

string GlobalStatisticsUnit::toString() {
    stringstream ss;
    std::cout << "getAddr:" << this->data << std::endl;
    for(int i = 0;i<size;i++){
        std::cout<< "data["<<i<<"]:"<< data[i]<<std::endl;
    }
    for(int i = 0;i<size;i++){
        if(i!=0)
            ss<<",";
        ss<<(double)data[i];
    }
    std::cout<< "toString:"<< ss.str()<<std::endl;
    return ss.str();
}
