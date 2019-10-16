#include <iostream>
#include <config_reader.h>
#include "MpiTable.h"

int main() {
    config *c = new config("../config.data");
    std::vector<double> table(20);

    c->get_table(table);

    for (int i = 0; i < table.size(); ++i) {
        std::cout << table[i] << std::endl;
    }
}