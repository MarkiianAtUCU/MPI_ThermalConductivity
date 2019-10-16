//
// Created by markiian on 16.10.19.
//

#ifndef MPI_MPITABLE_H
#define MPI_MPITABLE_H

#include <vector>

class MpiTable {
private:
    std::vector<double> data0;
    std::vector<double > data1;

    std::vector<double > * from;
    std::vector<double> * to;

    std::vector<double> neighbourTop;
    std::vector<double> neighbourBottom;

public:
    MpiTable(int width, int height, std::vector<double> & data);

    int width;
    int height;

    double & get(int x, int y);
    void set(int x, int y, double & el);

    void setNeighbourTop(std::vector<double> & data);
    void setNeighbourBottom(std::vector<double> & data);
    void flip();
//    float process(int x, int y, (*float)(std::vector<float>));

    std::vector<double> getTop();
    std::vector<double> getBottom();

};

#endif //MPI_MPITABLE_H
