#ifndef HPP_ALHELP
#define HPP_ALHELP
// header file
#include <string>

template <class T = float> class Vector {
public:
  T x;
  T y;
  Vector();
  Vector(T, T);
  std::string toString();

  Vector &operator+(Vector &vec);
  Vector &operator+=(Vector &vec);
  Vector &operator-(Vector &vec);
  Vector &operator-=(Vector &vec);
};

// #define ALHELP_IMPLEMENTATION
#ifdef ALHELP_IMPLEMENTATION
// code
template <class T> Vector<T>::Vector() : x(T(0)), y(T(0)){};
template <class T> Vector<T>::Vector(T inx, T iny) : x(T(inx)), y(T(iny)){};
template <class T> std::string Vector<T>::toString() {
  return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
};
template <class T> Vector<T> &Vector<T>::operator+(Vector &vec) {
  x += vec.x;
  y += vec.y;
  return *this;
};
template <class T> Vector<T> &Vector<T>::operator+=(Vector &vec) {
  x += vec.x;
  y += vec.y;
  return *this;
};
template <class T> Vector<T> &Vector<T>::operator-(Vector &vec) {
  x -= vec.x;
  y -= vec.y;
  return *this;
};
template <class T> Vector<T> &Vector<T>::operator-=(Vector &vec) {
  x -= vec.x;
  y -= vec.y;
  return *this;
};

#endif // ALHELP_IMPLEMENTATION
#endif // HPP_ALHELP
