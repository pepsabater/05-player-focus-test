#include "kdtree.h"

Kdtree::Kdtree()
{

}

Kdnode::Kdnode()
{

}

bool Kdnode::setNodePlayer(Player* player)
{
    if (player == nullptr || nodePlayer != nullptr)
        return false;

    nodePlayer = player;
    return true;
}

Kdnode* Kdnode::getChildByNumber(unsigned long childnum)
{
    if((unsigned long)childnum < nodeChilds.size())
        return nodeChilds[childnum];

    return nullptr;
}

Kdnode* Kdnode::getChildByPlayer(Player* player)
{
int counter;

    if (player == nullptr)
        return nullptr;

    for (counter = 0; (unsigned long)counter < nodeChilds.size(); counter ++)
        if (nodeChilds[counter]->nodePlayer == player)
        {
            targetChild=counter;
            return nodeChilds[targetChild];
        }

    return nullptr;
}

Kdnode* Kdnode::getCurrentChild()
{
    if (targetChild >= 0)
        return nodeChilds[targetChild];

    return nullptr;
}

Kdnode* Kdnode::getFirstChild()
{
    if (nodeChilds.size() > 0)
    {
        targetChild = 0;
        return nodeChilds[targetChild];
    }

    return nullptr;
}

Kdnode* Kdnode::getLastChild()
{
    if (nodeChilds.size() > 0)
    {
        targetChild = nodeChilds.size() - 1;
        return nodeChilds[targetChild];
    }

    return nullptr;
}

Kdnode* Kdnode::getNextChild()
{
    if (targetChild >= 0 && (unsigned long)(targetChild + 1) < nodeChilds.size())
    {
        targetChild++;
        return nodeChilds[targetChild];
    }

    return nullptr;
}

bool Kdnode::addChild(Player* player)
{
    if (player != nullptr)
    {
        Kdnode* newNode = new Kdnode();

        if (newNode != nullptr)
        {
            nodeChilds.push_back(newNode);
            targetChild = nodeChilds.size() - 1;
            return true;
        }
    }
    return false;
}

bool Kdnode::delChildByNumber(unsigned long childnum)
{
    return false;
}

void Kdnode::delChildByNode(Kdnode* childnode)
{

}

void Kdnode::delChildByPlayer(Player* childplayer)
{

}
