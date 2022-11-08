#pragma once
#include <string>
#include <list>
#include <mutex>

struct Result{
    unsigned long long line_number, position;
    std::string entry;
};

class MtFind{
    std::mutex mutex;
    std::string link, mask;
    std::list<Result> search_results;
    void find_match(const std::string& str, unsigned long long line_number); //поиск совпадений с маской

public:
    MtFind(int argc, char** argv);
    void find();    //поиск по файлу
    void print();   //вывод результатов
};