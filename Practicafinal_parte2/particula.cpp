#include "particula.h"

Particula::Particula(double x, double y, double vx, double vy, double m, double r)
    : pos(x,y), vel(vx,vy), masa(m), radio(r), gravedad(9.8), activa(true) {}

void Particula::mover(double dt) {
    vel.y += gravedad * dt; // gravedad hacia +y (ajusta segun sistema de coordenadas)
    pos = pos + vel * dt;
}
