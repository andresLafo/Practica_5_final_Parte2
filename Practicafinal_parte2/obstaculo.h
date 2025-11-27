#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Particula.h"

class Obstaculo {
public:
    double x, y, lado;
    double resistencia;

    Obstaculo(double x_=0, double y_=0, double lado_=10, double resistencia_=100);

    bool colisiona(const Particula& p) const;
    bool estaVivo() const { return lado > 0 && resistencia > 0; }
};

#endif
