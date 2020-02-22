#include <cstdlib>
#include <iostream>
#include <chrono>

#include "conveyor.hpp"

int main(int argc, const char * argv[])
{
    srand(time(NULL));

    if (argc == 2 && std::string(argv[1]) == "-memcheck")
    {
        int obj_count = 10;
        Conveyor conveyor(obj_count, 3, 5);
        conveyor.execute_parallel();
        conveyor.execute_linear();
        return 0;
    }

    int obj_count = 0;
    std::cin >> obj_count;
    if (obj_count < 2)
        return -1;

    Conveyor conveyor(obj_count, 3, 5);

    auto start = std::chrono::steady_clock::now();
    conveyor.execute_parallel();
    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
    cout << "Parallel: " << duration.count() << " msec" <<  endl;
    
    start = std::chrono::steady_clock::now();
    conveyor.execute_linear();
    end = std::chrono::steady_clock::now();
    
    duration = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
    cout << "Linear: " << duration.count() << " msec" <<  endl;
    
    return 0;
}
