#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath> // roundf 用

class Fixed {
private:
    int _rawBits;
    static const int _fractionalBits = 8;

public:
    // ex00 からの継続
    Fixed();
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed();

    // ex01 で追加
    Fixed(const int n);
    Fixed(const float f);

    float toFloat(void) const;
    int toInt(void) const;

    int getRawBits(void) const;
    void setRawBits(int const raw);
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
