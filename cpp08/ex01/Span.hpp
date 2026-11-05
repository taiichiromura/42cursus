#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>


class Span {
 private:
  unsigned int _max_size;
  std::vector<int> _nums;

 public:
  Span(unsigned int n);
  Span(const Span& other);
  Span& operator=(const Span& other);
  ~Span();
  void addNumber(const int n);
  unsigned int shortestSpan();
  unsigned int longestSpan();
  template <typename InputIterator>
  void addRange(InputIterator first, InputIterator last) {
    if (this->_nums.size() + static_cast<size_t>(std::distance(first, last)) > this->_max_size)
      throw std::out_of_range("span is full!");
    this->_nums.insert(this->_nums.end(), first, last);
  }
  std::vector<int> getNums() const;
};
