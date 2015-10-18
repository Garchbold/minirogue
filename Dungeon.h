//
//  Dungeon.h
//  MiniRogue
//
//  Created by George Archbold on 5/12/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__Dungeon__
#define __MiniRogue__Dungeon__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Point.h"
#include "Monster.h"
#include "GameObject.h"
#include "utilities.h"
#include "Player.h"

using namespace std;

class Player;
class Monster;
class Goblin;
class GameObject;


class Dungeon
{
    
    static const int MAX_DUNGEON_ROW = 18;
    static const int MAX_DUNGEON_COL = 70;

public:
    // Constructor/destructor
    Dungeon(int nRows, int nCols);
    ~Dungeon();
    char    grid[MAX_DUNGEON_ROW][MAX_DUNGEON_COL];
    char    gameGrid[MAX_DUNGEON_ROW][MAX_DUNGEON_COL];

    
    // Accessors
    int     rows() const;
    int     cols() const;
    void    display(string msg);
    Player* player() const;
    Point   stairs() const;
    Point   idol() const;
    Point   point_retrieve();
    Monster* returnMonster(int r, int c);
    
    
    // Mutators
    void        addPlayer(int r, int c);
    void        addMonsters();
    Monster*    randMonster();
    void        addItems();
    GameObject* randObject();
    bool        generateCorridor(Point start, Point end);
    Point       drawRoom(Point corner);
    Point       generateRooms(int i, Point corner);
    void        checkMonstersDead();
    void        updateGameGrid();
    void        fillGameGrid();
    void        levelup();
    void        playerPickUp();
    void        useItem();
    
    vector<Monster*> monster_vector;
    vector<GameObject*> object_vector;
    vector<string> action_vector;
    

private:
    Player*  m_player;
    int     m_rows;
    int     m_cols;
    int     m_level;
    Point   m_stairs;
    Point   m_idol;
    
    vector<Point>  empty_space;
};


#endif /* defined(__MiniRogue__Dungeon__) */
