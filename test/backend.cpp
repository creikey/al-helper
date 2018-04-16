#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <string>

class MyAdder : public alhelp::Backend {
public:
  void run(double delta) {
    counter++;
    std::cout << "Counter is " << std::to_string(counter) << std::endl;
  };
  void setSystem(alhelp::System *newSystem) { sys = newSystem; }
  std::string getID() { return this->id; };
  MyAdder(alhelp::System *toSys) : counter(0), sys(toSys){};

private:
  int counter;
  const std::string id = "Adder";
  alhelp::System *sys;
};

int main(int argc, char **argv) {
  alhelp::System sys(alhelp::Vector2<int>(500, 500),
                     alhelp::SafeColor(50, 50, 50), 60);
  sys.init();
  sys.addBackEnd(new MyAdder(&sys));
  while (!sys.getClose()) {
    sys.run();
  }
}
