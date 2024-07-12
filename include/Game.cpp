/******************************************************************************/
/*!
\file   Game.cpp
\author Kenneth Onulak
\par    Yahtzee
\date   07/11/2024
\brief
    Implementation of the Yahtzee game logic.
*/
/******************************************************************************/

#include "Game.h"
#include <iostream>

Game::Game(const std::vector<Player> &players)
    : mCurrentPlayerIndex(0)
    , mPlayers(players)
{}

void Game::playRound()
{
    // TODO: Implement the logic for a round of Yahtzee
    // Roll dice for all players, keeping score as you go
}

void Game::showScores() const
{
    // Display score
    // Possible fancy output of a scorecard
}

