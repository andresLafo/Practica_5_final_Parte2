#include "Simulador.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Simulador::Simulador(double ancho_, double alto_, double coef_rest)
    : ancho(ancho_), alto(alto_), c(coef_rest), K_dano(0.05) {}

void Simulador::agregarParticula(const Particula& p) { particulas.push_back(p); }
void Simulador::limpiarParticulas() { particulas.clear(); }
void Simulador::agregarObstaculo(const Obstaculo& o) { obstaculos.push_back(o); }

void Simulador::colisionesPared(Particula& p) {
    // paredes verticales x=0 y x=ancho
    if (p.pos.x - p.radio <= 0) {
        p.pos.x = p.radio;
        p.vel.x *= -1;
    } else if (p.pos.x + p.radio >= ancho) {
        p.pos.x = ancho - p.radio;
        p.vel.x *= -1;
    }

    // paredes horizontales y=0 y y=alto
    if (p.pos.y - p.radio <= 0) {
        p.pos.y = p.radio;
        p.vel.y *= -1;
    } else if (p.pos.y + p.radio >= alto) {
        p.pos.y = alto - p.radio;
        p.vel.y *= -1;
    }
}

void Simulador::colisionesObstaculos(Particula& p) {
    for (auto& o : obstaculos) {
        if (!o.estaVivo()) continue;
        if (o.colisiona(p)) {
            // Momento lineal
            double momento = p.masa * p.vel.magnitude();
            double dano = K_dano * momento;
            o.resistencia -= dano;
            std::cout << "Daño inflicted: " << dano << " | Resistencia restante: " << o.resistencia << "\n";

            if (o.resistencia <= 0) {
                // marcar como destruido
                o.lado = 0;
                continue;
            }

            // Rebote inelástico: decidir segun lado de choque
            double dxL = fabs(p.pos.x - o.x);
            double dxR = fabs(p.pos.x - (o.x + o.lado));
            double dyT = fabs(p.pos.y - o.y);
            double dyB = fabs(p.pos.y - (o.y + o.lado));
            double minD = std::min(std::min(dxL, dxR), std::min(dyT, dyB));

            if (minD == dxL || minD == dxR)
                p.vel.x *= -c;
            else
                p.vel.y *= -c;
        }
    }
}

void Simulador::colisionesParticulas() {
    for (size_t i = 0; i < particulas.size(); ++i) {
        for (size_t j = i + 1; j < particulas.size(); ++j) {
            Particula& A = particulas[i];
            Particula& B = particulas[j];

            if (!A.activa || !B.activa) continue;

            double dist = (A.pos - B.pos).magnitude();
            if (dist <= A.radio + B.radio) {
                // fusion simple
                double M = A.masa + B.masa;
                double vxf = (A.vel.x*A.masa + B.vel.x*B.masa) / M;
                double vyf = (A.vel.y*A.masa + B.vel.y*B.masa) / M;
                double xf = (A.pos.x*A.masa + B.pos.x*B.masa) / M;
                double yf = (A.pos.y*A.masa + B.pos.y*B.masa) / M;

                A.pos = {xf, yf};
                A.vel = {vxf, vyf};
                A.masa = M;
                A.radio = sqrt(A.radio*A.radio + B.radio*B.radio);
                B.activa = false;
            }
        }
    }
}

void Simulador::step(double dt) {
    // mover particulas
    for (auto& p : particulas) {
        if (!p.activa) continue;
        p.mover(dt);
        colisionesPared(p);
        colisionesObstaculos(p);
    }
    colisionesParticulas();


}