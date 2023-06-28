#include "global.h"
#include "gamecontrol.h"
#include <math.h>

GameController::GameController(QGraphicsScene* scene, GameView* view)
{
    // assignem l'escena i la vista heretades
    gameScene=scene;
    gameView=view;

    // connectem els events de teclat, les topades (col·lisions) i un temporitzador a la classe
    connect(view, SIGNAL(keyPressEvent(QKeyEvent*)), this, SLOT(touchMe(QKeyEvent*)));
    gameTamTam = new QTimer();
    connect(gameTamTam, SIGNAL(timeout()), this, SLOT(onTamTam()));

}

void GameController::gSetInit ()
{
    gameScene->setSceneRect(0,0,VIEW_WIDTH,VIEW_HEIGHT);
    gameView->setScene(gameScene);
    // fixa les mides i bloca els marcs
    gameView->setFixedSize(VIEW_WIDTH,VIEW_HEIGHT);
    gameView->setFrameStyle(0);
    // defineix la mida de l'escena
    gameScene->setSceneRect(0,0,VIEW_WIDTH,VIEW_HEIGHT);
    gameView->setStyleSheet("background-color:black;");
    gameView->setWindowTitle("player-focus-test");

    // programa el temporitzador
    gameTamTam->setInterval(GAME_WORLD_TIMER_TIME);
}

void GameController::gSetTheatre ()
{
    // crea un QPixmap amb la imatge de fons
//    gameBackImage=new QPixmap(backPixmapPath);
    // crea un pincell utilitzant el QPixmap com a textura
//    gameBrush=new QBrush(*gameBackImage);
    // estableix el pincell (brush) com a fons de l'escena
//    gameView->setBackgroundBrush(*gameBrush);
    // afegim els jugadors
    gMakePlayers(PLAYER_TYPE_1);
}

void GameController::gMakePlayers(int playertype)
{
int counter;
Player* newplayer=nullptr;

    if (playertype==PLAYER_TYPE_1)
        for (counter=0; counter<INITIAL_PLAYERS; counter++)
        {   // creem el jugador
            newplayer=new Player();

            if(counter==0)  // és el primer jugador
                // encenem el focus
                newplayer->setFocus();
            playerAdd(newplayer);
        }
}

void GameController::onTamTam()
{
static int playersCounter=0;

    if(playersCounter==1)
    {   // belluguem els jugadors, el jugador 0 ens el reservem pel control de teclat...
        playersCounter=0;
        playersMotion();
    }
    playersCounter++;
    sceneCollisions();
    if(playersPool.size()<2)
        gameTamTam->stop();

//    herdMotion();
}

void GameController::herdMotion()
{

}

void GameController::playersMotion()
{
int counter;

    for (counter=0; (unsigned long)counter < playersPool.size(); counter++)
    {   // movem els jugadors
        if ( playersPool[counter]->isActive()==true
             && playersPool[counter]->getStatus() == PLAYER_STATUS_LIVE
             && playersPool[counter]->isOnPlay()==true)
            // forcem un moviment aleatori, per ara
            playerMove(playersPool[counter], ((alNumGen(0,3,1) < 3)? PLAYER_ACTION_GO : alNumGen(0, 2, 1)));
    }
}

//---------------------
// belluga el jugador
//---------------------

bool GameController::playerMove (Player* player, int action)
{
bool retval=false;

    // si és un jugador vàlid
    if (player!=nullptr)
    {   // hi haurà moviment
        retval=true;
        // mirem cap a on assenyala la bruïxola
        switch (action)
        {   // i n'adjustem les noves coordinades
        case PLAYER_ACTION_GO:
            playerGo(player);
            break;
        case PLAYER_ACTION_REVERSE:
            playerGoReverse(player);
            break;
        case PLAYER_ACTION_TLEFT:
            playerGoLeft(player);
            break;
        case PLAYER_ACTION_TRIGHT:
            playerGoRight(player);
            break;
        case PLAYER_ACTION_WAIT:
            break;
        default:    // no sap on vol anar!
            retval=false;
        }
    }
    return retval;
}

//-----------------------
// el jugador va endavant
//-----------------------

