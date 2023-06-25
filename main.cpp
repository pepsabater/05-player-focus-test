#include "global.h"
#include "mygameview.h"
#include "gamecontrol.h"

int main(int argc, char *argv[])
{
    // crea l'aplicació Qt
    // cal fer-ho abans de les inicialitzacions per dependències internes a les classes de Qt
    QApplication gameApp(argc, argv);
    // crea una escena, una vista gràfica
    QGraphicsScene gameScene;   // escenari
    GameView gameView;          // la vista, finestra principal
    // crea el control de joc, l'inicialitza i el presenta
    GameController gameControl (&gameScene, &gameView);    // control del joc
    gameControl.gSetInit();
    gameControl.gSetTheatre();
    // mostra la finestra
    gameView.show();

    return gameApp.exec();
}

