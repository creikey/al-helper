#ifndef HPP_ALHELP
#define HPP_ALHELP
// header file
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <exception>
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace alhelp {
// Standard 2d Vector2
template <class T = float> class Vector2 {
public:
  T x;
  T y;
  Vector2() : x(T(0)), y(T(0)){};
  Vector2(T inx, T iny) : x(inx), y(iny){};
  Vector2<double> normalize() {
    double len = this->length();
    return Vector2<double>(this->x / len, this->y / len);
  };
  double length() { return sqrt(this->x * this->x + this->y * this->y); };
  std::string toString() {
    return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
  };

  Vector2 &operator+(const Vector2 &vec) {
    this->x += vec.x;
    this->y += vec.y;
    return *this;
  }; // add
  Vector2 &operator*(const Vector2 &vec) {
    this->x *= vec.x;
    this->y *= vec.y;
    return *this;
  };
  Vector2 &operator*(const T scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  };
  Vector2 &operator-(const Vector2 &vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
  };
  Vector2 &operator/(const Vector2 &vec) {
    this->x /= vec.x;
    this->y /= vec.y;
    return *this;
  };
  bool operator>(const Vector2 &vec) {
    return (this->x > vec.x) && (this->y > vec.y);
  }
  bool operator<(const Vector2 &vec) {
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
class IDFail : public std::exception {
public:
  const char *what() const throw() {
    // return (("Could not find object with id `" + toSearchFor + "`").c_str());
    // return "Couldn't find id";
    return this->error.c_str();
  };
  IDFail(const std::string inSearchFor)
      : error("Could not find object with id `" + inSearchFor + "`"),
        toSearchFor(inSearchFor){};

private:
  const std::string error;
  const std::string toSearchFor;
};

class System;

class Backend {
public:
  virtual void run(double delta) = 0;
  virtual void setSystem(System *newSystem) = 0;
  virtual std::string getID() = 0; // Unique name of object
};

class Frontend : public Backend {
public:
  virtual void draw() = 0;
  virtual int getZIndex() = 0;
};

class Settings {
public:
  Vector2<int> displaySize = Vector2<int>(500, 500);
  SafeColor clearColor = SafeColor(0, 0, 0);
  double fps = 30.0;
  Settings(){};
};

class System {
private:
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *queue = NULL;
  bool initialized = false;
  bool close = false;
  bool redraw = false;
  Settings *sets;
  ALLEGRO_TIMER *fpsTimer = NULL;
  ALLEGRO_TIMER *performanceTimer = NULL;
  int previousPerformanceCount = 0;
  std::vector<std::shared_ptr<Backend>> backend;
  std::vector<ALLEGRO_EVENT_TYPE> eventTypes;
  std::vector<void (*)(ALLEGRO_EVENT, bool *)> eventFunctions;
  std::list<std::shared_ptr<Frontend>> frontend;
  ALLEGRO_KEYBOARD_STATE *keyState = NULL;

public:
  System(Settings *inSettings) : sets(inSettings){};
  ~System();
  void init();
  bool isInitialized() { return initialized; };
  std::shared_ptr<Backend> getBackend(std::string inID);
  std::shared_ptr<Frontend> getFrontend(std::string inID);
  void addFrontend(Frontend *toAdd);
  void addBackend(Backend *toAdd);
  bool getClose() { return this->close; };
  void run(std::ostream &log);
  bool keyIsDown(int keycode) { return al_key_down(this->keyState, keycode); };
  double getFps() { return this->sets->fps; };
  void addEventCallback(ALLEGRO_EVENT_TYPE eventType,
                        void (*eventFunc)(ALLEGRO_EVENT, bool *));
  void addEventSource(ALLEGRO_EVENT_SOURCE *inSource);
};
}

#define ALHELP_IMPLEMENTATION // for linter in atom
#ifdef ALHELP_IMPLEMENTATION
// code
namespace alhelp {
void System::init() {
  if (!al_init()) {
    throw InitFail("al_init");
  }
  this->display =
      al_create_display(this->sets->displaySize.x, this->sets->displaySize.y);
  if (!this->display) {
    throw InitFail("al_create_display", this->sets->displaySize.toString());
  }
  this->queue = al_create_event_queue();
  if (!this->queue) {
    throw InitFail("al_create_event_queue");
  }
  if (!al_init_primitives_addon()) {
    throw InitFail("al_init_primitives_addon");
  }
  if (!al_install_keyboard()) {
    throw InitFail("al_install_keyboard");
  }
  try {
    this->keyState = new ALLEGRO_KEYBOARD_STATE;
  } catch (std::bad_alloc &ba) {
    throw InitFail("new", "ALLEGRO_KEYBOARD_STATE");
  }
  if (this->sets->fps <= 0) {
    throw InitFail("System()", "fps: " + std::to_string(this->sets->fps));
  }
  this->fpsTimer = al_create_timer(1.0 / this->sets->fps);
  if (!this->fpsTimer) {
    throw InitFail("al_create_timer", std::to_string(1.0 / this->sets->fps));
  }
  this->performanceTimer = al_create_timer((1.0 / this->sets->fps) / 10);
  if (!this->performanceTimer) {
    throw InitFail("al_create_timer",
                   std::to_string((1.0 / this->sets->fps) / 10));
  }
  al_register_event_source(this->queue,
                           al_get_display_event_source(this->display));
  al_register_event_source(this->queue,
                           al_get_timer_event_source(this->fpsTimer));
  al_register_event_source(this->queue, al_get_keyboard_event_source());
  al_start_timer(this->performanceTimer);
  al_start_timer(this->fpsTimer);
  al_clear_to_color(this->sets->clearColor.al_c());
  al_flip_display();
  this->initialized = true;
}
System::~System() {
  al_destroy_timer(this->fpsTimer);
  al_destroy_display(this->display);
  al_destroy_event_queue(this->queue);
}
std::shared_ptr<Backend> System::getBackend(std::string inID) {
  for (auto i = (this->backend).begin(); i != (this->backend).end(); i++) {
    if (i->get()->getID() == inID) {
      return *i;
    }
  }
  throw(IDFail(inID));
}
std::shared_ptr<Frontend> System::getFrontend(std::string inID) {
  for (auto i = (this->frontend).begin(); i != (this->frontend).end(); i++) {
    if (i->get()->getID() == inID) {
      return *i;
    }
  }
  throw(IDFail(inID));
}
void System::addFrontend(Frontend *toAdd) {
  if (this->isInitialized()) {
    throw InitFail("addFrontend");
  }
  if (this->frontend.empty()) {
    this->frontend.push_front(std::shared_ptr<Frontend>(toAdd));
    return;
  }
  auto i = (this->frontend).begin();
  for (; i != (this->frontend).end(); i++) {
    if (i->get()->getZIndex() > toAdd->getZIndex()) {
      this->frontend.insert(i, std::shared_ptr<Frontend>(toAdd));
    }
  }
  this->frontend.push_back(std::shared_ptr<Frontend>(toAdd));
}
void System::addBackend(Backend *toAdd) {
  if (this->isInitialized()) {
    throw InitFail("addBackend");
  }
  this->backend.push_back(std::shared_ptr<Backend>(toAdd));
}
void System::addEventSource(ALLEGRO_EVENT_SOURCE *inSource) {
  al_register_event_source(this->queue, inSource);
}

void System::addEventCallback(ALLEGRO_EVENT_TYPE eventType,
                              void (*eventFunc)(ALLEGRO_EVENT, bool *)) {
  this->eventTypes.push_back(eventType);
  this->eventFunctions.push_back(eventFunc);
}

void System::run(std::ostream &log) {
  ALLEGRO_EVENT ev;
  al_wait_for_event(this->queue, &ev);
  while (1) {
    bool caught = false;
    // Static events that never change
    if (ev.type == ALLEGRO_EVENT_TIMER) {
      if (ev.timer.source == this->fpsTimer) {
        this->redraw = true;
        caught = true;
      }
    } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      this->close = true;
      caught = true;
    }
    // If I need to close
    if (this->close) {
      return;
    }
    // If no static event has been found
    if (!caught) {
      auto type = this->eventTypes.begin();
      auto function = this->eventFunctions.begin();
      while (type != this->eventTypes.end()) {
        if (ev.type == *type) {
          (*function)(ev, &caught);
        }
        // If event has been caught
        if (caught) {
          // Stop checking dynamic events
          break;
        }
        type++;
        function++;
      }
    }
    if (al_get_next_event(this->queue, &ev) == false) {
      break;
    }
  }
  if (this->redraw) {
    al_get_keyboard_state(this->keyState);
    int countDelta = al_get_timer_count(this->performanceTimer) -
                     this->previousPerformanceCount;
    this->previousPerformanceCount = al_get_timer_count(this->performanceTimer);
    double delta = countDelta / 10.0;
    al_clear_to_color(this->sets->clearColor.al_c());
    for (auto i = this->backend.begin(); i != this->backend.end(); i++) {
      i->get()->run(delta);
    }
    for (auto i = this->frontend.begin(); i != this->frontend.end(); i++) {
      i->get()->run(delta);
      i->get()->draw();
    }
    al_flip_display();
    this->redraw = false;
  }
}
}

#endif // ALHELP_IMPLEMENTATION
#endif // HPP_ALHELP
