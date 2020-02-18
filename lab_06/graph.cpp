#include <cstdlib>
#include <iostream>
#include "graph.hpp"

template <typename T>
void Graph<T>::randomize()
{
    for (size_t i = 0; i < size; i++)
    {
        std::vector<T> line;
        for (size_t j = 0; j < size; j++)
            line.push_back((i == j) ? 0 : (rand() % 9 + 1));
        graph.push_back(line);
    }
}

template <typename T>
void Graph<T>::show()
{
    if (graph.size() == 0)
    {
        std::cout << "This graph is empty.\n" << std::endl;
        return;
    }

    std::cout << std::endl;
    for (auto &line : graph)
    {
        for (auto &elem : line)
            std::cout << elem << " ";
        std::cout <<std::endl;
    }
    std::cout << std::endl;
}