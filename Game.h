// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.

#include "Dungeon.h"
#include "Monster.h"


class Game
{
public:
	Game(int goblinSmellDistance);
	void play();
private:
    Dungeon m_dungeon;
};

#endif // GAME_INCLUDED
