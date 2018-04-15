#ifndef HPP_ALHELP
#define HPP_ALHELP
// header file
#include <allegro5/allegro.h>
#include <cmath>
#include <exception>
#include <string>

namespace alhelp {
// Standard 2d Vector
template <class T = float> class Vector {
public:
  T x;
  T y;
  Vector() : x(T(0)), y(T(0)){};
  Vector(T inx, T iny) : x(inx), y(iny){};
  Vector<double> normalize() {
    double len = this->length();
    return Vector<double>(this->x / len, this->y / len);
  };
  double length() { return sqrt(this->x * this->x + this->y * this->y); };
  std::string toString() {
    return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
  };

  Vector &operator+(const Vector &vec) {
    this->x += vec.x;
    this->y += vec.y;
    return *this;
  }; // add
  Vector &operator*(const Vector &vec) {
    this->x *= vec.x;
    this->y *= vec.y;
    return *this;
  };
  Vector &operator*(const T scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  };
  Vector &operator-(const Vector &vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
  };
  Vector &operator/(const Vector &vec) {
    this->x /= vec.x;
    this->y /= vec.y;
    return *this;
  };
  bool operator>(const Vector &vec) {
    return (this->x > vec.x) && (this->y > vec.y);
  }
  bool operator<(const Vector &vec) {
    return (this->x < vec.x) && (this->y < vec.y);
  }
};
class SafeColor {
public:
  SafeColor() : r(0), g(0), b(0){};
  SafeColor(double inr, double ing, double inb) : r(inr), g(ing), b(inb){};
  ALLEGRO_COLOR al_c() { return al_map_rgb(this->r, this->g, this->b); };

private:
  double r;
  double g;
  double b;
};
class InitFail : public std::exception {
public:
  const char *what() const throw() {
    return ("Failed to initialize allegro in method `" + methodName + "`" +
            " with input `" + methodInput + "`")
        .c_str();
  }
  InitFail() : methodName("unknown"), methodInput("unknown"){};
  InitFail(std::string inMethod, std::string inInput)
      : methodName(inMethod), methodInput(inInput){};
  InitFail(std::string inMethod) : methodName(inMethod), methodInput(""){};

private:
  std::string methodName;
  std::string methodInput;
};
class System {
private:
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *queue = NULL;
  SafeColor clearcl;
  Vector<int> dispSize;

public:
  System() : clearcl(SafeColor(0, 0, 0)), dispSize(Vector<int>(500, 500)){};
  System(Vector<int> inDispSize, SafeColor col)
      : clearcl(col), dispSize(inDispSize){};
  void init();
  ~System();
};
}

// #define ALHELP_IMPLEMENTATION // for linter in atom
#ifdef ALHELP_IMPLEMENTATION
// code
namespace alhelp {
void System::init() {
  if (!al_init()) {
    throw InitFail("al_init");
  }
  this->display = al_create_display(this->dispSize.x, this->dispSize.y);
  if (!this->display) {
    throw InitFail("al_create_display", this->dispSize.toString());
  }
  this->queue = al_create_event_queue();
  if (!this->queue) {
    throw InitFail("al_create_event_queue");
  }
  al_clear_to_color(clearcl.al_c());
  al_flip_display();
}
System::~System() {
  al_destroy_display(this->display);
  al_destroy_event_queue(this->queue);
}
}

#endif // ALHELP_IMPLEMENTATION
#endif // HPP_ALHELP
