#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./RPN <RPN expression>" << std::endl;
        return 1;
    }

    RPN rpn;
    int result;
    RPNError err = rpn.evaluate(argv[1], result);

    switch (err)
    {
        case RPN_OK:
            std::cout << result << std::endl;
            return 0;
        case RPN_BAD_TOKEN:
            std::cerr << "Error: bad token in expression" << std::endl;
            return 1;
        case RPN_DIV_BY_ZERO:
            std::cerr << "Error: division by zero" << std::endl;
            return 1;
        case RPN_INSUFFICIENT_VALUES:
            std::cerr << "Error: insufficient values in expression" << std::endl;
            return 1;
        case RPN_BAD_EXPRESSION:
            std::cerr << "Error: bad expression" << std::endl;
            return 1;
        default:
            std::cerr << "Error" << std::endl;
            return 1;
    }
}
