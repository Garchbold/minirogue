
#include "Actor.h"
#include "Dungeon.h"
#include "GameObject.h"


Actor::Actor(Dungeon *pp, int r, int c){
    m_dungeon = pp;
    m_row = r;
    m_col =c;
};

Actor::~Actor(){
    
}

//-----Mutators-----

void Actor::setRow(int x){
    m_row = x;
}
void Actor::setCol(int x){
    m_col = x;
}
void Actor::setHealth(int x){
    m_hit_pts = x;
}
void Actor::setStrength(int x){
    m_str_pts = x;
}

void Actor::setDexterity(int x){
    m_dex_pts = x;
}


void Actor::setArmor(int x){
    m_armor = x;
}

void Actor::setSleep(int x){
    m_sleeptime = x;
}


//-----Accesors-----

int Actor::row() const{
    return m_row;
}
int Actor::col() const{
    return m_col;
}
Dungeon* Actor::dungeon() const{
    return m_dungeon;
}
int Actor::health(){
    return m_hit_pts;
}
int Actor::strength(){
    return m_str_pts;
}
int Actor::dexterity(){
    return m_dex_pts;
}
int Actor::armor(){
    return m_armor;
}
int Actor::asleep(){
    return m_sleeptime;
}

