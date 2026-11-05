#include "RPN.hpp"

RPN::RPN(){}
RPN::RPN(const RPN &other) : _stack(other._stack){}
RPN &RPN::operator=(const RPN &other) {
  if (this != &other) {
    this->_stack = other._stack;
  }
  return *this;
}
RPN::~RPN(){}


bool RPN::isOperator(const std::string &token) const {
  return (token == "+"	|| token == "-"	|| token == "*"	|| token == "/");
}

int RPN::applyOperator(int a, int b, const std::string &op, int &result) const {
  if (op == "+") {
	result = a + b;
	return true;
  }
  if (op == "-") {
	result = a - b;
	return true;
  }
  if (op == "*") {
	result = a * b;
	return true;
  }
  if (op == "/") {
	if (b == 0)
	  return false;
	result = a / b;
	return true;
  }
  return false;
}

RPNError RPN::evaluate(const std::string &expression, int &result) {
  std::stringstream ss(expression);
  std::string token;

  while(!this->_stack.empty()) {
	_stack.pop();
  }

  while(ss >> token) {
    if (isOperator(token)) {
		if (this->_stack.size() < 2) {
		  return RPN_INSUFFICIENT_VALUES;
		}
		int b = this->_stack.top(); this->_stack.pop();
		int a = this->_stack.top(); this->_stack.pop();

		int res;
		if (!applyOperator(a, b, token, res)) {
		  return RPN_DIV_BY_ZERO;
		}

		this->_stack.push(res);
	} else {
	  if (token.length() != 1 || !std::isdigit(static_cast<unsigned char>(token[0]))) {
		return RPN_BAD_TOKEN;
	  }
      this->_stack.push(static_cast<int>(std::atoi(token.c_str())));
	}
  }

  if (this->_stack.size() != 1) {
	return RPN_BAD_EXPRESSION;
  }
  result = this->_stack.top();
  return RPN_OK;
}
