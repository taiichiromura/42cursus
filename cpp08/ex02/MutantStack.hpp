#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
 private:
 public:
  MutantStack() {};
  MutantStack(const MutantStack<T>& other) : std::stack<T>(other) {}
  MutantStack<T>& operator=(const MutantStack<T>& other) {
    if (this != &other) {
      std::stack<T>::operator=(other);
    }
    return *this;
  }
  ~MutantStack() {};

  typedef typename std::stack<T>::container_type::iterator it;

  it begin() { return this->c.begin(); }
  it end() { return this->c.end(); }
};

#endif
