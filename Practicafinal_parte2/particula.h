#ifndef PARTICULA_H
#define PARTICULA_H

#include "Vector2.h"

class Particula {
public:
    Vector2 pos, vel;
    double masa, radio;
    double gravedad;
    bool activa;

    Particula(double x = 0, double y = 0, double vx = 0, double vy = 0, double m = 1, double r = 5);

    void mover(double dt);
    double velocidad() const { return vel.magnitude(); }
};

#endif
