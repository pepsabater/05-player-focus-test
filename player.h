#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"

// si belluga i interacciona directament
#define PLAYER_MODE_STATIC    0 // no es mou per l'escena
#define PLAYER_MODE_DYNAMIC   1 // es mou per l'escena

#define PLAYER_STATUS_DEAD    0 // és mort
#define PLAYER_STATUS_LIVE    1 // és viu

// accions i esdeveniments
#define PLAYER_ACTION_GO        0   // anar endavant
#define PLAYER_ACTION_TLEFT     1   // tombrar a l'esquerra
#define PLAYER_ACTION_TRIGHT    2   // tombar a la dreta
#define PLAYER_ACTION_REVERSE   3   // girar cua
#define PLAYER_ACTION_WAIT      4   // esperar-se
#define PLAYER_ACTIONS          5   // nombre d'accions

#define PLAYER_CAPTURE_RADIUS   200
#define PLAYER_KEEPOUT_RADIUS   40
#define PLAYER_FOCUS_START      60
#define PLAYER_FOCUS_SPAN       60

struct PlayerAspect
{   // imatge associada
QGraphicsPixmapItem* pixmap=nullptr;
QGraphicsEllipseItem* focusItem=nullptr;
QColor* focusColor=nullptr;
QBrush* focusBrush=nullptr;
int focusRadius;
int focusStartAngle;
int focusSpanAngle;
QString pixmapPath;
};

class Player 
{
protected:
// característiques i estats
int type;       // de quina mena és
int status;     // estat
bool active;    // si és dinàmic o estàtic
bool onPlay;    // si hi és al joc o no
bool onHerd;    // si és part del ramat

// control de posició i orientació
Compass compass;
struct PlayerAspect playerFace;

public:

    Player();
    ~Player();
    // característiques i estats   
    int getType(){return type;};
    int getStatus(){return status;};
    bool isActive(){return active;};
    bool isOnPlay(){return onPlay;};
    // aparença
    QGraphicsPixmapItem* getPixmap(){return playerFace.pixmap;};

    // posicionament i orientació
    void pointTo(){compass.pointTo();};

    // focus
    QGraphicsEllipseItem* getFocusItem(){return playerFace.focusItem;};
    void setFocus();
    void setFocusOnOff(bool bfocus){playerFace.focusColor->setAlpha((bfocus==true)? 48 : 0);
                                    playerFace.focusBrush->setColor(*playerFace.focusColor);
                                    playerFace.focusItem->setBrush(*playerFace.focusBrush);};
    int getFocusRadius(){return playerFace.focusRadius;};
    int getFocusSpanAngle(){return playerFace.focusSpanAngle;};
    int getCompassAngle(){return compass.getCompassAngle();};
    void setPos(int, int);
    void setXPos (int xpos){compass.setXPos(xpos);};
    int getXPos(){return compass.getXPos();};
    void setYPos (int ypos){compass.setYPos(ypos);};
    int getYPos(){return compass.getYPos();};
    void setCompass(int direction){compass.setSense(direction);};
    int getCompass(){return compass.getSense();};
};

#endif // PLAYER_H
