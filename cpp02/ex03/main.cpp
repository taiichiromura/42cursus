#include <iostream>
#include "Point.hpp"
#include <iomanip>

int main(void) {
    // 三角形の頂点設定
    Point const a(0, 0);
    Point const b(10, 0);
    Point const c(0, 10);

    // 内部
    std::cout << "Inside (2, 2)   : " << (bsp(a, b, c, Point(2, 2)) ? "True" : "False") << std::endl;
    // 外部
    std::cout << "Outside (15, 15): " << (bsp(a, b, c, Point(15, 15)) ? "True" : "False") << std::endl;

    // 辺の上 (Edge)
    std::cout << "On Edge (5, 0)  : " << (bsp(a, b, c, Point(5, 0)) ? "True" : "False") << std::endl;
    std::cout << "On Edge (5, 5)  : " << (bsp(a, b, c, Point(5, 5)) ? "True" : "False") << std::endl;
    // 頂点の上 (Vertex)
    std::cout << "On Vertex (0, 0): " << (bsp(a, b, c, Point(0, 0)) ? "True" : "False") << std::endl;

    // 境界ギリギリの内側
    std::cout << "Tiny Inside     : " << (bsp(a, b, c, Point(0.1f, 0.1f)) ? "True" : "False") << std::endl;
    // 境界ギリギリの外側
    std::cout << "Tiny Outside    : " << (bsp(a, b, c, Point(-0.01f, 5)) ? "True" : "False") << std::endl;

    return 0;
}
