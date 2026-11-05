#include "Serializer.hpp"
#include <iostream>

int main() {
  Data value;
  value.num = 42;

  std::cout << "--- Original Pointer ---" << std::endl;
  std::cout << "Address of value : " << &value << std::endl;
  std::cout << "Value of value.num : " << value.num << std::endl;
  std::cout << std::endl;

  uintptr_t raw = Serializer::serialize(&value);
  std::cout << "--- Serialized (uintptr_t) ---" << std::endl;
  std::cout << "uintptr_t value  : " << raw << std::endl;
  std::cout << std::endl;

  Data *restored_ptr = Serializer::deserialize(raw);
  std::cout << "--- Deserialized Pointer ---" << std::endl;
  std::cout << "Restored Address : " << restored_ptr << std::endl;
  std::cout << "Restored value.num : " << restored_ptr->num << std::endl;
  std::cout << std::endl;

  std::cout << "--- Verification ---" << std::endl;
  if (restored_ptr == &value) {
    std::cout << "SUCCESS: Pointers match perfectly!" << std::endl;
  } else {
    std::cout << "FAILURE: Pointers do not match!" << std::endl;
  }

  return 0;
}
