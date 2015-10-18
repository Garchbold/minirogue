//
//  Goblin.h
//  MiniRogue
//
//  Created by George Archbold on 5/18/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__Goblin__
#define __MiniRogue__Goblin__

#include <stdio.h>
#include <stack>
#include "Actor.h"
#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"
#include "utilities.h"



class Goblin : public Monster {
    
public:
    
    Goblin(Dungeon *pp, int r, int c);
    ~Goblin();
    
    bool canSmell();
    void drop();
    //void move(char c);
    
    
private:
   
    
};


#endif /* defined(__MiniRogue__Goblin__) */