void GameController::playerGo(Player* player)
{
int newxpos=0;
int newypos=0;

    if (player==nullptr)
        return;

    // enregistrem la seva posicio
    newxpos=player->getXPos();
    newypos=player->getYPos();

    switch(player->getCompass())
    {   // recalculem la posició segon la brúixola
    case COMPASS_N:
        newypos-=PLAYER_XDRIFT;
        break;
    case COMPASS_NE:
        newxpos+=PLAYER_XDRIFT;
        newypos-=PLAYER_YDRIFT;
        break;
    case COMPASS_E:
        newxpos+=PLAYER_XDRIFT;
        break;
    case COMPASS_SE:
        newxpos+=PLAYER_XDRIFT;
        newypos+=PLAYER_YDRIFT;
        break;
    case COMPASS_S:
        newypos+=PLAYER_YDRIFT;
        break;
    case COMPASS_SW:
        newxpos-=PLAYER_XDRIFT;
        newypos+=PLAYER_YDRIFT;
        break;
    case COMPASS_W:
        newxpos-=PLAYER_XDRIFT;
        break;
    case COMPASS_NW:
        newxpos-=PLAYER_XDRIFT;
        newypos-=PLAYER_YDRIFT;
        break;
    default:
        break;
    }

    // si la nova posició és fora d'escena...
    if ((newxpos < 0 || newxpos > VIEW_WIDTH-PIXMAP_WIDTH)
        || (newypos < 0 || newypos > VIEW_HEIGHT-PIXMAP_HEIGHT))
        // fem màgia!
        switch (player->getCompass())
        {
        case COMPASS_N:
            newypos = VIEW_HEIGHT - PIXMAP_HEIGHT;
            break;
        case COMPASS_NE:
            if (newxpos + PIXMAP_WIDTH >= VIEW_WIDTH - PIXMAP_WIDTH)
                newxpos = 0;

            if (newypos - PIXMAP_HEIGHT <= 0 )
                newypos = VIEW_HEIGHT - PIXMAP_HEIGHT;
            break;
        case COMPASS_E:
            newxpos = 0;
            break;
        case COMPASS_SE:
            if (newxpos + PIXMAP_WIDTH >= VIEW_WIDTH - PIXMAP_WIDTH)
                newxpos = 0;

            if (newypos + PIXMAP_HEIGHT >= VIEW_HEIGHT - PIXMAP_HEIGHT)
                newypos = 0;
            break;
        case COMPASS_S:
            newypos = 0;
            break;
        case COMPASS_SW:
            if (newxpos - PIXMAP_WIDTH <= 0)
                newxpos = VIEW_WIDTH - PIXMAP_WIDTH;

            if (newypos + PIXMAP_HEIGHT >= VIEW_HEIGHT - PIXMAP_HEIGHT)
                newypos = 0;
            break;
        case COMPASS_W:
            newxpos = VIEW_WIDTH - PIXMAP_WIDTH;
            break;

        case COMPASS_NW:
            if (newxpos - PIXMAP_WIDTH <= 0)
                newxpos = VIEW_WIDTH - PIXMAP_WIDTH;

            if (newypos - PIXMAP_HEIGHT <= 0)
                newypos = VIEW_HEIGHT - PIXMAP_HEIGHT;
            break;
        }
    player->setPos(newxpos, newypos);
}

//--------------------------------
// el jugador tomba a l'esquerra
//--------------------------------

void GameController::playerGoLeft(Player* player)
{
int leftDir;

    if (player!=nullptr)
    {   // un tomb a l'esquerra tanca l'angle
        leftDir=player->getCompass() - 1;
        (leftDir < 0)? player->setCompass(COMPASS_STEPS - 1) : player->setCompass(leftDir);
        player->pointTo();
        playerRotation(player);
    }
}

//----------------------
// el jugador gira cua
//----------------------

void GameController::playerGoReverse(Player* player)
{
int newDir;

    if (player!=nullptr)
    {
        newDir=player->getCompass() + COMPASS_STEPS/2;
        (newDir >= COMPASS_STEPS)? player->setCompass(newDir-COMPASS_STEPS) : player->setCompass(newDir);
        player->pointTo();
        playerRotation (player);
    }
}

//----------------------------
// el jugador tomba a la dreta
//----------------------------
void GameController::playerGoRight(Player* player)
{
int rightDir;

    if (player!=nullptr)
    {   // un tomb a la dreta obre l'angle
        rightDir=player->getCompass() + 1;
        (rightDir >= COMPASS_STEPS)? player->setCompass(0) : player->setCompass(rightDir);
        player->pointTo();
        playerRotation(player);
    }
}

//----------------------------------------
// afegueix el jugador i l'hi busca lloc
//----------------------------------------
// fa servir el vector de jugadors
bool GameController::playerAdd(Player* newplayer)
{
bool retval=false;
Player* foundplayer;

    if (newplayer!=nullptr)
    {   // assignem una direcció aleatòria
        newplayer->setCompass(alNumGen(0,COMPASS_STEPS,1));
        newplayer->pointTo();
        playerRotation(newplayer);
        // afegim el jugador a la llista de jugadors
        playersPool.push_back(newplayer);
        // per raons d'estética s'enregistra primer el 'focus'
        if(newplayer->getFocusItem()!=nullptr)
            gameScene->addItem(newplayer->getFocusItem());
        // i després el jugador
        gameScene->addItem(newplayer->getPixmap());

        do
        {   // el busquem un lloc a l'escena, repetim fins trobar-ne un de lliure
            if (playersPool.size()>1)
                newplayer->setPos(alNumGen(0,VIEW_WIDTH-PIXMAP_WIDTH,PLAYER_XDRIFT),alNumGen(0,VIEW_HEIGHT-PIXMAP_HEIGHT,PLAYER_YDRIFT));
            else
                newplayer->setPos(VIEW_WIDTH/2, VIEW_HEIGHT/2);
            // i mirem si el lloc és ple
            foundplayer=playerCollision(newplayer);
            // si no n'ha trobat cap, sortim
            if (foundplayer!=newplayer)
                break;
        } while (true);
        retval=true;
    }
    return retval;
}

