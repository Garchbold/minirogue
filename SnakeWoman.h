
//
//  SnakeWoman.h
//  MiniRogue
//
//  Created by George Archbold on 5/19/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__SnakeWoman__
#define __MiniRogue__SnakeWoman__

#include <stdio.h>

#include "Actor.h"
#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"
#include "utilities.h"



class SnakeWoman : public Monster {
    
public:
    
    SnakeWoman(Dungeon *pp, int r, int c);
    ~SnakeWoman();
    
    void drop();
    
};


#endif /* defined(__MiniRogue__SnakeWoman__) */
