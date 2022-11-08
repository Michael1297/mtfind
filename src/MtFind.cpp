#include "MtFind.h"
#include <fstream>
#include <iostream>
#include "Exception.h"
#include "ThreadPool.h"

MtFind::MtFind(int argc, char** argv){
    switch (argc) {
        case 1: throw Exception("Missing link and mask");
        case 2: throw Exception("Missing mask");
        default:
            link = argv[1];
            mask = argv[2];
    }
}

void MtFind::find_match(const std::string& str, unsigned long long line_number) {
    for(unsigned long long pos = 0; pos + mask.length() < str.length(); pos++){
        bool match = true;
        for(int i = 0; i < mask.length(); i++){
            if(mask[i] == '?') continue;    //любой символ
            else if(mask[i] != str[i + pos]){
                match = false;
                break;
            }
        }
        if(match){  //найдено совпадение с маской
            mutex.lock();
            search_results.push_back({line_number + 1, pos + 1, str.substr(pos, mask.length())});
            mutex.unlock();
            pos += mask.length() - 1;
        }
    }
}

void MtFind::find() {
    std::ifstream file(link);
    if(!file.is_open()) throw Exception("Invalid file link ");
    unsigned long long line_number = 0;
    ThreadPool pool(std::thread::hardware_concurrency());
    //чтение файла
    while (!file.eof()){
        std::string str;
        std::getline(file, str);
        pool.enqueue(&MtFind::find_match, this, str, line_number++);
    }
    file.close();
}

void MtFind::print() {
    std::cout << search_results.size() << "\n";
    //отсортировать по номеру строки
    search_results.sort([](Result& result1, Result& result2){
        return result1.line_number < result2.line_number
               || result1.line_number == result2.line_number && result1.position < result2.position;
    });

    for(auto& result : search_results){
        std::cout << result.line_number << " " << result.position << " " << result.entry << std::endl;
    }
}