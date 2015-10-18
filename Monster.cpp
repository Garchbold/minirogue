//
//  Monster.cpp
//  MiniRogue
//
//  Created by George Archbold on 5/13/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#include "Monster.h"

Monster :: Monster(Dungeon *pp, int r, int c)
: Actor (pp, r, c)
{
    
}

Monster::~Monster(){
    
}


bool Monster::canSmell(){
    
    //find the distance between the player and the monster in both directions
    int r_distance = row() - dungeon()->player()->row();
    int c_distance = col() - dungeon()->player()->col();
    
    if(r_distance < 0)
        r_distance = -r_distance;
    
    if(c_distance < 0)
        c_distance = -c_distance;
    
    //add the positives of both differences
    if (r_distance + c_distance < 6) {
        return true;//in range
    }
    else
        return false;//out of range
}


char Monster::getType(){
    return m_type;
}

void Monster::setType(char c ){
    m_type = c;
}

void Monster::setEquiped(Weapon* weapon){
    equiped = weapon;
}

//DID NOT END UP USING THIS FUNCTION
//was intended to help me find a path from the goblin to the player
Point Monster::findPath(Point monster, Point player){
    
    monster = Point(row(), col());
    player = Point(dungeon()->player()->row(), dungeon()->player()->col());
    
    stack<Point> path;
    
    path.push(monster);
    
    while (!path.empty()) {
        monster = path.top();
        
        path.pop();
        
        if (monster.r != player.r && monster.c - 1  != player.c){
        //North
            if( dungeon() -> grid[monster.r-1][monster.c] == ' ' )
            {
                path.push(Point(monster.r-1,monster.c));
                dungeon() -> grid[monster.r-1][monster.c] = '#';
            }
        //East
            if( dungeon() -> grid[monster.r][monster.c+1] == ' ' )
            {
                path.push(Point(monster.r, monster.c+1));
                dungeon() -> grid[monster.r][monster.c+1] = '#';
            }
        //South
            if( dungeon() -> grid[monster.r+1][monster.c] == ' ' )
            {
                path.push(Point(monster.r+1, monster.c));
                dungeon() -> grid[monster.r+1][monster.c] = '#';
            }
        //West
            if( dungeon() -> grid[monster.r][monster.c-1] == ' ' )
            {
                path.push(Point(monster.r, monster.c-1));
                dungeon() -> grid[monster.r][monster.c-1] = '#';
            
            }
        
        }
    }

    return path.top();
}

void Monster::attack(Actor* player){
    
    //if the monster's attackerPoints are greater than the players defenderPoints then attack
    if (randInt(dexterity() + equiped->dex_bonus) >= randInt(player->dexterity() + player->armor()) ){
        player->setHealth(player->health() - randInt(strength() + equiped->str_bonus));
        
        
        //check the monsters type and depending on its name add the appropriate "hit" action
        if(getType() == 'S'){
            if(trueWithProbability(.3)){
                dungeon()->player()->setSleep(2+randInt(4));
                dungeon()->action_vector.push_back("Snakewoman" + equiped->action() + " the Player and puts him to sleep.");
            }
            else{
                dungeon()->action_vector.push_back("Snakewoman" + equiped->action() + " the Player and hits.");
            }
        }
        if(getType() == 'B')
            dungeon()->action_vector.push_back("Boogeyman" + equiped->action() + " the Player and hits.");
        if(getType() == 'G')
            dungeon()->action_vector.push_back("Goblin" + equiped->action() + " the Player and hits.");
        if(getType() == 'D')
            dungeon()->action_vector.push_back("Dragon" + equiped->action() + " the Player and hits.");
    }
    else{
        //check the monsters type and depending on its name add the appropriate "miss" action
        if(getType() == 'S')
            dungeon()->action_vector.push_back("SnakeWoman" + equiped->action() +  " the Player and misses.");
        if(getType() == 'B')
            dungeon()->action_vector.push_back("Boogeyman" + equiped->action() + " the Player and misses.");
        if(getType() == 'G')
            dungeon()->action_vector.push_back("Goblin" + equiped->action() + " the Player and misses.");
        if(getType() == 'D')
            dungeon()->action_vector.push_back("Dragon" + equiped->action() + " the Player and misses.");
    }
}


bool Monster::checkForItem(){
    //Iterate through the object_vector in the dungeon and check if there is an item at the same spot as the monster
    
    for (vector<GameObject*> :: iterator g = dungeon()->object_vector.begin(); g!= dungeon()->object_vector.begin(); g++) {
        if (row() == (*g)->row() && col() == (*g)->col()) {
            return true;
            break;
        }
    }
    
    return false;
}


void Monster::move(char c){
    
    //find the distance on each axis and use to determine direction of movement
    int r_distance = row() - dungeon()->player()->row();
    int c_distance = col() - dungeon()->player()->col();
    
    
    if(canSmell()){//within range
        
        if (asleep() < 1) {//not asleep
            
            //if monster is next to a player attack
            if(row() == dungeon()-> player()->row() && col()-1 == dungeon()-> player()->col())
                attack(dungeon()->player());
            
            //if player is to the right of the monster and that space is empty then move
            else if (c_distance > 0){
                if(dungeon()->gameGrid[row()][col()-1] == ' '){
                    setCol(col()-1);
                }
                //if it cant move right move up or down
                else if ( r_distance < 0){
                    setRow(row() +1);
                }
                else if( r_distance > 0){
                    setRow(row()-1);
                }
            }
    
            //if monster is next to a player attack
            else if(row() == dungeon()-> player()->row() && col()+1 == dungeon()-> player()->col())
                attack(dungeon()->player());
            
            //if player is to the left of the monster and that space is empty then move
            else if (c_distance < 0){
                if(dungeon()->gameGrid[row()][col()+1] == ' '){
                setCol(col()+1);
                }
                
                //if it cant move right move up or down
                else if ( r_distance < 0){
                    setRow(row() +1);
                }
                else if( r_distance > 0){
                    setRow(row()-1);
                }
            }
            //if monster is next to a player attack
            else if(row()-1 == dungeon()-> player()->row() && col() == dungeon()-> player()->col())
                attack(dungeon()->player());
            
            //if player is below the monster and that space is empty then move
            else if (r_distance > 0){
                if(dungeon()->gameGrid[row()-1][col()] == ' '){
                    setRow(row()-1);
                }
                //if it cant move down move right or left
                else if ( c_distance < 0){
                    setCol(col()+1);
                }
                else if( c_distance > 0){
                    setCol(col()-1);
                }
            }
    
            //if monster is next to a player attack
            else if(row()+1 == dungeon()-> player()->row() && col() == dungeon()-> player()->col())
                attack(dungeon()->player());
            
            //if player is above the monster and that space is empty then move
            else if (r_distance < 0){
                if(dungeon()->gameGrid[row()+1][col()] == ' '){
                    setRow(row() + 1);
                }
                //if it cant move up then move right or left
                else if ( c_distance < 0){
                    setCol(col()+1);
                }
                else if( c_distance > 0){
                    setCol(col()-1);
                }
            
            }
            
        
        }//end of sleep check
        else{
            //if the monster is asleep remove 1 point from its sleepTime
            setSleep(asleep() -1);
        }
        
    }//end of can smell
    
    
}//end of function

void Monster::drop(){
    
}
