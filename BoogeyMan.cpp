//
//  BoogeyMan.cpp
//  MiniRogue
//
//  Created by George Archbold on 5/24/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#include "BoogeyMan.h"

BoogeyMan :: BoogeyMan(Dungeon *pp, int r, int c)
:Monster(pp, r, c)
{
    setHealth(5 + randInt(6));
    setDexterity(2 + randInt(2));
    setSleep(0);
    setArmor(2);
    setStrength(2 + randInt(2));
    setType('B');
    
    setEquiped(new ShortSword(r,c));
    
}

BoogeyMan::~BoogeyMan(){
    
}

void BoogeyMan::drop(){
    
    //check for item and drop MagicAxe
    if (!checkForItem()){
        if(trueWithProbability(.1)){
            dungeon()->object_vector.push_back(new MagicAxe(row(), col()));
        }
    }
}

