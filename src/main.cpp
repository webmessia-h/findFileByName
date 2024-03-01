#include "findByName.hpp"
#include "search.h"

int main() {
    // hardcoded filename
    FindByName file("findMe.txt");
    // Call search function
    file.search();
    return 0;
}
