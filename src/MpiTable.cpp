//
// Created by markiian on 16.10.19.
//

#include <cmath>
#include <iostream>
#include "MpiTable.h"

std::vector<double> MpiTable::getBottom() {
    return std::vector<double>((*from).end() - (width + 2), (*from).end());

}

std::vector<double> MpiTable::getTop() {
    return std::vector<double >((*from).begin(), (*from).begin() + width + 2);
}

double & MpiTable::get(int x, int y) {
    if (y == 0) {
        return neighbourTop.at(x);
    } else if (y == height + 1) {
        return neighbourBottom.at(x);
    } else if (x >= 0 && x <= width+1 && y>0 && y<=height) {
        return (*from).at((y-1)*(width+2) + x);
    }
    throw;
}

void MpiTable::set(int x, int y, double & el) {
    if (!(x > 0 && x <= width && y > 0 && y <= height)) throw;
    (*to).at((y-1) * (width+2) + x) = el;
}


MpiTable::MpiTable(int width, int height, std::vector<double> & data) : width(width), height(height),
data0((width+2)*(height+2)), data1((width+2)*height), neighbourTop (width + 2), neighbourBottom(width + 2){
    data0 = std::move(data);
    from = &data0;
    to = &data1;
}

void MpiTable::flip() {
    std::swap(from, to);
}

void MpiTable::setNeighbourTop(std::vector<double> &data) {
    neighbourTop = std::move(data);
}

void MpiTable::setNeighbourBottom(std::vector<double> &data) {
    neighbourBottom = std::move(data);
}
