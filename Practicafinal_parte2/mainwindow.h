#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include "GameWidget.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void alFinalizarJuego(int jugadorGanador);

private:
    GameWidget *game;
    int turno;
    int jugadorActual;

    QLabel *lblTurno;
    QLabel *lblJugador;

    void reiniciarJuego();
};

#endif
