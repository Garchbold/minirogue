//
//  Player.h
//  MiniRogue
//
//  Created by George Archbold on 5/12/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__Actor__
#define __MiniRogue__Actor__

#include <stdio.h>
#include <vector>

using namespace std;

class Dungeon;
class GameObject;

class Actor
{
public:
    
    Actor(Dungeon *pp, int r, int c);
    virtual ~Actor();
    
    virtual int row() const;
    virtual int col() const;
    virtual void setRow(int x);
    virtual void setCol(int x);
    
    Dungeon* dungeon() const;
    int health();
    int strength();
    int dexterity();
    int armor();
    int asleep();
    
    void setHealth(int x);
    void setStrength(int x);
    void setDexterity(int x);
    void setArmor(int x);
    void setSleep(int x);
    
    virtual void move(char c) = 0;

   
private:
    Dungeon*  m_dungeon;
    
    int   m_row;
    int   m_col;
    
    int   m_hit_pts;
    int   m_str_pts;
    int   m_dex_pts;
    int   m_armor;
    int   m_sleeptime;
};


#endif /* defined(__MiniRogue__Player__) */
