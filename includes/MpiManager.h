//
// Created by markiian on 16.10.19.
//

#ifndef MPI_MPIMANAGER_H
#define MPI_MPIMANAGER_H

#include <string>
#include "MpiTable.h"

class MpiManager {
private:
    int nThreads;
    int tableHeight, tableWidth;
    std::string outFolder;
    std::vector<MpiTable> tableParts;

public:
    MpiManager(int nThreads, int tableHeight, int tableWidth, const std::string &outFolder);
    void splitData(int index, std::vector<double> & table);
};



#endif //MPI_MPIMANAGER_H
