//
//  Dragon.cpp
//  MiniRogue
//
//  Created by George Archbold on 5/24/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#include "Dragon.h"


Dragon :: Dragon(Dungeon *pp, int r, int c)
:Monster(pp, r, c)
{
    setHealth(20 + randInt(6));
    setDexterity(4);
    setSleep(0);
    setArmor(2);
    setStrength(4);
    setType('D');
    
    setEquiped(new LongSword(r,c));
    
}

Dragon::~Dragon(){
    
}

void Dragon::drop(){
    //check for an item under the dragon
    if (!checkForItem()){
        
        int generated = randInt(5);
        
        
        //randomly drop one of the 5 scrolls at the dragons position
        if(generated == 0)
            dungeon()->object_vector.push_back( new Scroll("Scroll of teleportation", row(), col()));
        if(generated == 1)
            dungeon()->object_vector.push_back( new Scroll("Scroll of enhance health", row(), col()));
        if(generated == 2)
            dungeon()->object_vector.push_back( new Scroll("Scroll of enhance dexterity", row(), col()));
        if(generated == 3)
            dungeon()->object_vector.push_back( new Scroll("Scroll of raise strength", row(), col()));
        if(generated == 4)
            dungeon()->object_vector.push_back( new Scroll("Scroll of improve armor", row(), col()));
    }
}

void Dragon::move(){
    
    //chance for the Dragon to heal
    if(trueWithProbability(.1)){
        setHealth(health()+1);
    }
    
    //never actually move the dragon but do check if the player is next to it and if so attack
    if(row() == dungeon()-> player()->row() && col()-1 == dungeon()-> player()->col())
        attack(dungeon()->player());
    
    else if(row() == dungeon()-> player()->row() && col()+1 == dungeon()-> player()->col())
        attack(dungeon()->player());
    
    else if(row()-1 == dungeon()-> player()->row() && col() == dungeon()-> player()->col())
        attack(dungeon()->player());

    else if(row()+1 == dungeon()-> player()->row() && col() == dungeon()-> player()->col())
        attack(dungeon()->player());
    
}
