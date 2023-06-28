#ifndef GLOBAL_H
#define GLOBAL_H

// de Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsScale>
#include <QtWidgets/QDialog>
#include <QTimer>
#include <QIcon>
#include <QVBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QTextEdit>
#include <QKeyEvent>


// genèrics de C++
#include <vector>
#include <array>
#include <string>

// de l'aplicació
#include "compass.h"
#include "player.h"

// paràmetres gràfics
#define VIEW_WIDTH      1440    // 1440 amplada de la pantalla de joc
#define DIALOG_WIDTH    320     // 240 amplada del diàleg
#define VIEW_HEIGHT     800     // 800 alçada de la pantalla de joc
#define PIXMAP_WIDTH    20      // amplada de les icones dels jugadors
#define PIXMAP_HEIGHT   20      // alçada de les icones dels jugadors
#define PIXMAP_XFOCUS   (PIXMAP_WIDTH)    //((PIXMAP_WIDTH/2))    // per a la detecció dels jugadors dins l'escena
#define PIXMAP_YFOCUS   (PIXMAP_HEIGHT)  //((PIXMAP_HEIGHT/2))   // per a la detecció dels jugadors dins l'escena
#define PLAYER_XDRIFT   2 // 40 desplaçament a l'eix X
#define PLAYER_YDRIFT   2 // 40 desplaçament a l'eix Y

// temps d'autoactualització
#define GAME_WORLD_TIMER_TIME   40    // 100 milisegons

#define PLAYER_TYPE_1    0

// ecosistema del 'joc'
#define INITIAL_PLAYERS  48  // 48
#define MAX_PLAYERS      48  // 48

// generador de números aleatoris (min, max, jump)
int alNumGen (int, int, int);

#endif // GLOBAL_H
