//
//  BoogeyMan.h
//  MiniRogue
//
//  Created by George Archbold on 5/24/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__BoogeyMan__
#define __MiniRogue__BoogeyMan__

#include <stdio.h>

#include "Actor.h"
#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"
#include "utilities.h"

class BoogeyMan : public Monster {
    
public:
    
    BoogeyMan(Dungeon *pp, int r, int c);
    ~BoogeyMan();
    
    void drop();
    
};

#endif /* defined(__MiniRogue__BoogeyMan__) */
