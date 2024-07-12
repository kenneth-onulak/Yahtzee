/******************************************************************************/
/*!
\file   Player.cpp
\author Kenneth Onulak
\par    Yahtzee
\date   07/11/2024
\brief
    Implementation of the player.
*/
/******************************************************************************/

#include "Player.h"

Player::Player(std::string name)
    : mName(name)
{}

std::string Player::getName() const
{
    return mName;
}

Scorecard & Player::getScorecard()
{
    return mScorecard;
}

