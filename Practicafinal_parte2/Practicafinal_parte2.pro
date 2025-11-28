QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    interfazjuego.cpp \
    simulador.cpp \
    particula.cpp \
    vector2.cpp \
    obstaculo.cpp

HEADERS += \
    mainwindow.h \
    interfazjuego.h \
    simulador.h \
    particula.h \
    vector2.h \
    obstaculo.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Sprites/bala4.png \
    ../Sprites/enemigo3.png \
    ../Sprites/fondo.avif \
    ../Sprites/fondo.jpg \
    ../Sprites/jugador3.png \
    multimedia/imagenes/bala.png \
    multimedia/imagenes/canon1.png \
    multimedia/imagenes/canon2.png \
    multimedia/imagenes/fondo.png \
    multimedia/imagenes/obs.jpg \
    multimedia/imagenes/obstaculo.png