//-----------------------------------------------
// control del joc per teclat (per proves)
//-----------------------------------------------

void GameController::touchMe (QKeyEvent* keyEvent)
{
static Player* gamePlayer0=nullptr;
int playerAction=0;

    if(gamePlayer0 == nullptr)
    {
        gamePlayer0=playerFinder(PLAYER_TYPE_1);

        if (gamePlayer0 == nullptr)
            return;
    }

    switch (keyEvent->key())
    {
    case Qt::Key_Up:
        playerAction=PLAYER_ACTION_GO;
        break;
    case Qt::Key_Left:
        playerAction=PLAYER_ACTION_TLEFT;
        break;
    case Qt::Key_Down:
        playerAction=PLAYER_ACTION_REVERSE;
        break;
    case Qt::Key_Right:
        playerAction=PLAYER_ACTION_TRIGHT;
        break;
    case Qt::Key_F:
        static bool focusonoff=false;
        focusonoff^=true;
        playersPool[0]->setFocusOnOff(focusonoff);
        break;
    case Qt::Key_Space: // arrenca/atura el temporitzador
//            gamePlayer0->setCompass(COMPASS_N);
//            gamePlayer0->pointToCompass();
        (gameTamTam->isActive()==true)? gameTamTam->stop(): gameTamTam->start();
    default:
        return;
    }
    playerMove(gamePlayer0, playerAction);
}

//-----------------------------------------------
// dibuixem el jugador
//-----------------------------------------------
// si rotation = true, és que cal girar-lo
// si rotation = false, és un desplaçament lineal
//-----------------------------------------------

void GameController::playerRotation(Player *player)
{
QGraphicsPixmapItem* pixmap;
QGraphicsEllipseItem* focusitem;
int compassangle;

    if (player==nullptr || player->getPixmap() == nullptr)
        return;

    pixmap=player->getPixmap();
    focusitem=player->getFocusItem();
    compassangle=player->getCompassAngle();

    // fixem el punt de gir fem la rotació
    pixmap->setTransformOriginPoint(pixmap->boundingRect().center());
    pixmap->setRotation(compassangle);

    if (focusitem!=nullptr)
    {   // ara pel focus // +cos(player->getFocusSpanAngle()*PIXMAP_WIDTH)
        focusitem->setTransformOriginPoint(focusitem->rect().center());
        focusitem->setRotation(compassangle);
    }
}

Player* GameController::playerFinder(int playerType)
{
int counter;
Player* foundPlayer=nullptr;

    for (counter=0; (unsigned long)counter<playersPool.size(); counter++)
        if (playersPool[counter]->getType()==playerType)
        {
            foundPlayer = playersPool[counter];
            break;
        }
    return foundPlayer;
}

Player* GameController::playerFinder(int xpos, int ypos)
{
int counter;
Player* foundPlayer=nullptr;

    for (counter=0; (unsigned long)counter<playersPool.size(); counter++)
    {
        if (playersPool[counter]->getXPos()==xpos && playersPool[counter]->getYPos()==ypos)
        {
            foundPlayer = playersPool[counter];
            break;
        }
    }
    return foundPlayer;
}

Player* GameController::playerCollision(Player* player)
{
int counter;
Player* foundPlayer=nullptr;

    for (counter=0; (unsigned long)counter<playersPool.size(); counter++)
    {
        if (playersPool[counter]!=player)
        {
            foundPlayer = playersPool[counter];
            break;
        }
/*        else
        {
            if (playersPool[counter]->getCaptureCircle()!= nullptr)
                counter++;

            if (playersPool[counter]->getKeepoutCircle()!= nullptr)
                counter++;
        } */
    }
    return foundPlayer;
}

void GameController::sceneCollisions()
{
QList<QGraphicsItem*> playerslist;
QGraphicsPixmapItem* pixmapitem=nullptr;
Player* delplayer;

    playerslist=gameScene->collidingItems(playersPool[0]->getFocusItem());

    // si hi ha algú més que el punter i el focus del primer jugador
    if (playerslist.size()>1)
    {   // el primer de la llista és l'ultim que ha arribat
        pixmapitem=(QGraphicsPixmapItem*)playerslist[0];
        // ens el petem
        gameScene->removeItem(pixmapitem);
        delplayer=playerFinder(pixmapitem->pos().x(), pixmapitem->pos().y());

        for (int counter=0; (unsigned int)counter < playersPool.size(); counter++)
            if (delplayer==playersPool[counter])
            {
                playersPool.erase(playersPool.begin() + counter);
            }
        delete delplayer;
    }
}
