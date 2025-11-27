#include "Obstaculo.h"

Obstaculo::Obstaculo(double x_, double y_, double lado_, double resistencia_)
    : x(x_), y(y_), lado(lado_), resistencia(resistencia_) {}

bool Obstaculo::colisiona(const Particula& p) const {
    if (!estaVivo()) return false;
    return (p.pos.x >= x && p.pos.x <= x + lado &&
            p.pos.y >= y && p.pos.y <= y + lado);
}
