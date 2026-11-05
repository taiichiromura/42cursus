#include <string>

#include "MutantStack.hpp"

template <typename T>
void printStack(MutantStack<T>& s) {
  typename MutantStack<T>::it it = s.begin();
  typename MutantStack<T>::it ite = s.end();
  while (it != ite) {
    std::cout << *it << " ";
    ++it;
  }
  std::cout << std::endl;
}

int main() {
  std::cout << "=== 1. 基本動作 (push/top/pop) ===" << std::endl;
  MutantStack<int> mstack;
  mstack.push(1);
  std::cout << "top: " << mstack.top() << std::endl;
  mstack.pop();
  std::cout << "size after pop: " << mstack.size() << std::endl;

  mstack.push(1);
  mstack.push(2);
  mstack.push(3);

  std::cout << "\n=== 2. イテレーターで begin -> end ===" << std::endl;
  printStack(mstack);

  std::cout << "\n=== 3. コピーコンストラクタ ===" << std::endl;
  MutantStack<int> copy(mstack);
  printStack(copy);
  std::cout << "元と別物か確認のため copy に push(99)" << std::endl;
  copy.push(99);
  std::cout << "copy : ";
  printStack(copy);
  std::cout << "元(mstack)は影響を受けないはず : ";
  printStack(mstack);

  std::cout << "\n=== 4. 代入演算子 ===" << std::endl;
  MutantStack<int> assigned;
  assigned.push(100);
  assigned = mstack;
  std::cout << "assigned : ";
  printStack(assigned);

  std::cout << "\n=== 5. 自己代入 (a = a) が壊れないか ===" << std::endl;
  MutantStack<int>* self = &assigned;
  assigned = *self;
  std::cout << "self-assign後も無事か : ";
  printStack(assigned);

  std::cout << "\n=== 6. "
               "begin()取得後にpush/popしても新しいiteratorなら反映されるか ==="
            << std::endl;
  MutantStack<int> mutating;
  mutating.push(1);
  mutating.push(2);
  mutating.push(3);
  mutating.push(4);
  mutating.pop();    // 4を消す
  mutating.push(5);  // 5を足す
  std::cout << "mutating後 : ";
  printStack(mutating);

  std::cout << "\n=== 7. std::stack との比較(通常stackと同じ挙動か) ==="
            << std::endl;
  std::stack<int> normal;
  normal.push(1);
  normal.push(2);
  normal.push(3);
  std::cout << "std::stack top: " << normal.top() << " size: " << normal.size()
            << std::endl;
  std::cout << "MutantStack top: " << mstack.top() << " size: " << mstack.size()
            << std::endl;

  std::cout << "\n=== 8. empty() の確認 ===" << std::endl;
  MutantStack<int> emptyStack;
  std::cout << "emptyStack.empty(): " << (emptyStack.empty() ? "true" : "false")
            << std::endl;
  emptyStack.push(42);
  std::cout << "push後 empty(): " << (emptyStack.empty() ? "true" : "false")
            << std::endl;

  std::cout << "\n=== 9. 別の型(std::string)でも動くか ===" << std::endl;
  MutantStack<std::string> sstack;
  sstack.push("hello");
  sstack.push("mutant");
  sstack.push("stack");
  printStack(sstack);

  std::cout << "\n=== 10. 要素1つだけの時のイテレーター ===" << std::endl;
  MutantStack<int> single;
  single.push(42);
  printStack(single);

  return 0;
}
