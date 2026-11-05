#include <iostream>
#include "Fixed.hpp"

int main(void) {
    std::cout << "resumeのテスト" << std::endl;
    Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;

    std::cout << "演算子テスト" << std::endl;
    Fixed const f1(2);
    Fixed const f2(1.5f);

    std::cout << "2 + 1 = " << (f1 + f2) << std::endl;
    std::cout << "2 - 1.5 = " << (f1 - f2) << " (expected: 0.5)" << std::endl;
    std::cout << "2 * 1.5 = " << (f1 * f2) << " (expected: 3)" << std::endl;
    std::cout << "2 / 1.5 = " << (f1 / f2) << " (expected: 1.33203)" << std::endl;

    std::cout << "f1(2) > f2(1.5): " << (f1 > f2) << std::endl;
    std::cout << "f1(2) < f2(1.5): " << (f1 < f2) << std::endl;
	std::cout << "f1(2) >= f2(1.5): " << (f1 >= f2) << std::endl;
    std::cout << "f1(2) >= f2(1.5): " << (f1 >= f2) << std::endl;

    std::cout << "f1(2) == 2:      " << (f1 == Fixed(2)) << std::endl;
	std::cout << "fixedと通常int" << (f1 < 2) << std::endl;

	//境界値
	Fixed const max_fixed_int(8388607);
	Fixed const min_fixed_int(-8388608);

	std::cout << "max_fixed_int + 2:      " << (max_fixed_int + f1) << std::endl;

	Fixed const float1(1.0f);
	Fixed const float2(0.00280624f);
	std::cout << "1/256以下の値をプラスするテスト:" << (float1 + float2) << std::endl;


    std::cout << "\nminmaxテスト" << std::endl;

    // 非const版のテスト
    Fixed g(10);
    Fixed h(20);
    std::cout << "Max of 10 and 20: " << Fixed::max(g, h) << std::endl;

    // 非const版が参照を返しているか確認（値を直接書き換える）
    Fixed::max(g, h) = Fixed(0);
    std::cout << "After Fixed::max(g, h) = 0, h is: " << h << " (expected: 0)" << std::endl;

    // const版のテスト
    Fixed const i(42.42f);
    Fixed const j(100);
    std::cout << "Max (const) of 42.42 and 100: " << Fixed::max(i, j) << std::endl;

	// max,minの同値テスト
	Fixed o(10);
	Fixed p(10);

	Fixed& result_min = Fixed::min(o, p);
	Fixed& result_max = Fixed::max(o, p);
	std::cout << "addres o =" << &o << std::endl;
	std::cout << "addres max result =" << &result_min << std::endl;
	std::cout << "addres min result =" << &result_max << std::endl;
    return 0;
}
