#ifndef HPP_ALHELP
#define HPP_ALHELP
// header file
#include <allegro5/allegro.h>
#include <string>

namespace alhelp {
template <class T = float> class Vector {
public:
  T x;
  T y;
  Vector();
  Vector(T, T);
  void normalize();
  std::string toString();

  Vector &operator+(const Vector &vec); // add
  Vector &operator+(const Vector vec);
  Vector &operator+=(const Vector &vec);
  Vector &operator+=(const Vector vec);
  Vector &operator*(const Vector &vec); // multiply
  Vector &operator*(const Vector vec);
  Vector &operator*=(const Vector &vec);
  Vector &operator*=(const Vector vec);
  Vector &operator-(const Vector &vec); // subtract
  Vector &operator-(const Vector vec);
  Vector &operator-=(const Vector &vec);
  Vector &operator-=(const Vector vec);
  Vector &operator/(const Vector &vec); // divide
  Vector &operator/(const Vector vec);
  Vector &operator/=(const Vector &vec);
  Vector &operator/=(const Vector vec);
  bool operator==(const Vector &vec); // equals
  bool operator==(const Vector vec);
  bool operator>=(const Vector &vec); // gt eq
  bool operator>=(const Vector vec);
  bool operator<=(const Vector &vec); // lt eq
  bool operator<=(const Vector vec);
  bool operator>(const Vector &vec); // gt
  bool operator>(const Vector vec);
  bool operator<(const Vector &vec); // lt
  bool operator<(const Vector vec);
  Vector &operator=(const Vector);
};
class System {
private:
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *queue = NULL;
  ALLEGRO_COLOR clearcl;

public:
  System();
};
}

#define ALHELP_IMPLEMENTATION // for linter in atom
#ifdef ALHELP_IMPLEMENTATION
// code
namespace alhelp {
// Damn vector shit
template <class T> Vector<T>::Vector() : x(T(0)), y(T(0)){};
template <class T> Vector<T>::Vector(T inx, T iny) : x(T(inx)), y(T(iny)){};
template <class T> std::string Vector<T>::toString() {
  return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
};
template <class T> void Vector<T>::normalize() {
  T mag = sqrt((this->x * this->x) + (this->y * this->y));
  this->x /= mag;
  this->y /= mag;
}
template <class T>
Vector<T> &Vector<T>::operator+(const Vector &vec) { // addition
  this->x += vec.x;
  this->y += vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator+(const Vector vec) {
  this->x += vec.x;
  this->y += vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator+=(const Vector &vec) {
  this->x += vec.x;
  this->y += vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator+=(const Vector vec) {
  this->x += vec.x;
  this->y += vec.y;
  return *this;
}
template <class T>
Vector<T> &Vector<T>::operator*(const Vector &vec) { // aultip
  this->x *= vec.x;
  this->y *= vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator*(const Vector vec) {
  this->x *= vec.x;
  this->y *= vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator*=(const Vector &vec) {
  this->x *= vec.x;
  this->y *= vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator*=(const Vector vec) {
  this->x *= vec.x;
  this->y *= vec.y;
  return *this;
}
template <class T>
Vector<T> &Vector<T>::operator-(const Vector &vec) { // subtract
  this->x -= vec.x;
  this->y -= vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator-(const Vector vec) {
  this->x -= vec.x;
  this->y -= vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator-=(const Vector &vec) {
  this->x -= vec.x;
  this->y -= vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator-=(const Vector vec) {
  this->x -= vec.x;
  this->y -= vec.y;
  return *this;
}
template <class T>
Vector<T> &Vector<T>::operator/(const Vector &vec) { // divide
  this->x /= vec.x;
  this->y /= vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator/(const Vector vec) {
  this->x /= vec.x;
  this->y /= vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator/=(const Vector &vec) {
  this->x /= vec.x;
  this->y /= vec.y;
  return *this;
}
template <class T> Vector<T> &Vector<T>::operator/=(const Vector vec) {
  this->x /= vec.x;
  this->y /= vec.y;
  return *this;
}
template <class T> bool Vector<T>::operator==(const Vector &vec) { // eq
  return (this->x == vec.x) && (this->y == vec.y);
}
template <class T> bool Vector<T>::operator==(const Vector vec) {
  return (this->x == vec.x) && (this->y == vec.y);
}
template <class T> bool Vector<T>::operator>=(const Vector &vec) { // gt eq
  return (this->x >= vec.x) && (this->y >= vec.y);
}
template <class T> bool Vector<T>::operator>=(const Vector vec) {
  return (this->x >= vec.x) && (this->y >= vec.y);
}
template <class T> bool Vector<T>::operator<=(const Vector &vec) { // lt eq
  return (this->x <= vec.x) && (this->y <= vec.y);
}
template <class T> bool Vector<T>::operator<=(const Vector vec) {
  return (this->x <= vec.x) && (this->y <= vec.y);
}
template <class T> bool Vector<T>::operator>(const Vector &vec) { // gt
  return (this->x > vec.x) && (this->y > vec.y);
}
template <class T> bool Vector<T>::operator>(const Vector vec) {
  return (this->x > vec.x) && (this->y > vec.y);
}
template <class T> bool Vector<T>::operator<(const Vector &vec) { // lt
  return (this->x < vec.x) && (this->y < vec.y);
}
template <class T> bool Vector<T>::operator<(const Vector vec) {
  return (this->x < vec.x) && (this->y < vec.y);
}
}

#endif // ALHELP_IMPLEMENTATION
#endif // HPP_ALHELP
