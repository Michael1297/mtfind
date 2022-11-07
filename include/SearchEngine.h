#pragma once
#include <string>
#include <vector>
#include <mutex>

struct Result{
    int count_str;
    unsigned long long position;
    std::string entry;
};

class SearchEngine{
    std::mutex mutex;
    std::string link, mask;
    std::vector<Result> search_results;
    void search_word(const std::string& str, int count_str);

public:
    SearchEngine(int argc, char* argv[]);
    void search();
    void print();
};