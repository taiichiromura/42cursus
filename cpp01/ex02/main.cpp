#include <iostream>
#include <string>

int main() {
  // 1. 文字列変数の初期化
  std::string str = "HI THIS IS BRAIN";

  // 2. ポインタと参照の作成
  std::string *stringPTR = &str; // 変数の「住所」を格納
  std::string &stringREF = str;  // 変数の「別名」として振る舞う

  // --- メモリアドレスの表示 ---
  std::cout << "Memory address of the string variable: " << &str << std::endl;
  std::cout << "Memory address held by stringPTR:      " << stringPTR
            << std::endl;
  std::cout << "Memory address held by stringREF:      " << &stringREF
            << std::endl;

  std::cout << "------------------------------------------------" << std::endl;

  // --- 値の表示 ---
  std::cout << "Value of the string variable:  " << str << std::endl;
  std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
  std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;

  return 0;
}
