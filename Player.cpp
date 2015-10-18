//
//  Player.cpp
//  MiniRogue
//
//  Created by George Archbold on 5/13/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#include "Player.h"
#include <cassert>

Player :: Player(Dungeon *pp, int r, int c)
: Actor (pp, r, c)
{
    max_health = 20;
    setHealth(20);
    setDexterity(2);
    setSleep(0);
    setArmor(2);
    setStrength(2);
    
    equiped = new ShortSword(r,c);
    Inventory.push_back(equiped);
    
}

Player::~Player(){
    
}


int Player::maxHealth(){
    return max_health;
}
void Player::setMaxHealth(int x){
    max_health = x;
}


void Player::attack(Actor* monster){
    
    //check if the function input is acually a monster through dynamic cast
    Monster* temp = dynamic_cast<Monster*>(monster);
    string monsterName;
    char c = temp->getType();
    
    //check the monsters type and based on that, assign monsterName a specific name
    switch (c) {
        case 'S':
            monsterName = " a Snakewoman";
            break;
        case 'B':
            monsterName = " a Boogeyman";
            break;
        case 'D':
            monsterName = " a Dragon";
            break;
        case 'G':
            monsterName = " a Goblin";
            break;
            
        default:
            break;
    }
    
    //check if the players attackerPoints are greater than the monsters defenderPoints
    if (randInt(dexterity() + equiped->dex_bonus) >= randInt(monster->dexterity() + monster->armor())) {
        
        //subtract the inflicted damage from the monster
        monster->setHealth(monster->health() - randInt(strength() + equiped->str_bonus));
        
        //if the user is using MagicFangs and probablilty is greater than 1/3 then put the monster to sleep
        if (equiped->m_name == "Magic fangs of sleep") {
            if(trueWithProbability(.3)){
                monster->setSleep(2+randInt(5));
                //add an action to action vector
                dungeon()->action_vector.push_back("Player" + equiped->action() + monsterName+" and puts him to sleep.");
            }
            else
                //add an action saying that the player hit but did not put to sleep
                dungeon()->action_vector.push_back("Player" + equiped->action()  +monsterName + " and hits.");
        }
        else
            //add an action saying that the player hit
            dungeon()->action_vector.push_back("Player" + equiped->action()  +monsterName + " and hits.");
    }
    else
        //add an action saying that the player missed
        dungeon()->action_vector.push_back("Player" + equiped->action() + monsterName+ " and misses.");

}

//ITERATE through the Inventory and print out all the items
void Player::printInventory(){
    
    char letter= 'a';
    int j = 0;
    
    clearScreen();
    cout << endl << "Inventory:"<< endl;
    
    for (vector<GameObject*> :: iterator i = Inventory.begin(); i != Inventory.end(); i++) {
        cout<< static_cast<char>(letter + j) << ": " << (*i)->m_name << endl;
        j++;
    }
}



//A helper function that just checksif there is a monster around the player
bool Player::checkForMonster(string dir){
    
    bool b = false;
    if (dir == "UP") {
        b = dungeon()->gameGrid[row()][col()-1] == 'G' || dungeon()->gameGrid[row()][col()-1] == 'S'
        || dungeon()->gameGrid[row()][col()-1] == 'B'|| dungeon()->gameGrid[row()][col()-1] == 'D';
            
    }
    if (dir == "DOWN") {
        b = dungeon()->gameGrid[row()][col()+1] == 'G' || dungeon()->gameGrid[row()][col()+1] == 'S'
        || dungeon()->gameGrid[row()][col()+1] == 'B'|| dungeon()->gameGrid[row()][col()+1] == 'D';
    }
    if (dir == "LEFT") {
        b = dungeon()->gameGrid[row()-1][col()] == 'G' || dungeon()->gameGrid[row()-1][col()] == 'S'
        || dungeon()->gameGrid[row()-1][col()] == 'B'|| dungeon()->gameGrid[row()-1][col()] == 'D';
    }
    if (dir == "RIGHT") {
        b = dungeon()->gameGrid[row()+1][col()] == 'G' || dungeon()->gameGrid[row()+1][col()] == 'S'
        || dungeon()->gameGrid[row()+1][col()] == 'B'|| dungeon()->gameGrid[row()+1][col()] == 'D';
    }
    
    return b;
}

//setter function for the players weapon
void Player::setEquiped(Weapon* weapon){
    equiped = weapon;
}

void Player::move(char c){
    
    //heal the player
    if(trueWithProbability(.1)){
        if( health() < max_health)
            setHealth(health()+1);
    }
    
    //check if the player is asleep
    if( asleep() < 1){
    
        
        switch (c) {
            case 'h':
                //if there is a monster above the player attack it
                if(checkForMonster("UP"))
                    attack(dungeon()->returnMonster(row(), col()-1));
                
                //if the next space is something the player can move onto(empty space or item) then move
                else if(dungeon()->gameGrid[row()][col()-1] == ' '|| dungeon()->gameGrid[row()][col()-1] == '>' || dungeon()->gameGrid[row()][col()-1] == '&')
                    setCol(col()-1);
                break;
                
            case 'l':
                //if there is a monster below the player attack it
                if(checkForMonster("DOWN"))
                    attack(dungeon()->returnMonster(row(), col()+1));
                
                else if(dungeon()->gameGrid[row()][col()+1] == ' ' || dungeon()->gameGrid[row()][col()+1] == '>'|| dungeon()->gameGrid[row()][col()-1] == '&')
                    setCol(col()+1);
                break;
                
            case 'k':
                //if there is a monster to the left of the player attack it
                if(checkForMonster("LEFT"))
                    attack(dungeon()->returnMonster(row()-1, col()));
                
                else if(dungeon()->gameGrid[row()-1][col()] == ' '|| dungeon()->gameGrid[row()-1][col()] == '>'|| dungeon()->gameGrid[row()][col()-1] == '&')
                    setRow(row()-1);
                break;
                
            case 'j':
                //if there is a monster to the right of the player attack it
                if(checkForMonster("RIGHT"))
                    attack(dungeon()->returnMonster(row()+1, col()));
                
                else if(dungeon()->gameGrid[row()+1][col()] == ' '|| dungeon()->gameGrid[row()+1][col()] == '>'|| dungeon()->gameGrid[row()][col()-1] == '&')
                    setRow(row() +1);
                break;
                
            default:
                break;
        
        }
    }
    else{
        //if the player is asleep then each move reduce his sleepTime by 1 point
        setSleep(asleep()-1);
        dungeon()->action_vector.push_back("Player is asleep");
    }
}




