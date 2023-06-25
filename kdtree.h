#ifndef KDTREE_H
#define KDTREE_H

#include "global.h"

class Kdnode
{
int headDistance=-1;        // distància al primer node, Euklides!!
int parentDistance=-1;      // distància al node anterior, Euklides!!
Player* nodePlayer=nullptr;
std::vector<Kdnode*>nodeChilds;
long targetChild=-1;

public:

    Kdnode();
    bool setNodePlayer(Player*);
    Player* getNodePlayer(){return nodePlayer;};
    int getChildrens(){return nodeChilds.size();};
    Kdnode* getChildByNumber(unsigned long);
    Kdnode* getChildByPlayer(Player*);
    Kdnode* getCurrentChild();
    Kdnode* getFirstChild();
    Kdnode* getLastChild();
    Kdnode* getNextChild();
    bool addChild(Player*);
    bool delChildByNumber(unsigned long);
    void delChildByNode(Kdnode*);
    void delChildByPlayer(Player*);
};

class Kdtree
{

Kdnode* firstNode=nullptr;  // punt d'entrada
int nodes=0;                // n. de nodes actual

public:

    Kdtree();
    bool setFirstNode(Kdnode*);
    Kdnode* getFirstNode(){return firstNode;};
    int getNodes(){return nodes;};
};

#endif // KDTREE_H
