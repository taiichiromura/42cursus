#pragma once

template <typename T>
Array<T>::Array() : _array(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _size(n) {
  if (n == 0) {
    _array = NULL;
  } else {
    _array = new T[n]();
  }
}

template <typename T>
Array<T>::Array(const Array<T> &other) : _array(NULL), _size(other.size()) {
  if (this->_size > 0) {
    this->_array = new T[this->_size]();
    for(unsigned int i = 0; i < this->_size; i++) {
      this->_array[i] = other._array[i];
    }
  }
}

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &other) {
  if (this != &other) {
    delete[] this->_array;
    this->_size = other._size;
    if (this->_size > 0) {
      this->_array = new T[this->_size]();
      for (unsigned int i = 0; i < this->_size; i++) {
        this->_array[i] = other._array[i];
      }
    } else {
      this->_array = NULL;
    }
  }
  return *this;
}

template <typename T>
Array<T>::~Array() { delete[] this->_array; }

template <typename T>
unsigned int Array<T>::size() const { return this->_size; }

template <typename T>
T &Array<T>::operator[](unsigned int i) {
  if (i >= this->_size) {
    throw std::out_of_range("Array: index out of range");
  }
  return this->_array[i];
}

template <typename T>
const T &Array<T>::operator[](unsigned int i) const {
  if (i >= this->_size) {
    throw std::out_of_range("Array: index out of range");
  }
  return this->_array[i];
}
