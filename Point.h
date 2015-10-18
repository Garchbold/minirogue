//
//  Point.h
//  MiniRogue
//
//  Created by George Archbold on 5/14/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__Point__
#define __MiniRogue__Point__

#include <stdio.h>

class Point{
    
public:
    
    int r;
    int c;
    
    Point();
    Point( int row, int col);
    
};

#endif /* defined(__MiniRogue__Point__) */
