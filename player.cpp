#include "global.h"
#include "player.h"

Player::Player()
{
    // característiques i estats
    type=PLAYER_TYPE_1;
    status=PLAYER_STATUS_LIVE;
    active=true;
    onPlay=true;
    onHerd=false;
    // aparença de focus
    playerFace.pixmapPath = "../imatges/arrow-lgreen20.png";
    playerFace.pixmap=new QGraphicsPixmapItem(QPixmap(playerFace.pixmapPath));


    // posicionament i orientació
    compass.setPos(0, 0);
    compass.setSense(COMPASS_N);
};

Player::~Player()
{   // focus
    delete playerFace.focusItem;
    delete playerFace.focusBrush;
    delete playerFace.focusColor;
    delete playerFace.pixmap;
}

void Player::setFocus()
{    // pincell
    playerFace.focusColor = new QColor(0xaa,0xff,0xff);
    playerFace.focusColor->setAlpha(96);
    playerFace.focusBrush = new QBrush(*playerFace.focusColor);
    // focus
    playerFace.focusRadius=PLAYER_CAPTURE_RADIUS;
    playerFace.focusStartAngle=PLAYER_FOCUS_START;
    playerFace.focusSpanAngle=PLAYER_FOCUS_SPAN;
    playerFace.focusItem = new QGraphicsEllipseItem(0, 0, playerFace.focusRadius, playerFace.focusRadius);
    playerFace.focusItem->setBrush(*playerFace.focusBrush);
    playerFace.focusItem->setStartAngle(PLAYER_FOCUS_START*16); // clock wise!! 0 = East
    playerFace.focusItem->setSpanAngle(PLAYER_FOCUS_SPAN*16);   // counterclock wise!!
}

void Player::setPos(int xpos, int ypos)
{
    compass.setXPos(xpos);
    compass.setYPos(ypos);

    if (playerFace.pixmap!=nullptr)
        playerFace.pixmap->setPos(xpos, ypos);

    if (playerFace.focusItem!=nullptr)
        playerFace.focusItem->setPos(xpos-(playerFace.focusRadius/2)+(PIXMAP_WIDTH/2),
                                     ypos-(playerFace.focusRadius/2)+(PIXMAP_HEIGHT/2));
}
