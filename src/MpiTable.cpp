//
// Created by markiian on 16.10.19.
//

#include "../includes/MpiTable.h"

std::vector<float> MpiTable::getBottom() {
    return nullptr;
}

std::vector<float> MpiTable::getTop() {
    return std::vector<float>();
}

double MpiTable::at(int x, int y) {
    return 0;
}

MpiTable::MpiTable(int width, int height, std::vector<float> & data) : width(width), height(height) {
    data0 = std::move(data);
    currentData = &data0;
}

