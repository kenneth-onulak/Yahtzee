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
#include <format>

////////////////////////////////////////////////////////////////////////////////
// Public Methods

Game::Game(const std::vector<Player> &players)
    : mCurrentPlayerIndex(0)
    , mPlayers(players)
{}

// Helper function to turn a category into text
void printCategory(int category)
{
    switch (category)
    {
    case 1: std::cout << "ACES\n"; break;
    case 2: std::cout << "TWOS\n" ; break;
    case 3: std::cout << "THREES\n" ; break;
    case 4: std::cout << "FOURS\n" ; break;
    case 5: std::cout << "FIVES\n" ; break;
    case 6: std::cout << "SIXES\n" ; break;
    case 7: std::cout << "PAIR\n" ; break;
    case 8: std::cout << "TWO PAIR\n" ; break;
    case 9: std::cout << "THREE OF A KIND\n" ; break;
    case 10: std::cout << "FOUR OF A KIND\n" ; break;
    case 11: std::cout << "FULL HOUSE\n" ; break;
    case 12: std::cout << "SMALL STRAIGHT\n" ; break;
    case 13: std::cout << "LARGE STRAIGHT\n" ; break;
    case 14: std::cout << "YAHTZEE\n" ; break;
    case 15: std::cout << "CHANCE\n" ; break;
    default: std::cout << "NONE\n"; break;
    }
}

void Game::playRound()
{
    for (auto & player : mPlayers)
    {   // Roll the dice and max out the score for that roll
        std::vector<int> rolledDice = rollDice();
        int bestCategory = player.getScorecard().getMaxScoreCategory(rolledDice);

        std::cout << player.getName() << " rolled : ";
        for (auto const & dice : rolledDice)
        {
            std::cout << dice << " ";
        }
        std::cout << std::endl;

        // All scores result in zero, so just choose one
        // Setup to just choose the first unfilled category
        if (bestCategory == -1)
        {
            bestCategory = getFirstOpenCategory(player.getScorecard());
        }

        // All scores are filled if there is still no best category
        if (bestCategory != -1)
        {
            player.getScorecard().updateScore(static_cast<Category>(bestCategory), rolledDice);
            std::cout << player.getName() << " placed roll in category ";
            printCategory(bestCategory);
            std::cout << " Max score of " << player.getScorecard().getTotalScore() << std::endl;
        }
        else
        {
            std::cout << player.getName() << " has no available categories to place the roll." << std::endl;
        }
    }
}

void Game::showScores()
{
    for (auto & player : mPlayers)
    {
        std::cout << player.getName() << "'s total score: " << player.getScorecard().getTotalScore() << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Private Methods

std::vector<int> Game::rollDice()
{
    std::vector<int> rolledDice;
    for (int i = 0; i < 5; ++i)
    {
        mDice.roll();
        rolledDice.push_back(mDice.getValue());
    }
    return rolledDice;
}

int Game::getFirstOpenCategory(Scorecard & scorecard)
{
    for (int category = ACES; category <= CHANCE; ++category)
    {
        if (!scorecard.isCategoryFilled(static_cast<Category>(category)))
        {
            return category;
        }
    }

    // All categories have been filled
    return -1;
}

