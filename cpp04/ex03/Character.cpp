#include "Character.hpp"

Character::Character(std::string const &name) : _name(name) {
  for (int i = 0; i < 4; i++)
    _cSlot[i] = NULL;
  for (int i = 0; i < 100; i++)
    _floor[i] = NULL;
}

Character::~Character() {
  for (int i = 0; i < 4; i++) {
      delete _cSlot[i];
  }
  for (int i = 0; i < 100; i++) {
      delete _floor[i];
  }
}

Character::Character(const Character &other) {
  for (int i = 0; i < 4; i++)
    _cSlot[i] = NULL;
  for (int i = 0; i < 100; i++)
    _floor[i] = NULL;
  *this = other;
}

Character &Character::operator=(const Character &other) {
  if (this == &other)
    return *this;
  _name = other._name;
  for (int i = 0; i < 4; i++) {
    if (this->_cSlot[i] != NULL) {
      delete this->_cSlot[i];
      this->_cSlot[i] = NULL;
    }
    if (other._cSlot[i] != NULL)
      this->_cSlot[i] = other._cSlot[i]->clone();
  }
  return *this;
}

std::string const &Character::getName() const { return _name; }

void Character::equip(AMateria *m) {
  if (m == NULL)
    return;
  for (int i = 0; i < 4; i++) {
    if (_cSlot[i] == NULL) {
      _cSlot[i] = m;
      std::cout << "Equipped " << m->getType() << " at slot " << i << std::endl;
      return;
    }
  }
  std::cout << "character slot is full!" << std::endl;
  this->drop(m);
  return ;
}

void Character::unequip(int idx) {
  if (idx < 0 || idx >= 4 || _cSlot[idx] == NULL)
    return;
  for (int i = 0; i < 100; i++) {
    if (_floor[i] == NULL) {
      _floor[i] = _cSlot[idx];
      break;
    }
  }
  _cSlot[idx] = NULL;
}

void Character::use(int idx, ICharacter &target) {
  if (idx >= 0 && idx < 4 && _cSlot[idx])
    _cSlot[idx]->use(target);
}

void Character::drop(AMateria *materia) {
    if (materia == NULL) return;

    for (int i = 0; i < 100; i++) {
        if (this->_floor[i] == materia) return;
        if (this->_floor[i] == NULL) {
            this->_floor[i] = materia;
            return;
        }
    }
    delete materia;
}
