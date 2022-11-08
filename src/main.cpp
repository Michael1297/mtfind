#include <iostream>
#include "MtFind.h"

int main(int argc, char* argv[]) {
    try{
        MtFind mtFind(argc, argv);
        mtFind.find();
        mtFind.print();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}
