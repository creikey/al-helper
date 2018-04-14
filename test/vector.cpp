#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <iostream>

int main(void) {
  alhelp::Vector<int> myVec(5, 4);
  std::cout << "Before myvec: " << myVec.toString() << std::endl;
  alhelp::Vector<int> otherVec(3, 2);
  myVec = myVec + alhelp::Vector<int>(2, 2);
  std::cout << "Myvec: " << myVec.toString() << std::endl;
  std::cout << "OtherVec: " << otherVec.toString() << std::endl;
}
