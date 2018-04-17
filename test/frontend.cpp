#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

class MyCounter : public alhelp::Backend {
private:
  int counter = 0;
  const std::string myID = "MyCounter";
  alhelp::System *sys;

public:
  MyCounter(alhelp::System *inSys) : sys(inSys){};
  MyCounter(alhelp::System *inSys, int startCount)
      : counter(startCount), sys(inSys){};
  int getCount() { return counter; };
  void run(double delta) { counter++; }
  void setSystem(alhelp::System *newSys) { this->sys = newSys; };
  std::string getID() { return myID; };
};

class MyLine : public alhelp::Frontend {
private:
  alhelp::SafeColor myColor;
  alhelp::Vector2<int> myExtent;
  alhelp::System *sys;
  const int zIndex = 1;
  const std::string myID = "MyLine";

public:
  MyLine(alhelp::SafeColor inColor, alhelp::System *inSys)
      : myColor(inColor), sys(inSys){};
  void run(double delta) {
    try {
      myExtent.x =
          ((MyCounter *)sys->getBackend("MyCounter").get())->getCount();
      myExtent.y = ((MyCounter *)sys->getBackend("MyCounter").get())->getCount();
    } catch (alhelp::IDFail fail) {
      std::cout << "Error: " << fail.what() << std::endl;
    }
  };
  void setSystem(alhelp::System *newSystem) { this->sys = newSystem; };
  std::string getID() { return this->myID; };
  void draw() { al_draw_line(0, 0, myExtent.x, myExtent.y, myColor.al_c(), 1); }
  int getZIndex() { return this->zIndex; };
};

int main(int argc, char **argv) {
  alhelp::System sys(alhelp::Vector2<int>(500, 500),
                     alhelp::SafeColor(20, 20, 20), 60);
  try {
    sys.init();
  } catch (alhelp::InitFail fail) {
    std::cout << fail.what() << std::endl;
    return 1;
  }
  sys.addBackend(new MyCounter(&sys, 0));
  sys.addFrontend(new MyLine(alhelp::SafeColor(255, 0, 0), &sys));
  while (!sys.getClose()) {
    sys.run();
  }
  return 0;
}
