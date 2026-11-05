#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
private:
    Fixed const _x;
    Fixed const _y;

public:
    Point();                                 // デフォルト
    Point(const float x, const float y);     // 座標指定
    Point(const Point& other);              // コピー
    Point& operator=(const Point& other);    // 代入（実際はconstなので何もしない）
    ~Point();

    Fixed getX(void) const;
    Fixed getY(void) const;
};

bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif
