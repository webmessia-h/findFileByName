#include <iostream>
#include "findByName.hpp"

#define MAX_TREADS 8    // pretty self-explanatory

FindByName::FindByName(const std::string &filename) : filename(filename) {}; 

void searchInDir(const fs::path &searchPath, const std::string &filename, std::shared_ptr<ThreadPool> t) 
{
    try
    {
        for (const auto &entry : fs::recursive_directory_iterator(searchPath))    // for every directory starting from "/"
        {
            if (fs::is_regular_file(entry) && entry.path().filename() == filename)    // if the file was found
            {
                std::cout << "file:  " << entry.path().filename() << " was found in " << entry.path() << std::endl;    // print it's name and location, as asked
                t->stopped();    // stop thread pool
            }
        }
    }
    catch (const std::exception &e)    // catch and wrap any errors
    {
        std::cerr << "Error - " << e.what() << std::endl;
    }
}

void FindByName::search()
{
    fs::path path = fs::path("/");    // path to start search from, adjustable, better use "/home/username" for safety reasons 
    
    // count directories in current location
    int directoryCount = std::count_if(   
            fs::directory_iterator(path),
            fs::directory_iterator(),
            [](const fs::directory_entry &entry)
            {
                return fs::is_directory(entry.status());
            });

    // if amount of directories then create maximum amount of threads (adjustable), else create corresponding amount of threads
    (directoryCount > MAX_TREADS) ? t = std::make_shared<ThreadPool>(MAX_TREADS) : t = std::make_shared<ThreadPool>(directoryCount);

    // for every directory enque task of searching for file in it
    for (const auto &dir : fs::directory_iterator(path))
    {
        auto paths = dir.path();
        t->enqueue([paths, this]()
                   { searchInDir(paths, filename, t); });
    }
}
