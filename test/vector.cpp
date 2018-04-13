#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <iostream>

int main(void) {
  Vector<int> myVec(5, 4);
  std::cout << "Before myvec: " << myVec.toString() << std::endl;
  Vector<int> otherVec(3, 2);
  myVec = myVec + otherVec;
  std::cout << "Myvec: " << myVec.toString() << std::endl;
  std::cout << "OtherVec: " << otherVec.toString() << std::endl;
}
