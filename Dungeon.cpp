

//
//  Dungeon.cpp
//  MiniRogue
//
//  Created by George Archbold on 5/12/15.
//  Copyright (c) 2015 George Archbold. All rights reserved.
//

#include "Dungeon.h"
#include "Actor.h"
#include "Player.h"
#include "utilities.h"
#include "Goblin.h"
#include "SnakeWoman.h"
#include "BoogeyMan.h"
#include "Dragon.h"





Dungeon::Dungeon(int nRows, int nCols)
{
    //intitialize member variables
    m_rows = nRows;
    m_cols = nCols;
    m_level = 4;
    m_player = nullptr;
    
    int i;
    int j;
    
    //fill grid with walls
    for ( i = 0; i < MAX_DUNGEON_COL; i++) {
        for ( j = 0; j < MAX_DUNGEON_ROW; j++) {
            grid[j][i] = '#';
        }
    }
    
    //generate rooms and corridors
    Point room_start(randInt(14),randInt(60));
    generateRooms(3, room_start);
    
    //copy over to the game grid
    updateGameGrid();
    
    //set the stairs to a random location
    m_stairs = point_retrieve();
    m_idol = Point(0,0);

    //add player, monsters and items
    Point rand = point_retrieve();
    addPlayer(rand.r, rand.c);
    addMonsters();
    addItems();
}

Dungeon::~Dungeon()
{
}

int Dungeon::rows() const
{
    return m_rows;
}

int Dungeon::cols() const
{
    return m_cols;
}

Point Dungeon::stairs() const{
    return m_stairs;
}

Player* Dungeon::player() const
{
    return m_player;
}

void Dungeon::addPlayer(int r, int c){
    
    m_player =  new Player(this, r, c);
    
 
}

Point Dungeon::idol() const{
    return m_idol;
}


Point Dungeon::point_retrieve(){
    
    //store a random point from the empty space in the dungeon
    int x = randInt(empty_space.size()-1);
    Point p = empty_space[x];
    
    //delete the returned point so that no two things are created at the same space
    for (vector<Point> :: iterator i = empty_space.begin(); i != empty_space.end(); i++) {
        if( (*i).r == p.r && (*i).c == p.c){
            i = empty_space.erase(i);
            break;
        }
    }
    
    return p;
}

bool Dungeon::generateCorridor(Point start, Point end){
    
    //find the distance between two points in both directions
    int x_length = end.r - start.r +1;
    int y_length = end.c - start.c +1;
    
    //clear out a path along the x direction
    if (x_length < 0) {
        for (int i = 0; i < -x_length; i++) {
            grid[start.r - i][start.c] = ' ';
        }
    }
    
    if (x_length > 0) {
        for (int i = 0; i < x_length; i++) {
            grid[start.r + i][start.c] = ' ';
        }
    }
    
    //clear out a path along the y direction
    if (y_length < 0) {
        for (int i = 0; i < -y_length; i++) {
            grid[start.r + x_length][start.c - i] = ' ';
        }
    }
    
    if (y_length > 0) {
        for (int i = 0; i < y_length; i++) {
            grid[start.r +x_length][start.c + i] = ' ';
        }
    }
    
    return true;
    
}

Point Dungeon::drawRoom(Point corner){
    
    //create the opposite corner for the room
    Point room_bound(corner.r + 7 +randInt(4), corner.c + 14 +randInt(4));
    
    //make sure the room is never created with parts outside of the boundary
    if (corner.r == 0) {
        corner.r = 1;
    }
    
    if (corner.c == 0) {
        corner.c = 1;
    }
    
    if (room_bound.r > MAX_DUNGEON_ROW-1) {
        room_bound.r = MAX_DUNGEON_ROW-1;
    }
    
    if (room_bound.c > MAX_DUNGEON_COL-1) {
        room_bound.c = MAX_DUNGEON_COL-1;// ;)
    }
    
    //hollow out the room based on the corner pt and the room_bound pt
    for (int i = corner.r;  i <  room_bound.r ; i++) {
        for (int j = corner.c;  j <  room_bound.c; j++)
        {
            grid[i][j] = ' ';
            empty_space.push_back(Point(i,j));//store each empty spot
        }
    }

    return Point(randInt(14),randInt(60));//return a random new point for the corner of the next room
}


