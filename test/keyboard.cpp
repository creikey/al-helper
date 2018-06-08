#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

class FPSCounter : public alhelp::Backend {
public:
  void run(double delta) {
    this->fpsCounter += delta;
    this->frameCounter++;
    if (this->frameCounter >= this->fps) {
      std::cout << "Fps: " << this->fpsCounter << std::endl;
      this->frameCounter = 0;
      this->fpsCounter = 0;
    }
  }
  void setSystem(alhelp::System *newSys) { this->sys = newSys; }
  std::string getID() { return this->myID; };
  FPSCounter(alhelp::System *inSys) : sys(inSys) {
    this->fps = this->sys->getFps();
  };

private:
  alhelp::System *sys;
  double fpsCounter = 0;
  int frameCounter = 0;
  double fps;
  std::string myID = "Frame Counter";
};

class Square : public alhelp::Frontend {
public:
  void run(double delta) {
    if (this->sys->keyIsDown(ALLEGRO_KEY_RIGHT))
      this->pos.x += this->speed;
    if (this->sys->keyIsDown(ALLEGRO_KEY_LEFT))
      this->pos.x -= this->speed;
    if (this->sys->keyIsDown(ALLEGRO_KEY_UP))
      this->pos.y -= this->speed;
    if (this->sys->keyIsDown(ALLEGRO_KEY_DOWN))
      this->pos.y += this->speed;
    this->size.x += delta;
    this->size.y += delta;
    // std::cout << "Increasing by " << delta << "size!" << std::endl;
  }
  void setSystem(alhelp::System *newSystem) { this->sys = newSystem; };
  std::string getID() { return this->myID; };
  void draw() {
    al_draw_rectangle(pos.x, pos.y, pos.x + size.x, pos.y + size.y,
                      myColor.al_c(), 1);
  }
  int getZIndex() { return this->zIndex; }
  Square(alhelp::Vector2<double> inSize, alhelp::SafeColor inColor,
         double inSpeed, alhelp::System *inSys, std::string inID)
      : pos(alhelp::Vector2<double>(0, 0)), size(inSize), myColor(inColor),
        speed(inSpeed), sys(inSys), myID(inID){};

private:
  alhelp::Vector2<double> pos;
  alhelp::Vector2<double> size;
  alhelp::SafeColor myColor;
  const int zIndex = 1;
  double speed;
  alhelp::System *sys;
  std::string myID = "Square";
};

int main(int argc, char **argv) {
  alhelp::Settings settings;
  settings.displaySize = alhelp::Vector2<int>(500, 500);
  settings.clearColor = alhelp::SafeColor(0, 0, 0);
  settings.fps = 60.0;
  alhelp::System sys(&settings);
  sys.addBackend(new FPSCounter(&sys));
  sys.init();
  for (int i = 0; i < 100; i++) {
    sys.addFrontend(new Square(
        alhelp::Vector2<double>(i * 2 + 10.0, i * 2 + 10.0),
        alhelp::SafeColor(i, i * 2, i * 3), 5, &sys, std::to_string(i)));
  }
  while (sys.getClose() == false) {
    sys.run(std::cout);
  }
}
