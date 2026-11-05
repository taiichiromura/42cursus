#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include "PmergeMe.hpp"

MergeInsertionSort::MergeInsertionSort() {}
MergeInsertionSort::MergeInsertionSort(const MergeInsertionSort &other) { (void)other; }
MergeInsertionSort &MergeInsertionSort::operator=(const MergeInsertionSort &other)
{
    (void)other;
    return *this;
}
MergeInsertionSort::~MergeInsertionSort() {}

std::vector<long> MergeInsertionSort::generateJacobsthalSequence(size_t limit) {
  std::vector<long>	jacobsthal;
  jacobsthal.push_back(0);
  jacobsthal.push_back(1);
  while(jacobsthal.back() < static_cast<long>(limit)) {
    jacobsthal.push_back(jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2]);
  }
  return jacobsthal;
}

std::vector<std::pair<int, int> > MergeInsertionSort::makePairs(std::vector<int> &values, bool &hasStray, int &stray) {
  hasStray = values.size() % 2 != 0;
  stray = hasStray ? values.back() : 0;
  if (hasStray)
    values.pop_back();

  std::vector<std::pair<int, int> > pairs;
  for (size_t i = 0; i < values.size(); i += 2)
	pairs.push_back(values[i] < values[i + 1] ? std::make_pair(values[i], values[i + 1]) : std::make_pair(values[i + 1], values[i]));
  return pairs;
}

void MergeInsertionSort::buildMainAndPend(const std::vector<std::pair<int, int> > &pairs, std::vector<int> &main, std::vector<int> &pend, std::vector<int> &largeInMain)
{
    std::vector<int> larges;
    for (size_t i = 0; i < pairs.size(); i++)
        larges.push_back(pairs[i].second);

    std::vector<int> sortedLarges = mergeInsertionSort(larges);

    std::vector<bool> used(pairs.size(), false);
    std::vector<int> sortedIdx;
    for (size_t i = 0; i < sortedLarges.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].second == sortedLarges[i])
            {
                used[j] = true;
                sortedIdx.push_back(static_cast<int>(j));
                break;
            }
        }
    }

    main = sortedLarges;
    largeInMain = sortedLarges;

    pend.clear();
    for (size_t i = 0; i < sortedIdx.size(); i++)
        pend.push_back(pairs[sortedIdx[i]].first);

    if (!pend.empty())
        main.insert(main.begin(), pend[0]);
}

void MergeInsertionSort::insertPendByJacobsthal(std::vector<int> &main, const std::vector<int> &pend, const std::vector<int> &largeInMain) {
  if (pend.size() < 2)
    return ;
  std::vector<long> jacobsthal = generateJacobsthalSequence(pend.size());
  size_t prev = 1;

  for (size_t i = 2; prev < pend.size(); i++) {
	size_t bound = std::min(static_cast<size_t>(jacobsthal[i]), pend.size());
	for (size_t b = bound; b > prev; b--) {
	  size_t idx = b - 1;
	  std::vector<int>::iterator posA = std::find(main.begin(), main.end(), largeInMain[idx]);
	  main.insert(std::lower_bound(main.begin(), posA, pend[idx]), pend[idx]);
	}
	prev = bound;
  }
}

std::vector<int> MergeInsertionSort::mergeInsertionSort(std::vector<int> values) {
  if (values.size() < 2)
    return values;

  bool hasStray;
  int stray;
  std::vector<std::pair<int, int> > pairs = makePairs(values, hasStray, stray);
  std::vector<int> main, pend, largeInMain;
  buildMainAndPend(pairs, main, pend, largeInMain);
  insertPendByJacobsthal(main, pend, largeInMain);

  if (hasStray)
    main.insert(std::lower_bound(main.begin(), main.end(), stray), stray);
  return main;
}

std::deque<int> MergeInsertionSort::sortDeque(const std::deque<int> &deq)
{
    std::vector<int> tmp(deq.begin(), deq.end());
    tmp = mergeInsertionSort(tmp);
    return std::deque<int>(tmp.begin(), tmp.end());
}
