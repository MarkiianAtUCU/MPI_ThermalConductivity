#include <iostream>
#include "MpiTable.h"

int main() {
    std::vector<double> vect{-1, -1,  -1,  -1,  -1, -1,
                             -1, 10,  20,  30,  40, -1,
                             -1, 50,  60,  70,  80, -1,
                             -1, 90, 100, 110, 120, -1,
                             -1, 130, 140, 150, 160, -1,
                             -1, 170, 180, 190, 200, -1,
                             -1, -1,  -1,  -1,  -1, -1};

    auto a = MpiTable(4,5, vect);

    std::cout << a.get(3, 2) << std::endl;
    a.set(3, 2, 3.5);
    a.flip();
    std::cout << a.get(3, 2) << std::endl;
    std::cout << a.getTop()[0] << std::endl;
    std::cout << a.getBottom()[0] << std::endl;
}