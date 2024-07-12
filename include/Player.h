/******************************************************************************/
/*!
\file   Player.h
\author Kenneth Onulak
\par    Yahtzee
\date   07/11/2024
\brief
    Necessary player information.
*/
/******************************************************************************/
#ifndef YAHTZEE_PLAYER_H
#define YAHTZEE_PLAYER_H

#include "Scorecard.h"
#include <string>

// All necessary player information
class Player
{
  public:
    // Create a player with a given name
    explicit Player(std::string name);
    // Get the players name
    [[nodiscard]] std::string getName() const;
    // Get the players scorecard
    Scorecard & getScorecard();

  private:
    std::string mName;    // Player's name
    Scorecard mScorecard; // Track the players score
};
#endif // YAHTZEE_PLAYER_H
