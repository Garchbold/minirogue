//
//  SnakeWoman.cpp
//  MiniRogue
//
//  Created by George Archbold on 5/19/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#include "SnakeWoman.h"


SnakeWoman :: SnakeWoman(Dungeon *pp, int r, int c)
:Monster(pp, r, c)
{
    setHealth(3 + randInt(4));
    setDexterity(1);
    setSleep(0);
    setArmor(1);
    setStrength(3);
    setType('S');
    setEquiped(new MagicFangs(r,c));
    
}

SnakeWoman::~SnakeWoman(){
    
}

void SnakeWoman::drop(){
    
    //check for item then drop Magic Fangs
    if (!checkForItem()){
        if(trueWithProbability(.33)){
            dungeon()->object_vector.push_back(new MagicFangs(row(), col()));
        }
    }
}