Point Dungeon::generateRooms(int i, Point corner){
    
    if( i == 0){
        
        return drawRoom(corner);//draw a random room
    }
    
    Point x = drawRoom(corner);//store the randomly returned point
    
    generateCorridor(corner, x);//draw a corridor between them
    
    return generateRooms(i-1, x);
    
}

Monster* Dungeon::randMonster(){
    
    int generated;
    
    //find a random point to generate this monster
    Point temp_point = point_retrieve();
    Monster* temp_monster;
    
    //based on which level it it create a certain random monster
    if ( m_level <= 1){
        generated = randInt(2);
        
        if(generated == 0)
            temp_monster = new  Goblin(this, temp_point.r, temp_point.c);
        if(generated == 1)
            temp_monster = new  SnakeWoman(this, temp_point.r, temp_point.c);
    }
    
    else if ( m_level == 2){
        generated = randInt(3);
        
        if(generated == 0)
            temp_monster = new  Goblin(this, temp_point.r, temp_point.c);
        if(generated == 1)
            temp_monster = new  SnakeWoman(this, temp_point.r, temp_point.c);
        if(generated == 2)
            temp_monster = new  BoogeyMan(this, temp_point.r, temp_point.c);
    }
    else if ( m_level >= 3){
        generated = randInt(4);
        
        if(generated == 0)
            temp_monster = new  Goblin(this, temp_point.r, temp_point.c);
        if(generated == 1)
            temp_monster = new  SnakeWoman(this, temp_point.r, temp_point.c);
        if(generated == 2)
            temp_monster = new  BoogeyMan(this, temp_point.r, temp_point.c);
        if (generated == 3) {
            temp_monster = new  Dragon(this, temp_point.r, temp_point.c);

        }
    }
    
    return temp_monster;
}

void Dungeon::addMonsters(){
    
    
    //based on the level create a certain number of monsters
    int numOfMonsters = 2 + randInt(5*(m_level+1));
    
    //store each monster in the monster_vector
    for (int i = 0; i < numOfMonsters; i++) {
        monster_vector.push_back(randMonster());
    }
}

Monster* Dungeon::returnMonster(int r, int c){
    
    //check all the monsters and return which ever monster is located at a certain point
    for (int i = 0; i< monster_vector.size(); i++) {
            if(monster_vector[i]->row() == r && monster_vector[i]->col() == c)
                return monster_vector[i];
    }
    
    return nullptr;
}

void Dungeon::checkMonstersDead()
{
    //iterate through all the monsters
    for (vector<Monster*>::iterator p = monster_vector.begin(); p != monster_vector.end(); p++)
    {
        Monster* ptr = *p;
        
        //if the monster's health is less than 0 drop its item and erase it
        if (ptr->health() <= 0)
        {
            (*p)->drop();
            p = monster_vector.erase(p);
            break;
        }
    }
}

//sets the gameGrid equal to the grid
void Dungeon::updateGameGrid(){
    
    for ( int i = 0; i < MAX_DUNGEON_COL; i++) {
        for ( int j = 0; j < MAX_DUNGEON_ROW; j++) {
            gameGrid[j][i] = grid[j][i];
        }
    }
}

void Dungeon::fillGameGrid(){
    
    //add monsters and stairs to the gameGrid
    for (int i =0; i < monster_vector.size(); i++) {
        gameGrid[monster_vector[i] -> row()][monster_vector[i] -> col()] = monster_vector[i]->getType();
    }
    gameGrid[m_stairs.r][m_stairs.c] = '>';
    

}

