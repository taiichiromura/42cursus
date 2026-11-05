#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <list>

enum RPNError
{
    RPN_OK,
    RPN_BAD_TOKEN,
    RPN_DIV_BY_ZERO,
    RPN_INSUFFICIENT_VALUES,
    RPN_BAD_EXPRESSION
};

class RPN {
  private:
    std::stack<int, std::list<int> > _stack;

	bool isOperator(const std::string &token) const;
	int applyOperator(int a, int b, const std::string &op, int &result) const;
  public:
    RPN();
    RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

    RPNError evaluate(const std::string &expression, int &result);
};

#endif
