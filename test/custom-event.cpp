#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <iostream>
#include <string>

class MyTimer : public alhelp::Backend {
public:
  void run(double delta) { std::cout << "Running" << std::endl; };
  void setSystem(alhelp::System *newSystem) { this->sys = newSystem; };
  std::string getID() { return this->myID; };
  void onTimer(ALLEGRO_EVENT inEv, bool *toCaught) {
    if (inEv.timer.source == this->myTimer) {
    }
  }
  MyTimer(alhelp::System *inSys, int delay) : sys(inSys) {
    this->myTimer = al_create_timer(delay);
    this->otherTimer = al_create_timer(delay * 2);
    inSys->addEventSource(al_get_timer_event_source(this->myTimer));
    inSys->addEventSource(al_get_timer_event_source(this->otherTimer));
    inSys->addEventCallback(ALLEGRO_EVENT_TIMER, this->onTimer);
    inSys->addEventCallback(ALLEGRO_EVENT_TIMER, this->onTimer);
  }

private:
  ALLEGRO_TIMER *myTimer;
  ALLEGRO_TIMER *otherTimer;
  alhelp::System *sys;
  std::string myID;
};

int main(void) {
  alhelp::Settings settings;
  settings.displaySize = alhelp::Vector2<int>(500, 500);
  settings.clearColor = alhelp::SafeColor(20, 20, 20);
  settings.fps = 60;
  alhelp::System sys = alhelp::System(&settings);
  sys.addBackend(new MyTimer(&sys, 1));
  sys.init();
  while (sys.getClose() == false) {
    sys.run(std::cout);
  }
}
