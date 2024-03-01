#include <iostream>
#include "findByName.hpp"

#define MAX_TREADS 8

FindByName::FindByName(const std::string &filename) : filename(filename) {};

void searchInDir(const fs::path &searchPath, const std::string &filename, std::shared_ptr<ThreadPool> t)
{
    try
    {
        for (const auto &entry : fs::recursive_directory_iterator(searchPath))
        {
            if (fs::is_regular_file(entry) && entry.path().filename() == filename)
            {
                std::cout << "file:  " << entry.path().filename() << " was found in " << entry.path() << std::endl;
                t->stopped();
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error - " << e.what() << '\n';
    }
}

void FindByName::search()
{
    fs::path path = fs::path("/");
    int directoryCount = std::count_if(
            fs::directory_iterator(path),
            fs::directory_iterator(),
            [](const fs::directory_entry &entry)
            {
                return fs::is_directory(entry.status());
            });

    (directoryCount > MAX_TREADS) ? t = std::make_shared<ThreadPool>(MAX_TREADS) : t = std::make_shared<ThreadPool>(directoryCount);
    for (const auto &dir : fs::directory_iterator(path))
    {
        auto paths = dir.path();
        t->enqueue([paths, this]()
                   { searchInDir(paths, filename, t); });
    }
}