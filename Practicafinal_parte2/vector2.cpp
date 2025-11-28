#include "Vector2.h"
#include <cmath>

Vector2::Vector2(double x_, double y_) : x(x_), y(y_) {}

Vector2 Vector2::operator+(const Vector2& v) const { return {x + v.x, y + v.y}; }
Vector2 Vector2::operator-(const Vector2& v) const { return {x - v.x, y - v.y}; }
Vector2 Vector2::operator*(double k) const { return {x * k, y * k}; }
double Vector2::magnitude() const { return sqrt(x*x + y*y); }
Vector2 Vector2::normalize() const {
    double mag = magnitude();
    return (mag != 0) ? Vector2(x/mag, y/mag) : Vector2(0,0);
}