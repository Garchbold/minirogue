
// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
#include "Player.h"
#include "Dungeon.h"
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
:m_dungeon(Dungeon(18, 70))
{
    m_dungeon.display("");
}

void Game::play()
{
    
    Player* a = m_dungeon.player();
    if (a == nullptr)
    {
        m_dungeon.display("");
        return;
    }
    
    
    cout << "Press q to exit game." << endl;
    
    char c = getCharacter();
  
    while (c != 'q'){
        
        //check if the player is dead
        if ( m_dungeon.player()->health() < 1){
            m_dungeon.action_vector.push_back("You lose");
            m_dungeon.display("");
            break;
        }
        
        //player wants to try to pick somthing up
        if (c == 'g' ){
            m_dungeon.playerPickUp();
        }
        
        //player wants to access inventory
        if (c == 'w' || c == 'r' || c== 'i') {
            m_dungeon.player()->printInventory();
            m_dungeon.useItem();
        }
    
        //player wants to levelup, also check is his position allows it
        if (c == '>' && m_dungeon.player()->row() == m_dungeon.stairs().r && m_dungeon.player()->col() == m_dungeon.stairs().c) {
            m_dungeon.levelup();
            m_dungeon.action_vector.push_back("You advance deeper in the dungeon.");

        }
        
        //player wins the game
        if (c == '&' && m_dungeon.player()->row() == m_dungeon.idol().r && m_dungeon.player()->col() == m_dungeon.idol().c) {
            m_dungeon.action_vector.push_back("Congratulations! You found the Golden Idol and won.");
        }
    
        //accept the users input for movement
        m_dungeon.player()->move(c);
        
        for (int i = 0; i < m_dungeon.monster_vector.size(); i++) {
            m_dungeon.monster_vector[i]->move(c);
            m_dungeon.fillGameGrid();
        }
        //reprint the grid after completion of one turn
        m_dungeon.display("");
        
        //accept another character
        c = getCharacter();

    }
    //check for quit command
    if (c == 'q') {
        return;
    }
}

