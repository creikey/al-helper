#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <iostream>

int main(void) {
  alhelp::Vector<int> myVec(5, 4);
  std::cout << "My vec: " << myVec.toString() << std::endl;
  std::cout << "Length: " << myVec.length() << std::endl;
  std::cout << "Normalized: " << myVec.normalize().toString() << std::endl;
}
