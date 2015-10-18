//
//  GameObject.cpp
//  MiniRogue
//
//  Created by George Archbold on 5/19/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#include "GameObject.h"

//constructors
GameObject::GameObject( string name, int row, int col){
    
    m_name = name;
    m_row = row;
    m_col = col;
}

Weapon::Weapon( string name, int dex, int str, int row, int col) : GameObject( name, row, col){
    dex_bonus = dex;
    str_bonus = str;
    setType('(');
}

Weapon::Weapon() : GameObject(" ", 0, 0){
    dex_bonus = 0;
    str_bonus = 0;
    setType('(');
}

Scroll :: Scroll(): GameObject("" ,0,0){
}

GameObject::~GameObject(){
    
}

//-------Accessors--------

char GameObject::getType(){
    return type;
}
int GameObject::row(){
    return m_row;
}

int GameObject::col(){
    return m_col;
}

string GameObject::action(){
    return m_action;
}

//-------Mutators--------

void GameObject::setRow(int x){
    m_row = x;
}
void GameObject::setCol(int x){
    m_row = x;
}

void GameObject::setType(char c){
    type = c;
}
void GameObject::setName(string s){
    m_name = s;
}
void GameObject::setAction(string s){
    m_action = s;
}


//each derived constructor with its respective "action" and attributes

Mace::Mace( int row, int col) : Weapon( "Mace", 0 , 2, row, col){
    setAction(" swings mace at");
}

ShortSword::ShortSword( int row, int col) : Weapon( "Short sword", 0 , 2, row, col){
    setAction(" slashes short sword at");
}
LongSword::LongSword( int row, int col) : Weapon( "Long sword", 2 , 4, row, col){
    setAction(" swings long sword at");
}

MagicAxe::MagicAxe( int row, int col) : Weapon( "Magic axe", 5 , 5, row, col){
    setAction(" chops magic axe at");
}

MagicFangs::MagicFangs( int row, int col) : Weapon( "Magic fangs of sleep", 0 , 2, row, col){
    setAction(" strikes magic fangs at");
}

Scroll::Scroll( string name, int row, int col) : GameObject (name, row, col){
    setType('?');

}