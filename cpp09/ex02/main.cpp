#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <cstddef>

bool parseInput(int argc, char **argv, std::vector<int> &vec, std::deque<int> &deq)
{
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (arg.empty() || arg.find_first_not_of("0123456789") != std::string::npos)
        {
            std::cerr << "Error: Invalid argument: " << arg << std::endl;
            return false;
        }

        int value = std::atoi(arg.c_str());
        vec.push_back(value);
        deq.push_back(value);
    }
    return true;
}

template <typename Container>
void printContainer(const Container &c)
{
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <numbers>" << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::deque<int> deq;

    if (!parseInput(argc, argv, vec, deq))
        return 1;

    std::cout << "Before: ";
    printContainer(vec);

    MergeInsertionSort sorter;

    clock_t startVec = clock();
    std::vector<int> sortedVec = sorter.mergeInsertionSort(vec);
    clock_t endVec = clock();

    clock_t startDeq = clock();
    std::deque<int> sortedDeq = sorter.sortDeque(deq);
    clock_t endDeq = clock();

    std::cout << "After:  ";
    printContainer(sortedVec);

    double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000;
    double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque  : " << timeDeq << " us" << std::endl;

    return 0;
}
