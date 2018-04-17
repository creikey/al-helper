#define ALHELP_IMPLEMENTATION
#include <alhelp.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Square : public alhelp::Frontend {
public:
  void run(double delta) {
    if (this->sys->key_down(ALLEGRO_KEY_RIGHT))
      this->pos.x += this->speed;
    if (this->sys->key_down(ALLEGRO_KEY_LEFT))
      this->pos.x -= this->speed;
    if (this->sys->key_down(ALLEGRO_KEY_UP))
      this->pos.y -= this->speed;
    if (this->sys->key_down(ALLEGRO_KEY_DOWN))
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
         double inSpeed, alhelp::System *inSys)
      : pos(alhelp::Vector2<double>(0, 0)), size(inSize), myColor(inColor),
        speed(inSpeed), sys(inSys){};

private:
  alhelp::Vector2<double> pos;
  alhelp::Vector2<double> size;
  alhelp::SafeColor myColor;
  const std::string myID = "Square";
  const int zIndex = 1;
  double speed;
  alhelp::System *sys;
};

int main(int argc, char **argv) {
  alhelp::System sys(alhelp::Vector2<int>(500, 500),
                     alhelp::SafeColor(50, 50, 50), 60);
  sys.init();
  sys.addFrontend(new Square(alhelp::Vector2<double>(100.0, 100.0),
                             alhelp::SafeColor(255, 0, 0), 5, &sys));
  while (sys.getClose() == false) {
    sys.run();
  }
}
