#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(const Serializer &other) { (void)other; }
Serializer &Serializer::operator=(const Serializer &other) {
  (void)other;
  return *this;
}
Serializer::~Serializer() {}

uintptr_t Serializer::serialize(Data *ptr) {
  uintptr_t pointer_value = reinterpret_cast<uintptr_t>(ptr);
  return pointer_value;
}

Data *Serializer::deserialize(uintptr_t raw) {
  Data *data = reinterpret_cast<Data *>(raw);
  return data;
}
