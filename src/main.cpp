#include <iostream>
#include <ConfigReader.h>
#include "MpiTable.h"
#include "MpiManager.h"
#include "openmpi/mpi.h"

int main() {


//    ConfigReader c("../config.data");
//    int numThreads = c.get_int("num_threads");
//    int height = c.get_int("height");
//    int width = c.get_int("width");
//    MpiManager manager(numThreads,
//                       height,
//                       width,
//                       "test");
//
//    std::vector<double> table((height + 2)*(width + 2));
//    c.getTable(table);
//
//    for (int i = 0; i < numThreads; ++i) {
//        manager.splitData(i, table);
//    }
//



//    std::vector<double> top { 0,   1,   2,   3,   4,  5};
//    std::vector<double> vect{-1,  10,  20,  30,  40, -1,
//                             -1,  50,  60,  70,  80, -1,
//                             -1,  90, 100, 110, 120, -1,
//                             -1, 130, 140, 150, 160, -1,
//                             -1, 170, 180, 190, 200, -1};
//    std::vector<double> bot { -2,  -3,  -4, -5,  -6, -7};
//
//    auto a = MpiTable(4,5, vect);
//    a.setNeighbourTop(top);
//    a.setNeighbourBottom(bot);
//
//    c.getTable(table);

//
//    for (int i = 0; i < table.size(); ++i) {
//        std::cout << table[i] << std::endl;
//    }

//    std::cout << table.size() << std::endl;
//
//    std::vector<double> tt = a.getTop();
//    std::vector<double> tb = a.getBottom();
//    double x = 3.5;
//    a.set(1, 5, x);
//    a.flip();
//
//    tt = a.getTop();
//    tb = a.getBottom();
//
//    std::cout << a.get(1, 5) << std::endl;
}