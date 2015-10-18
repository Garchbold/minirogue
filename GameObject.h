//
//  GameObject.h
//  MiniRogue
//
//  Created by George Archbold on 5/19/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#ifndef __MiniRogue__GameObject__
#define __MiniRogue__GameObject__


#include <stdio.h>
#include <string>

using namespace std;

class GameObject{
    
public:
    GameObject(string name, int row, int col);
    virtual ~GameObject();
    
    string m_name;

    char getType();
    int row();
    int col();
    string action();
    
    void setRow(int x);
    void setCol(int x);
    void setType(char c);
    void setName(string s);
    void setAction(string s);
    
private:
    char type;
    int m_row;
    int m_col;
    string m_action;
    
};

class Weapon : public GameObject{

public:

    Weapon();
    Weapon( string name, int dex, int str, int row, int col);

    int dex_bonus;
    int str_bonus;

};


class Mace : public Weapon{
public:
    Mace( int row, int col);

};

class ShortSword : public Weapon{

public:

    ShortSword( int row, int col);

};

class LongSword : public Weapon{
public:
    LongSword( int row, int col);

};

class MagicAxe : public Weapon{
public:
    MagicAxe( int row, int col);

};

class MagicFangs : public Weapon{
public:
    MagicFangs( int row, int col);

};

class Scroll : public GameObject{
    
public:
    
    Scroll();
    Scroll( string name, int row, int col);
    
};





#endif /* defined(__MiniRogue__GameObject__) */
