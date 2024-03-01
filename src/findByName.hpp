#pragma once

#include <string>
#include <filesystem>
#include "ThreadPool.hpp"

namespace fs = std::filesystem;

class FindByName
{
public:
    FindByName(const std::string &filename);
    void search();
    std::string filename;
    std::shared_ptr<ThreadPool> t;
};
