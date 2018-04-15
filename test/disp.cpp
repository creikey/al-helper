#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <allegro5/allegro.h>
#include <iostream>

int main(int argc, char **argv) {
  alhelp::System sys(alhelp::Vector<int>(300, 300),
                     alhelp::SafeColor(200, 200, 200));
  try {
    sys.init();
  } catch (alhelp::InitFail fail) {
    std::cout << fail.what() << std::endl;
    return 1;
  }
  al_rest(3);
  return 0;
}
