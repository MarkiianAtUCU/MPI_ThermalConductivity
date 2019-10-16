//
// Created by markiian on 16.10.19.
//

#include <cmath>
#include <iostream>
#include "MpiTable.h"
double * MpiTable::getBottom() {
    return &(*from)[(width+2) * height + 1];
}

double * MpiTable::getTop() {
    return &(*from)[width + 3];
}

double MpiTable::get(int x, int y) {
    if (!(x > -1 && x < width && y > -1 && y < height)) throw;
    return (*from)[ (y+1) * (width+2) + x+1];
}

void MpiTable::set(int x, int y, double el) {
    if (!(x > -1 && x < width && y > -1 && y < height)) throw;
    (*to)[ (y+1) * (width+2) + x+1] = el;
}


MpiTable::MpiTable(int width, int height, std::vector<double> & data) : width(width), height(height), data0((width+2)*(height+2)), data1((width+2)*(height+2)) {
    data0 = std::move(data);
    from = &data0;
    to = &data1;
}

void MpiTable::flip() {
    std::swap(from, to);
}
