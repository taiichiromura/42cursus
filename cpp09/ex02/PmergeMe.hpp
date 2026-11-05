#ifndef MERGE_INSERTION_SORT_HPP
#define MERGE_INSERTION_SORT_HPP

#include <vector>
#include <deque>
#include <cstddef>

class MergeInsertionSort
{
public:
    MergeInsertionSort();
    MergeInsertionSort(const MergeInsertionSort &other);
    MergeInsertionSort &operator=(const MergeInsertionSort &other);
    ~MergeInsertionSort();

    std::vector<int> mergeInsertionSort(std::vector<int> values);
    std::deque<int> sortDeque(const std::deque<int> &deq);

private:
    std::vector<long> generateJacobsthalSequence(size_t limit);
    std::vector<std::pair<int, int> > makePairs(std::vector<int> &values, bool &hasStray, int &stray);
    void buildMainAndPend(const std::vector<std::pair<int, int> > &pairs, std::vector<int> &main, std::vector<int> &pend, std::vector<int> &largeInMain);
    void insertPendByJacobsthal(std::vector<int> &main, const std::vector<int> &pend, const std::vector<int> &largeInMain);
};

#endif
