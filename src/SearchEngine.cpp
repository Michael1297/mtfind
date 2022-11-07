#include "SearchEngine.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Exception.h"
#include "ThreadPool.h"

SearchEngine::SearchEngine(int argc, char** argv){
    switch (argc) {
        case 1: throw Exception("Missing link and mask");
        case 2: throw Exception("Missing mask");
        default:
            link = argv[1];
            mask = argv[2];
    }
}

void SearchEngine::search_word(const std::string& str, int count_str) {
    for(unsigned long long pos = 0; pos + mask.length() < str.length(); pos++){
        bool match = true;
        for(int i = 0; i < mask.length(); i++){
            if(mask[i] == '?') continue;
            else if(mask[i] != str[i + pos]){
                match = false;
                break;
            }
        }
        if(match){
            mutex.lock();
            search_results.push_back({count_str, pos + 1, str.substr(pos, mask.length())});
            mutex.unlock();
            pos += mask.length() - 1;
        }
    }
}

void SearchEngine::search() {
    std::ifstream file(link);
    if(!file.is_open()) throw Exception("Invalid file link ");
    int count_str = 0;
    ThreadPool pool(std::thread::hardware_concurrency());
    while (!file.eof()){
        std::string str;
        std::getline(file, str);
        pool.enqueue(&SearchEngine::search_word, this, str, ++count_str);
    }
    file.close();
}

void SearchEngine::print() {
    std::cout << search_results.size() << "\n";
    std::sort(search_results.begin(), search_results.end(), [](Result& result1, Result& result2){
        return result1.count_str < result2.count_str
                || result1.count_str == result2.count_str && result1.position < result2.position;
    });

    for(auto& result : search_results){
        std::cout << result.count_str << " " << result.position << " " << result.entry << std::endl;
    }
}