//
//  Player.h
//  MiniRogue
//
//  Created by George Archbold on 5/13/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__Player__
#define __MiniRogue__Player__

#include <stdio.h>
#include <vector>
#include "Actor.h"
#include "Dungeon.h"
#include "utilities.h"
#include "GameObject.h"

using namespace std;

class GameObject;
class Weapon;
class Monster;

class Player : public Actor {
    
public:
    
    Player(Dungeon *pp, int r, int c);
    ~Player();
    
    void move(char c);
    void attack(Actor* monster);
    bool checkForMonster(string dir);
    void printInventory();
    int  maxHealth();
    void setMaxHealth( int x);
    void setEquiped(Weapon*);
    
    vector<GameObject*> Inventory;
    
    
private:
    Weapon* equiped;
    int max_health;

};

#endif /* defined(__MiniRogue__Player__) */
