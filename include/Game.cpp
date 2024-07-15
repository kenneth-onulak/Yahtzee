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
#include <unordered_set>

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
    case 1: std::cout << "ACES"; break;
    case 2: std::cout << "TWOS" ; break;
    case 3: std::cout << "THREES" ; break;
    case 4: std::cout << "FOURS" ; break;
    case 5: std::cout << "FIVES" ; break;
    case 6: std::cout << "SIXES" ; break;
    case 7: std::cout << "PAIR" ; break;
    case 8: std::cout << "TWO PAIR" ; break;
    case 9: std::cout << "THREE OF A KIND" ; break;
    case 10: std::cout << "FOUR OF A KIND" ; break;
    case 11: std::cout << "FULL HOUSE" ; break;
    case 12: std::cout << "SMALL STRAIGHT" ; break;
    case 13: std::cout << "LARGE STRAIGHT" ; break;
    case 14: std::cout << "YAHTZEE" ; break;
    case 15: std::cout << "CHANCE" ; break;
    default: std::cout << "NONE"; break;
    }
}

void Game::playRound()
{
    for (auto & player : mPlayers)
    {   // Roll the dice and max out the score for that roll
        std::vector<int> rolledDice = rollDice();
        int bestCategory = player.getScorecard().getMaxScoreCategory(rolledDice, false);

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

void Game::playRound2()
{
    int iterations = 0;
    std::unordered_set<int> uniqueCategories;

    // Only checking 14 categories
    // CHANCE is commented out in scorecard since CHANCE is often better than
    // ACES through SIXES
    while (uniqueCategories.size() < 14)
    {
        for (auto & player : mPlayers)
        {   // Roll the dice and max out the score for that roll
            std::vector<int> rolledDice = rollDice();
            int bestCategory = player.getScorecard().getMaxScoreCategory(rolledDice, true);

            std::cout << player.getName() << " rolled : ";
            for (auto const & dice : rolledDice)
            {
                std::cout << dice << " ";
            }
            std::cout << "\n";

            // All scores are filled if there is still no best category
            if (bestCategory != -1)
            {
                player.getScorecard().updateScore(static_cast<Category>(bestCategory), rolledDice);
                std::cout << player.getName() << " placed roll in category ";
                printCategory(bestCategory);
                std::cout << " for a score of " << player.getScorecard().getScore(static_cast<Category>(bestCategory)) << "\n";
                uniqueCategories.insert(bestCategory);
            }
            else
            {
                std::cout << player.getName() << " has no available categories to place the roll." << "\n";
            }
        }
        ++iterations;
    }

    std::cout << "Iterations: " << iterations << std::endl;
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

