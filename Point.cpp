//
//  Point.cpp
//  MiniRogue
//
//  Created by George Archbold on 5/14/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#include "Point.h"

//constructor
Point::Point( int row, int col){
    r = row;
    c = col;
}

//default constructor
Point::Point(){
    r = 0;
    c = 0;
}