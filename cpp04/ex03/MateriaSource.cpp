#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
  std::cout << "MateriaSource constructor called." << std::endl;
  for (int i = 0; i < 4; i++)
    _mSlot[i] = NULL;
}

MateriaSource::MateriaSource(std::string const &type) {
  std::cout << "MateriaSource type : " << type << " constructor called."
            << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource &other) {
  std::cout << "MateriaSource copy constructor called." << std::endl;
  *this = other;
}

MateriaSource &MateriaSource::operator=(const MateriaSource &other) {
  if (this == &other)
    return *this;
  for (int i = 0; i < 4; i++) {
    if (this->_mSlot[i] != NULL) {
      delete this->_mSlot[i];
      this->_mSlot[i] = NULL;
    }
    if (other._mSlot[i] != NULL)
      this->_mSlot[i] = other._mSlot[i]->clone();
  }
  std::cout << "MateriaSource assignement constructor called" << std::endl;
  return *this;
}

MateriaSource::~MateriaSource() {
  for (int i = 0; i < 4; i++) {
    if (this->_mSlot[i] != NULL)
      delete _mSlot[i];
  }
  std::cout << "MateriaSource destructor called." << std::endl;
}

void MateriaSource::learnMateria(AMateria *materia) {

  if (materia == NULL)
    return;
  for (int i = 0; i < 4; i++) {
    if (this->_mSlot[i] == NULL) {
      _mSlot[i] = materia;
      std::cout << "MateriaSource just learnt " << materia->getType()
                << " at slot[" << i << "]" << std::endl;
      materia = NULL; // 住所メモを消す
      return;
    }
  }
  std::cout << "MateriaSource slot is full!" << std::endl;
  delete materia;
}

AMateria *MateriaSource::createMateria(std::string const &type) {
  for (int i = 0; i < 4; i++) {
    if (this->_mSlot[i] != NULL && this->_mSlot[i]->getType() == type) {
      return (this->_mSlot[i]->clone());
    }
  }
  return NULL;
}
