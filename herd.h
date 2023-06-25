#ifndef HERD_H
#define HERD_H

#include "player.h"
#include "compass.h"

class Herd
{   // herdKDTree;
int captureRadius=0;    // radi d'associació
int keepoutRadius=0;    // radi de seguretat
Compass compass;        // brúixola de la guia del ramat
//Kdtree* herdMembers=nullptr;    // membres del ramat, a actualitzar quan
                                  // hagi acabat amb la classe Kdtree
std::vector<Player*> members;   // el membre 0 és el cap del ramat!
                                // caldrà buscar una estructura més eficient per a la gestió de 'grups dinàmics'

public:

    Herd();
    void setCaptireRadius(int newradius){captureRadius=newradius;};
    int getCaprureRadius(){return captureRadius;};
    void setkeepoutRadius(int newkeepoutradius){keepoutRadius=newkeepoutradius;};
    int getKeepoutRadius(){return keepoutRadius;};
    bool setLeader(Player*);
    bool getLeader(Player*);
    bool replaceLeader(Player*);
    bool addleader(Player*);
    bool delLeader(Player*);
    bool addMember(Player*);
    bool delMember(Player*);
    bool replaceMember(Player*);
};

#endif // HERD_H
