#include "Fixed.hpp"


Fixed::Fixed() : _rawBits(0) {}

Fixed::Fixed(const int n) {
	if (n > MAX_FIXED_INT || n < MIN_FIXED_INT) {
         std::cerr << "[Warning] Input int " << n << " is too large!" << std::endl;
    }
	this->_rawBits = n << _fractionalBits;
}

Fixed::Fixed(const float f) {
	if (f > (float)MAX_FIXED_INT || f < (float)MIN_FIXED_INT) {
        std::cerr << "[Warning] Float value " << f << " is too large!" << std::endl;
    }
    this->_rawBits = (int)roundf(f * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed& other) {
    *this = other;
}

void Fixed::_checkIntegerOverflow(long raw_value, const std::string& op) const {
	long int_part = raw_value >> _fractionalBits;
    if (int_part > MAX_FIXED_INT || int_part < MIN_FIXED_INT) {
        std::cerr << "[Warning] Integer overflow in " << op
                  << ": " << int_part << " exceeds 24-bit range!" << std::endl;
    }
}

Fixed& Fixed::operator=(const Fixed& other) {
    if (this != &other) {
        this->_rawBits = other.getRawBits();
    }
    return *this;
}

Fixed::~Fixed() {}


int Fixed::getRawBits(void) const {
    return this->_rawBits;
}

void Fixed::setRawBits(int const raw) {
    this->_rawBits = raw;
}


float Fixed::toFloat(void) const {
    return (float)this->_rawBits / (1 << _fractionalBits);
}

int Fixed::toInt(void) const {
    return this->_rawBits >> _fractionalBits;
}


bool Fixed::operator>(const Fixed& other) const { return this->_rawBits > other._rawBits; }
bool Fixed::operator<(const Fixed& other) const { return this->_rawBits < other._rawBits; }
bool Fixed::operator>=(const Fixed& other) const { return this->_rawBits >= other._rawBits; }
bool Fixed::operator<=(const Fixed& other) const { return this->_rawBits <= other._rawBits; }
bool Fixed::operator==(const Fixed& other) const { return this->_rawBits == other._rawBits; }
bool Fixed::operator!=(const Fixed& other) const { return this->_rawBits != other._rawBits; }


Fixed Fixed::operator+(const Fixed& other) const {
    Fixed res;
    res.setRawBits(this->_rawBits + other._rawBits);
	_checkIntegerOverflow((long)this->_rawBits + (long)other._rawBits, "plus");
    return res;
}

Fixed Fixed::operator-(const Fixed& other) const {
    Fixed res;
    res.setRawBits(this->_rawBits - other._rawBits);
	_checkIntegerOverflow((long)this->_rawBits - (long)other._rawBits, "minus");
    return res;
}

Fixed Fixed::operator*(const Fixed& other) const {
    Fixed res;
    res.setRawBits(((long)this->_rawBits * other._rawBits) >> _fractionalBits);
	_checkIntegerOverflow(((long)this->_rawBits * other._rawBits) >> _fractionalBits, "multi");
    return res;
}

Fixed Fixed::operator/(const Fixed& other) const {
    Fixed res;
    res.setRawBits(((long)this->_rawBits << _fractionalBits) / other._rawBits);
	_checkIntegerOverflow(((long)this->_rawBits << _fractionalBits) / other._rawBits, "division");
    return res;
}

Fixed& Fixed::operator++(void) {
    this->_rawBits++;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp(*this);
    this->_rawBits++;
    return temp;
}

Fixed& Fixed::operator--(void) {
    this->_rawBits--;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp(*this);
    this->_rawBits--;
    return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a <= b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a <= b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a >= b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a >= b) ? a : b;
}


std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    os << fixed.toFloat();
    return os;
}
