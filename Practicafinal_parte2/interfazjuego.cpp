#include "interfazjuego.h"
#include <QPainter>
#include <QKeyEvent>
#include <cmath>
#include <algorithm>

InterfazJuego::InterfazJuego(QWidget *parent)
    : QWidget(parent),
    sim(500, 350, 0.6),
    escala(1.0),
    dt(0.016),
    framesSinProyectil(0),
    anguloActual(30.0),
    velocidadActual(120.0),
    jugadorActual(1)
{
    setMinimumSize(600, 450);

    connect(&temporizador, &QTimer::timeout, this, &InterfazJuego::actualizar);
    temporizador.start(int(dt * 1000));

    fondo = QPixmap(":/imagenes/multimedia/imagenes/fondo.png");
    texturaObstaculo = QPixmap(":/imagenes/multimedia/imagenes/obstaculo.png");
    canonIzq = QPixmap(":/imagenes/multimedia/imagenes/canon1.png");
    canonDer = QPixmap(":/imagenes/multimedia/imagenes/canon2.png");
    texturaProyectil = QPixmap(":/imagenes/multimedia/imagenes/bala.png");

    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    // Crear obstáculos (idéntico a tu versión)
    sim.obstaculos.clear();

    double colTam = 40.0;
    double techoTam = 100.0;
    double margen = 10.0;

    double baseY = sim.alto - colTam - margen;
    double topY  = baseY - techoTam;

    double xIzq = 80.0;
    double xDer = sim.ancho - xIzq - techoTam;

    // Fortaleza izquierda
    sim.agregarObstaculo(Obstaculo(xIzq, baseY, colTam, 200));
    sim.agregarObstaculo(Obstaculo(xIzq + techoTam - colTam, baseY, colTam, 200));
    sim.agregarObstaculo(Obstaculo(xIzq, topY, techoTam, 100));

    // Fortaleza derecha
    sim.agregarObstaculo(Obstaculo(xDer, baseY, colTam, 200));
    sim.agregarObstaculo(Obstaculo(xDer + techoTam - colTam, baseY, colTam, 200));
    sim.agregarObstaculo(Obstaculo(xDer, topY, techoTam, 100));

    posCanon1X = xIzq - 25.0;
    posCanon1Y = topY - 20.0;

    posCanon2X = xDer + techoTam + 25.0;
    posCanon2Y = posCanon1Y;
}

void InterfazJuego::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        anguloActual = std::min(90.0, anguloActual + 1.0);
        break;

    case Qt::Key_S:
        anguloActual = std::max(0.0, anguloActual - 1.0);
        break;

    case Qt::Key_D:
        velocidadActual = std::min(300.0, velocidadActual + 2.0);
        break;

    case Qt::Key_A:
        velocidadActual = std::max(0.0, velocidadActual - 2.0);
        break;

    case Qt::Key_Space:
        disparar(anguloActual, velocidadActual, jugadorActual);
        break;
    }

    QWidget::keyPressEvent(event);
}

void InterfazJuego::disparar(double angulo, double velocidad, int jugador)
{
    double rad = angulo * M_PI / 180.0;

    double x0 = (jugador == 1) ? posCanon1X : posCanon2X;
    double y0 = (jugador == 1) ? posCanon1Y : posCanon2Y;

    double dir = (jugador == 1) ? 1.0 : -1.0;

    double vx = velocidad * std::cos(rad) * dir;
    double vy = -velocidad * std::sin(rad);

    sim.limpiarParticulas();
    Particula p(x0, y0, vx, vy, 4.0, 6.0);
    p.gravedad = 9.0;
    p.activa = true;

    sim.agregarParticula(p);
    framesSinProyectil = 0;

    if (!temporizador.isActive())
        temporizador.start(int(dt * 1000));
}

void InterfazJuego::actualizar()
{
    sim.step(dt);

    if (verificarVictoria()) {
        temporizador.stop();
        update();
        return;
    }

    bool activa = false;
    for (auto &p : sim.particulas)
        if (p.activa) activa = true;

    if (!activa)
        framesSinProyectil++;

    if (framesSinProyectil > 5) {
        emit finProyectil();
        framesSinProyectil = -100;
    }

    update();
}

bool InterfazJuego::verificarVictoria()
{
    int vivosIzq = 0;
    int vivosDer = 0;

    double mitad = sim.ancho / 2.0;

    for (const auto &o : sim.obstaculos) {
        if (!o.estaVivo()) continue;

        double centroX = o.x + o.lado / 2.0;

        if (centroX < mitad)
            vivosIzq++;
        else
            vivosDer++;
    }

    if (vivosDer == 0) {
        emit juegoTerminado(1);
        return true;
    }
    if (vivosIzq == 0) {
        emit juegoTerminado(2);
        return true;
    }

    return false;
}

void InterfazJuego::reiniciarSimulacion()
{
    sim.limpiarParticulas();
    framesSinProyectil = 0;

    // Recrear obstáculos
    // mismo código que el constructor…

    update();
}

void InterfazJuego::establecerJugadorActual(int jugador)
{
    jugadorActual = jugador;
}

void InterfazJuego::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    double sx = width() / sim.ancho;
    double sy = height() / sim.alto;
    double S = std::min(sx, sy);

    p.drawPixmap(rect(), fondo);

    // Obstáculos
    for (auto &o : sim.obstaculos) {
        if (!o.estaVivo()) continue;

        QRectF r(o.x*S, o.y*S, o.lado*S, o.lado*S);
        p.drawPixmap(r.toRect(), texturaObstaculo);

        p.setPen(Qt::black);
        p.drawText(r, Qt::AlignCenter, QString::number(int(o.resistencia)));
    }

    // Cañones
    QRectF c1((posCanon1X - 48)*S, (posCanon1Y - 48)*S, 96*S, 96*S);
    p.drawPixmap(c1.toRect(), canonIzq);

    QRectF c2((posCanon2X - 48)*S, (posCanon2Y - 48)*S, 96*S, 96*S);
    p.drawPixmap(c2.toRect(), canonDer);

    // Proyectil
    for (auto &pt : sim.particulas) {
        if (!pt.activa) continue;

        double px = pt.pos.x*S;
        double py = pt.pos.y*S;

        QRectF pr(px - 12, py - 12, 24, 24);
        p.drawPixmap(pr.toRect(), texturaProyectil);
    }
}
