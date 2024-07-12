/******************************************************************************/
/*!
\file   Game.h
\author Kenneth Onulak
\par    Yahtzee
\date   07/11/2024
\brief
    Yahtzee game logic.
*/
/******************************************************************************/
#ifndef YAHTZEE_GAME_H
#define YAHTZEE_GAME_H

#include "Player.h"
#include "D6.h"
#include <vector>

// The game logic necessary to run Yahtzee
class Game
{
  public:
    // Setup a game
    Game(const std::vector<Player> & players);
    // Simulate a single round of dice rolls
    void playRound();
    // Display the current scores
    void showScores() const;

  private:
    int mCurrentPlayerIndex;      // Index of the current player
    std::vector<Player> mPlayers; // All players
    D6 mDice;                     // Single instance of a D6 used for all rolls
};

#endif // YAHTZEE_GAME_H
