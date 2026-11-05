template <typename T>
const int& easyfind(T& container, const int& num) {
  typename T::const_iterator it =
      std::find(container.begin(), container.end(), num);
  if (it == container.end()) {
    throw std::runtime_error("could not find the value");
  }
  return *it;
}
