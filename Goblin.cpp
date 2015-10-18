//
//  Goblin.cpp
//  MiniRogue
//
//  Created by George Archbold on 5/18/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#include "Goblin.h"


Goblin :: Goblin(Dungeon *pp, int r, int c)
:Monster(pp, r,c)
{
    setHealth(15 + randInt(5));
    setDexterity(1);
    setSleep(0);
    setArmor(1);
    setStrength(3);
    setType('G');
    
    setEquiped(new ShortSword(r,c));

    
}

Goblin::~Goblin(){
    
}

//same function as Monster.cpp however it has a larger smell range
bool Goblin::canSmell(){
    

    int r_distance = row() - dungeon()->player()->row();
    int c_distance = col() - dungeon()->player()->col();
    
    if(r_distance < 0)
        r_distance = -r_distance;
    
    if(c_distance < 0)
        c_distance = -c_distance;
    
    if (r_distance + c_distance < 15) {
        return true;
    }
    else
        return false;
}

void Goblin::drop(){
    
    //check if there is an item below the monster
    if (!checkForItem()){
        if(trueWithProbability(.1)){
            
            // randomly generate a 1 or 0
            int generated = randInt(2);
            
                //based on generated "drop" either a MagicAxe or MagicFangs
                if (generated == 0)
                    dungeon()->object_vector.push_back(new MagicAxe(row(), col()));
            
                if (generated == 1)
                    dungeon()->object_vector.push_back(new MagicFangs(row(), col()));
        }
    }
}

//void Goblin::move(char c){
//
//}


