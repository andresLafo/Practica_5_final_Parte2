#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2 {
    double x, y;
    Vector2(double x_=0, double y_=0);

    Vector2 operator+(const Vector2& v) const;
    Vector2 operator-(const Vector2& v) const;
    Vector2 operator*(double k) const;

    double magnitude() const;
    Vector2 normalize() const;
};

#endif