void Dungeon::levelup(){
    
    m_level++;
    
    //fresh grid
    for ( int i = 0; i < MAX_DUNGEON_COL; i++) {
        for ( int j = 0; j < MAX_DUNGEON_ROW; j++) {
            grid[j][i] = '#';
        }
    }
    
    //delete all the monster, items, and emptyspaces
    for (vector<Monster*>::iterator p = monster_vector.begin(); p != monster_vector.end(); p++)
    {
        p = monster_vector.erase(p);
        p--;
    }
    
    for (vector<Point> :: iterator i = empty_space.begin(); i != empty_space.end(); i++) {
        i = empty_space.erase(i);
        i--;
    }
    
    for (vector<GameObject*>::iterator g = object_vector.begin(); g != object_vector.end(); g++)
    {
        g = object_vector.erase(g);
        g--;
    }
    
    //create new rooms
    Point room_start(randInt(14),randInt(60));
    generateRooms(3, room_start);
    
    updateGameGrid();
    
    //replace the player in a new position
    Point rand = point_retrieve();
    player()->setRow(rand.r);
    player()->setCol(rand.c);
    //add new monsters and items
    addMonsters();
    addItems();
    m_stairs = point_retrieve();
    
    //only create the idol if its level 4
    if (m_level == 4) {
        m_idol = point_retrieve();
    }
}

void Dungeon::addItems(){
    
    int numOfItems = 2 + randInt(2);
    
    //store all the items in the dungeon
    for (int i = 0; i< numOfItems; i++) {
        object_vector.push_back(randObject());
    }
}

GameObject*  Dungeon::randObject(){
    
    int generated = randInt(2);
    GameObject* temp;
    Point pt = point_retrieve();

    //create a random item
    if(generated == 0){
        generated = randInt(3);
        
        if (generated == 0)
            temp = new Mace(pt.r,pt.c);
        if(generated == 1)
            temp = new ShortSword(pt.r,pt.c) ;
        if(generated == 2)
            temp = new LongSword(pt.r,pt.c);
    }
    
    if( generated == 1){
        generated = randInt(5);
        
        //create one of the 5 scrolls
        if(generated == 0)
            temp = new Scroll("Scroll of teleportation", pt.r,pt.c);
        if(generated == 1)
            temp = new Scroll("Scroll of enhance health",pt.r,pt.c);
        if(generated == 2)
            temp = new Scroll("Scroll of enhance dexterity", pt.r,pt.c);
        if(generated == 3)
            temp = new Scroll("Scroll of raise strength", pt.r,pt.c);
        if(generated == 4)
            temp = new Scroll("Scroll of improve armor", pt.r,pt.c);
    }

    return temp;
}

void Dungeon::playerPickUp(){
   
    if (player()->Inventory.size()< 25) {//check if inventory is full
        
        //iterate through the object_vector
        for (vector<GameObject*> :: iterator g = object_vector.begin() ; g != object_vector.end(); g++) {
            
            //if the player is ontop of an item store it in the inventory and delete it from the object_vector
            if ((*g)->row() == player()->row() && (*g)->col() == player()->col()) {
                
                player()->Inventory.push_back((*g));
                action_vector.push_back("Player picked up a " + (*g)->m_name);
                g = object_vector.erase(g);
                g--;
            }
        }
    }
    else{
        action_vector.push_back("Your Inventory is full.");
    }
}

