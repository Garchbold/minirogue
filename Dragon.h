//
//  Dragon.h
//  MiniRogue
//
//  Created by George Archbold on 5/24/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__Dragon__
#define __MiniRogue__Dragon__

#include <stdio.h>
#include "Actor.h"
#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"
#include "utilities.h"

class Dragon : public Monster {
    
public:
    
    Dragon(Dungeon *pp, int r, int c);
    ~Dragon();
    
    void move();
    void drop();
    
};



#endif /* defined(__MiniRogue__Dragon__) */
