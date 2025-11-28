#ifndef INTERFAZJUEGO_H
#define INTERFAZJUEGO_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include "Simulador.h"
#include "Obstaculo.h"

class InterfazJuego : public QWidget {
    Q_OBJECT

signals:
    void juegoTerminado(int jugadorGanador);
    void finProyectil();   // Turno finalizado

public:
    explicit InterfazJuego(QWidget *parent = nullptr);

    void disparar(double angulo, double velocidad, int jugador);
    void reiniciarSimulacion();
    void establecerJugadorActual(int jugador);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void actualizar();

private:
    Simulador sim;
    QTimer temporizador;

    double escala;
    double dt;
    int framesSinProyectil;

    double posCanon1X, posCanon1Y;
    double posCanon2X, posCanon2Y;

    QPixmap fondo;
    QPixmap texturaObstaculo;
    QPixmap canonIzq;
    QPixmap canonDer;
    QPixmap texturaProyectil;

    double anguloActual;
    double velocidadActual;
    int jugadorActual;

    bool verificarVictoria();
    double tiempoProyectil;
    double tiempoMaximo;     // duración del disparo
    bool disparoEnCurso;

};

#endif // INTERFAZJUEGO_H
