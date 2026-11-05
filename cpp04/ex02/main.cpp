#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main() {
  Cat *cat = new Cat();
  Dog *dog = new Dog();

  for (int i = 0; i < 50; i++) {
    cat->setIdea(i, "catsidea");
    dog->setIdea(i, "dogidea");
  }

  // 表示テスト
  std::cout << "--- Cat's Idea 0 ---" << std::endl;
  std::cout << cat->getIdea(0) << std::endl;
  std::cout << cat->getIdea(70) << std::endl;
  std::cout << cat->getIdea(10000) << std::endl;

  std::cout << dog->getIdea(10000) << std::endl;


  Cat *shallow = cat;
  std::cout << "Shallow copy cat : " << shallow->getIdea(0) << std::endl;
  std::cout << "Shallow address: " << shallow << " cat address : " << cat
            << std::endl;
  std::cout << "--- Deep Copy Test ---" << std::endl;
  Cat temp_cat = *cat;
  std::cout << "Deep address: " << &temp_cat << " cat address : " << cat
            << std::endl;
  temp_cat.setIdea(0, "Updated idea");
  std::cout << "Original cat idea 0: " << cat->getIdea(0) << std::endl;
  std::cout << "Copied cat idea 0: " << temp_cat.getIdea(0) << std::endl;

  delete cat;
  delete dog;

  return 0;
  // const Animal* meta = new Animal();
  // const Animal* j = new Dog();
  // const Animal* i = new Cat();
  // std::cout << j->getType() << " " << std::endl;
  // std::cout << i->getType() << " " << std::endl;
  // i->makeSound(); //will output the cat sound!
  // j->makeSound();
  // meta->makeSound();

  // delete i;
  // delete j;
}
