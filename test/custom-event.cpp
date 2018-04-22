#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <iostream>
#include <string>

class MyTimer : public alhelp::Backend {
public:
  void run(double delta) { std::cout << "Running" << std::endl; };
  void setSystem(alhelp::System *newSystem) { this->sys = newSystem; };
  std::string getID() { return this->myID; };
  MyTimer(alhelp::System *inSys, int delay) : sys(inSys) {
    this->myTimer = al_create_timer(delay);
    inSys->addEventSource(al_get_timer_event_source(this->myTimer));
    inSys->addEventCallback(ALLEGRO_TIMER)
  };

private:
  ALLEGRO_TIMER *myTimer;
  alhelp::System *sys;
  std::string myID;
};

int main(void) {
  alhelp::Settings settings;
  settings.displaySize = alhelp::Vector2<int>(500, 500);
  settings.clearColor = alhelp::SafeColor(20, 20, 20);
  settings.fps = 60;
  alhelp::System sys(&settings);
  sys.addBackend(new MyTimer(&sys));
  sys.init();
  while (sys.getClose() == false) {
    sys.run();
  }
}
