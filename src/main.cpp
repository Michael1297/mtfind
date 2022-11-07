#include <iostream>
#include "SearchEngine.h"

int main(int argc, char* argv[]) {
    try{
        SearchEngine searchEngine(argc, argv);
        searchEngine.search();
        searchEngine.print();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}
