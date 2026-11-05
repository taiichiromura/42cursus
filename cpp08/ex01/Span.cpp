#include "Span.hpp"

Span::Span(unsigned int n) : _max_size(n) {}
Span::Span(const Span& other) { *this = other; }
Span& Span::operator=(const Span& other) {
  this->_max_size = other._max_size;
  this->_nums = other._nums;
  return *this;
}
Span::~Span() {}

void Span::addNumber(const int n) {
  if (this->_nums.size() >= this->_max_size)
    throw std::out_of_range("span is full!");
  this->_nums.push_back(n);
}

unsigned int Span::shortestSpan() {
  if (this->_nums.size() <= 1) {
    throw std::logic_error("not enough element");
  }
  std::sort(this->_nums.begin(), this->_nums.end());
  long shortestspan =
      static_cast<long>(this->_nums[1]) - static_cast<long>(this->_nums[0]);
  for (unsigned int i = 1; i < this->_nums.size() - 1; i++) {
    long nowspan = static_cast<long>(this->_nums[i + 1]) -
                   static_cast<long>(this->_nums[i]);
    if (nowspan < shortestspan) shortestspan = nowspan;
  }
  return static_cast<unsigned int>(shortestspan);
}

unsigned int Span::longestSpan() {
  if (this->_nums.size() <= 1) {
    throw std::logic_error("not enough element");
  }
  std::sort(this->_nums.begin(), this->_nums.end());
  long diff = static_cast<long>(this->_nums.back()) -
              static_cast<long>(this->_nums.front());
  return static_cast<unsigned int>(diff);
}

std::vector<int> Span::getNums() const { return this->_nums; }
