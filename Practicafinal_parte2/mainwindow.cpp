#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), jugadorActual(1), turno(1)
{
    game = new InterfazJuego(this);

    lblJugador = new QLabel("Jugador actual: 1", this);
    lblTurno   = new QLabel("Turno: 1", this);

    connect(game, &InterfazJuego::juegoTerminado, this, &MainWindow::alFinalizarJuego);

    QVBoxLayout *controles = new QVBoxLayout;
    controles->addWidget(lblJugador);
    controles->addWidget(lblTurno);
    controles->addStretch();

    QHBoxLayout *layoutPrincipal = new QHBoxLayout;
    layoutPrincipal->addWidget(game, 1);
    layoutPrincipal->addLayout(controles);

    setLayout(layoutPrincipal);
    setWindowTitle("Juego de Artillería por Turnos - Qt");

    resize(900, 600);

    // El widget del juego debe saber quién es el jugador actual
    game->establecerJugadorActual(jugadorActual);
}

void MainWindow::alFinalizarJuego(int jugadorGanador)
{
    QMessageBox msg;
    msg.setWindowTitle("¡Juego Terminado!");
    msg.setText(QString("¡El Jugador %1 ha ganado en el turno %2!")
                    .arg(jugadorGanador)
                    .arg(turno));
    msg.setInformativeText("¿Quieres reiniciar el juego?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    int r = msg.exec();

    if (r == QMessageBox::Yes)
        reiniciarJuego();
    else
        QCoreApplication::quit();
}

void MainWindow::reiniciarJuego()
{
    jugadorActual = 1;
    turno = 1;

    lblJugador->setText("Jugador actual: 1");
    lblTurno->setText("Turno: 1");

    game->reiniciarSimulacion();
    game->establecerJugadorActual(1);
}
