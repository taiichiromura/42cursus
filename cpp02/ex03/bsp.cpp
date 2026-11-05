#include "Point.hpp"

static Fixed sign(Point const p1, Point const p2, Point const p3) {
    // --- STEP 1: ベクトルを作る ---
    Fixed ux = p2.getX() - p1.getX();
    Fixed uy = p2.getY() - p1.getY();

    Fixed vx = p3.getX() - p1.getX();
    Fixed vy = p3.getY() - p1.getY();

    // --- STEP 2: 左に90度回転 ---
    // (x, y) を左に90度回すと (-y, x) になるという定義をそのまま変数にする
    Fixed left_ux = Fixed(-1) * uy;
    Fixed left_uy = ux;

    // --- STEP 3: 回転させた後のベクトルと、相手の内積をとる ---
    // 内積の公式： A(x1, y1) * B(x2, y2) = x1 * x2 + y1 * y2
    Fixed result = (left_ux * vx) + (left_uy * vy);

    return result;
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed d1, d2, d3;

    d1 = sign(a, b, point);
    d2 = sign(b, c, point);
    d3 = sign(c, a, point);

    // 全てが正、あるいは全てが負なら内部にある
    // 0が含まれる場合は辺上か頂点上なので False
    bool neg = (d1 < 0) && (d2 < 0) && (d3 < 0);
    bool pos = (d1 > 0) && (d2 > 0) && (d3 > 0);

    return neg || pos;
}
