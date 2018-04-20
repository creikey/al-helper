#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

class Square : public alhelp::Frontend {
public:
  void run(double delta) {
    this->fpsCounter += delta;
    this->frameCounter++;
    if (frameCounter >= this->fps) {
      std::cout << "Fps: " << this->fpsCounter << std::endl;
      this->fpsCounter = 0;
      this->frameCounter = 0;
    }
    if (this->sys->keyIsDown(ALLEGRO_KEY_RIGHT))
      this->pos.x += this->speed;
    if (this->sys->keyIsDown(ALLEGRO_KEY_LEFT))
      this->pos.x -= this->speed;
    if (this->sys->keyIsDown(ALLEGRO_KEY_UP))
      this->pos.y -= this->speed;
    if (this->sys->keyIsDown(ALLEGRO_KEY_DOWN))
      this->pos.y += this->speed;
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
        speed(inSpeed), sys(inSys), myID(inID) {
    this->fps = this->sys->getFps();
  };

private:
  alhelp::Vector2<double> pos;
  alhelp::Vector2<double> size;
  alhelp::SafeColor myColor;
  double fpsCounter = 0;
  int frameCounter = 0;
  double fps;
  const int zIndex = 1;
  double speed;
  alhelp::System *sys;
  std::string myID = "Square";
};

int main(int argc, char **argv) {
  alhelp::System sys(alhelp::Vector2<int>(500, 500),
                     alhelp::SafeColor(50, 50, 50), 60);
  sys.init();
  for (int i = 0; i < 100; i++) {
    sys.addFrontend(
        new Square(alhelp::Vector2<double>(i * 5 + 10.0, i * 5 + 10.0),
                   alhelp::SafeColor(255, 0, 0), 5, &sys, std::to_string(i)));
  }
  while (sys.getClose() == false) {
    sys.run();
  }
}
