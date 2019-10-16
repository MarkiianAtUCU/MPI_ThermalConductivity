//
// Created by markiian on 16.10.19.
//

#ifndef MPI_MPITABLE_H
#define MPI_MPITABLE_H

#include <vector>

class MpiTable {
private:
    std::vector<float> data0;
    std::vector<float> data1;

    std::vector<float> * currentData;

    std::vector<float> neighbourTop;
    std::vector<float> neighbourBottom;

public:
    MpiTable(int width, int height, std::vector<float> & data);

    int width;
    int height;
    double at(int x, int y);
    float process(int x, int y, (*float)(std::vector<float>));

    std::vector<float> getTop();
    std::vector<float> getBottom();

};

#endif //MPI_MPITABLE_H
