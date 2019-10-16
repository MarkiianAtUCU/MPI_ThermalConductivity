//
// Created by markiian on 16.10.19.
//

#include <iostream>
#include "MpiManager.h"
MpiManager::MpiManager(int nThreads, int tableHeight, int tableWidth, const std::string &outFolder) : nThreads(
        nThreads), tableHeight(tableHeight), tableWidth(tableWidth), outFolder(outFolder), tableParts(nThreads) {
}
void MpiManager::splitData(int index, std::vector<double> & table) {
    int elementHeight = tableHeight / nThreads;
    std::vector<double> element;
    int real_width = tableWidth + 2;

    MpiTable res;
    if (index == nThreads - 1) {
        element = std::vector<double>(table.begin() + real_width * (elementHeight*index + 1),
                                      table.end() - real_width);
        res = MpiTable(tableWidth, tableHeight - elementHeight * index  , element);

        auto top = std::vector<double>(table.begin() + real_width * (elementHeight*index), table.begin() + real_width * (elementHeight*index + 1));
        res.setNeighbourTop(top);

        auto bottom = std::vector<double>(table.end() - real_width, table.end());
        res.setNeighbourBottom(bottom);
    } else {
        element = std::vector<double>(table.begin() + real_width * (elementHeight*index + 1),
                                      table.begin() + real_width * (elementHeight*(index + 1)+1));
        res = MpiTable(tableWidth, elementHeight, element);

        auto top = std::vector<double>(table.begin() + real_width * (elementHeight*index), table.begin() + real_width * (elementHeight*index + 1));
        res.setNeighbourTop(top);
        auto bottom = std::vector<double>(table.begin() + real_width * (elementHeight*(index + 1)+1), table.begin() + real_width * (elementHeight*(index + 1)+2));
        res.setNeighbourBottom(bottom);
    }
    tableParts.push_back(res);
}