void Dungeon::useItem(){
    char c = getCharacter();//check which item the player wants to use
    
    int i = (int)c - 97;//cast it to match the inventory index
    
    //check for valid inventory entry
    if (i > player()->Inventory.size()) {
        clearScreen();
        return;
    }
    
    //check if the item to be used is a weapon or a scroll
    Weapon* check = dynamic_cast<Weapon*>(player()->Inventory[i]);
    Scroll* check2 = dynamic_cast<Scroll*>(player()->Inventory[i]);
    
    //set the players weapon to the specified weapon
    if  (check != nullptr){
        player()->setEquiped(check);
        action_vector.push_back("You equiped " + check->m_name + ".");
    }
    
    if ( check2 != nullptr){
        
        //check the name of the scroll and based on that implement its effect
        if (check2->m_name == "Scroll of teleportation") {
            
            //reset the players position
            Point rand = point_retrieve();
            player()->setRow(rand.r);
            player()->setCol(rand.c);
            action_vector.push_back("Scroll of teleportation: You feel your body wrenched in space and time.");
        }
        
        if (check2->m_name == "Scroll of enhance health") {
            //add to the players health
            player()->setMaxHealth(player()->maxHealth() + 3 + randInt(6));
            action_vector.push_back("Scroll of enhance health: You feel your heart beating stronger.");
        }
        
        if (check2->m_name == "Scroll of raise strength") {
            //add to the players strength
            player()->setStrength(player()->strength() + 1 + randInt(3));
            action_vector.push_back("Scroll of raise strength: Your muscles bulge.");
        }
        if (check2->m_name == "Scroll of improve armor") {
            //add to the players armor
            player()->setArmor(player()->armor() + 1 + randInt(3));
            action_vector.push_back("Scroll of improve armor: Your armor glows blue.");

        }
        if (check2->m_name == "Scroll of enhance dexterity") {
            //add to the players dexterity
            player()->setDexterity(player()->dexterity()+1);
            action_vector.push_back("Scroll of enhance decterity: You feel like less of a klutz.");

        }
        
        //if it was a scroll erase it from the inventory
        for (vector<GameObject*> :: iterator i = player()->Inventory.begin(); i != player()->Inventory.end(); i++) {
            if((*i)->row() == check2->row() && (*i)->col() == check2->col()){

                i = player()->Inventory.erase(i);
                i--;
            }
        }
    }

}



void Dungeon::display(string msg)
{
    clearScreen();
    cout << endl;
    
    //check all the monsters and update and fill the gameGrid
    checkMonstersDead();
    updateGameGrid();
    fillGameGrid();
    
    //add the items monsters ans stairs to the grid at the beginning
    for (int i = 0; i < object_vector.size(); i++) {
        grid[object_vector[i]->row()][object_vector[i]->col()] = object_vector[i]->getType();
    }
    
    for (int i =0; i < monster_vector.size(); i++) {
        grid[monster_vector[i] -> row()][monster_vector[i] -> col()] = monster_vector[i]->getType();
    }
    
    if ( m_level < 4){
        grid[m_stairs.r][m_stairs.c] = '>';
    }
    
    //only show the idol for level 4
    if (m_level == 4){
        grid[m_idol.r][m_idol.c] = '&';

    }

    
    
    for (int r = 0; r < rows(); r++)
    {
        for (int c = 0; c < cols(); c++){
            
            //print out the player
            if (r == player() -> row() && c == player()->col()) {
                cout << '@';
            }
            //print out a border
            else if( r == 0 || c == 0 || r == MAX_DUNGEON_ROW-1 || c == MAX_DUNGEON_COL-1){
                cout << '#';
            }
            
            
            else{
                cout << grid[r][c];
            }
            
        }
        cout << endl;
    }
    
    //remve the monsters items and stairs from the grid after each display
    for (int i = 0; i < monster_vector.size(); i++) {
        grid[monster_vector[i] -> row()][monster_vector[i] -> col()] = ' ';
    }
    for (int i = 0; i< object_vector.size(); i++) {
        grid[object_vector[i]->row()][object_vector[i]->col()] = ' ';
    }
    
    grid[m_stairs.r][m_stairs.c] = ' ';
    
    //print out the players attributes each turn
    cout << "Dungeon Level: "<< m_level<<", Hit points: "<< m_player->health()<<", Armor: "<< m_player->armor()<<" Strength: "<<m_player->strength()<<", Dexterity: "<< m_player->dexterity() <<endl;
    cout << endl;
    
    //print out all the actions that took place that turn
    for (vector<string> :: iterator s = action_vector.begin(); s != action_vector.end(); s++) {
        cout << *s << endl;
        s = action_vector.erase(s);
        s--;
    }
    
  

}