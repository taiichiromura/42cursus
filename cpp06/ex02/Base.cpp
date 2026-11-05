#include "Base.hpp"

Base::~Base() {}

Base *generate(void) {
  int random_num = std::rand() % 3;
  if (random_num == 0) {
    A *a = new A;
    return a;
  }
  if (random_num == 1) {
    B *b = new B;
    return b;
  }
  if (random_num == 2) {
    C *c = new C;
    return c;
  }
  return NULL;
}

void identify(Base *p) {
  if (!p) {
    std::cout << "NULL" << std::endl;
    return;
  }
  std::cout << "Identify (Pointer): ";
  if (dynamic_cast<A *>(p)) {
    std::cout << "A" << std::endl;
  } else if (dynamic_cast<B *>(p)) {
    std::cout << "B" << std::endl;
  } else if (dynamic_cast<C *>(p)) {
    std::cout << "C" << std::endl;
  } else
    std::cout << "Unknown class" << std::endl;
}

void identify(Base &p) {
  std::cout << "Identify (Reference): ";
  try {
    (void)dynamic_cast<A &>(p);
    std::cout << "A" << std::endl;
    return;
  } catch (const std::exception &e) {
  }

  try {
    (void)dynamic_cast<B &>(p);
    std::cout << "B" << std::endl;
    return;
  } catch (const std::exception &e) {
  }

  try {
    (void)dynamic_cast<C &>(p);
    std::cout << "C" << std::endl;
    return;
  } catch (const std::exception &e) {
  }

  std::cout << "Unknown class" << std::endl;
}
