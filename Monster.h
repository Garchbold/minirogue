//
//  Monster.h
//  MiniRogue
//
//  Created by George Archbold on 5/13/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__Monster__
#define __MiniRogue__Monster__

#include <stdio.h>
#include <stack>
#include "Actor.h"
#include "Player.h"
#include "Dungeon.h"

class Weapon;

class Monster : public Actor{
 
public:
    
    Monster(Dungeon *pp, int r, int c);
    ~Monster();
    
    virtual void move(char c);
    virtual bool canSmell();
    virtual void drop();
    
    char getType();
    void setType(char c);
    void setEquiped(Weapon* weapon);
    
    void attack(Actor* player);

    bool checkForItem();

    
    Point findPath(Point monster, Point player);
    char m_type;

    
private:

    Weapon* equiped;
    
};



#endif /* defined(__MiniRogue__Monster__) */
