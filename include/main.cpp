/******************************************************************************/
/*!
\file   main.cpp
\author Kenneth Onulak
\par    Yahtzee
\date   07/11/2024
\brief
    Entry point for testing and running Yahtzee.
*/
/******************************************************************************/

#include "D6.h"
#include "Scorecard.h"
#include "Player.h"
#include "Game.h"

#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>


// Verify random number produces all-inclusive values between 1-6
void test0()
{
    std::unordered_set<int> generatedNumbers; // Store unique values
    D6 dice;                                  // Random number generator

    // Test the dice for all values
    for (int i = 0; i < 100; ++i)
    {
        dice.roll();
        generatedNumbers.insert(dice.getValue());
        std::cout << dice.getValue() << std::endl;

        // Break if all numbers have appeared at least once
        if (generatedNumbers.size() == 6)
        {
            break;
        }
    }
}

void test1()
{
    std::vector<int> dice = { 1, 2, 3, 4, 5 };
    Scorecard scorecard;

    // Aces through Sixes
    scorecard.updateScore(ACES, dice);
    std::cout << "Aces score  : " << scorecard.getAces() << "\n";

    scorecard.updateScore(TWOS, dice);
    std::cout << "Twos score  : " << scorecard.getTwos() << "\n";

    scorecard.updateScore(THREES, dice);
    std::cout << "Threes score: " << scorecard.getThrees() << "\n";

    scorecard.updateScore(FOURS, dice);
    std::cout << "Fours score : " << scorecard.getFours() << "\n";

    scorecard.updateScore(FIVES, dice);
    std::cout << "Fives score : " << scorecard.getFives() << "\n";

    scorecard.updateScore(SIXES, dice);
    std::cout << "Sixes score : " << scorecard.getSixes() << "\n";

    // Yahtzee scored as sixes
    dice = { 6, 6, 6, 6, 6 };
    scorecard.updateScore(SIXES, dice);
    std::cout << "Sixes score : " << scorecard.getSixes() << "\n";

    // Pairs
    scorecard.updateScore(PAIR, dice);
    std::cout << "Pair score     : " << scorecard.getPair() << "\n";

    // Yahtzee scored as two pair
    scorecard.updateScore(TWO_PAIRS, dice);
    std::cout << "Two Pair score : " << scorecard.getTwoPairs() << "\n";

    // Scoring the largest pair
    dice = { 4, 3, 2, 2, 3 };
    scorecard.updateScore(PAIR, dice);
    std::cout << "Pair score     : " << scorecard.getPair() << "\n";

    // Scoring two different pairs
    scorecard.updateScore(TWO_PAIRS, dice);
    std::cout << "Two Pair score : " << scorecard.getTwoPairs() << "\n";

    // No Pairs
    dice = { 1, 2, 3, 4, 5 };
    scorecard.updateScore(PAIR, dice);
    std::cout << "Pair score     : " << scorecard.getPair() << "\n";

    scorecard.updateScore(TWO_PAIRS, dice);
    std::cout << "Two Pair score : " << scorecard.getTwoPairs() << "\n";

    // Three of a kind
    scorecard.updateScore(THREE_OF_A_KIND, dice);
    std::cout << "Three of a Kind score : " << scorecard.getThreeOfAKind() << "\n";

    dice = { 1, 1, 5, 5, 5 };
    scorecard.updateScore(THREE_OF_A_KIND, dice);
    std::cout << "Three of a Kind score : " << scorecard.getThreeOfAKind() << "\n";

    dice = { 1, 5, 5, 5, 5 };
    scorecard.updateScore(THREE_OF_A_KIND, dice);
    std::cout << "Three of a Kind score : " << scorecard.getThreeOfAKind() << "\n";

    // Four of a kind
    scorecard.updateScore(FOUR_OF_A_KIND, dice);
    std::cout << "Four of a Kind score : " << scorecard.getFourOfAKind() << "\n";

    dice = { 1, 1, 5, 5, 5 };
    scorecard.updateScore(FOUR_OF_A_KIND, dice);
    std::cout << "Four of a Kind score : " << scorecard.getFourOfAKind() << "\n";

    // Full house
    scorecard.updateScore(FOUR_OF_A_KIND, dice);
    std::cout << "Full House score : " << scorecard.getFullHouse() << "\n";

    dice = { 3, 4, 3, 4, 3 };
    scorecard.updateScore(FOUR_OF_A_KIND, dice);
    std::cout << "Full House score : " << scorecard.getFullHouse() << "\n";

    // Small Straight
    scorecard.updateScore(SMALL_STRAIGHT, dice);
    std::cout << "Small Straight score : " << scorecard.getSmallStraight() << "\n";

    dice = { 1, 6, 2, 3, 4 };
    scorecard.updateScore(SMALL_STRAIGHT, dice);
    std::cout << "Small Straight score : " << scorecard.getSmallStraight() << "\n";

    dice = { 1, 4, 2, 3, 5 };
    scorecard.updateScore(SMALL_STRAIGHT, dice);
    std::cout << "Small Straight score : " << scorecard.getSmallStraight() << "\n";

    dice = { 1, 4, 6, 3, 5 };
    scorecard.updateScore(SMALL_STRAIGHT, dice);
    std::cout << "Small Straight score : " << scorecard.getSmallStraight() << "\n";

    dice = { 1, 2, 4, 5, 6 };
    scorecard.updateScore(SMALL_STRAIGHT, dice);
    std::cout << "Small Straight score : " << scorecard.getSmallStraight() << "\n";

    // Large Straight
    scorecard.updateScore(LARGE_STRAIGHT, dice);
    std::cout << "Large Straight score : " << scorecard.getLargeStraight() << "\n";

    dice = { 1, 2, 3, 4, 5 };
    scorecard.updateScore(LARGE_STRAIGHT, dice);
    std::cout << "Large Straight score : " << scorecard.getLargeStraight() << "\n";

    dice = { 2, 3, 4, 5, 6 };
    scorecard.updateScore(LARGE_STRAIGHT, dice);
    std::cout << "Large Straight score : " << scorecard.getLargeStraight() << "\n";

    scorecard.updateScore(YAHTZEE, dice);
    std::cout << "Yahtzee score : " << scorecard.getYahtzee() << "\n";

    dice = { 1, 1, 1, 1, 1 };
    scorecard.updateScore(YAHTZEE, dice);
    std::cout << "Yahtzee score : " << scorecard.getYahtzee() << "\n";

    dice = { 1, 2, 3, 4, 5 };
    scorecard.updateScore(CHANCE, dice);
    std::cout << "Chance score : " << scorecard.getChance() << "\n";
}

void test2()
{
    // Set up the game
    std::vector<Player> players = { Player("Player 1"), Player("PLayer 2") };
    Game game(players);

    // Run the game with 1 extra round to check all outcomes
    for (int round = 1; round <= 16; ++round)
    {
        game.playRound();
    }

    // Display the final result
    game.showScores();
}

void test3()
{
    // Set up the game
    std::vector<Player> players = { Player("Player") };
    Game game(players);

    // Run the game until you get all outputs at least once (other than CHANCE)
    game.playRound2();
}

int main(/*int argc, char** argv*/)
{
    // Vector of function pointers
    std::vector<void(*)()> pTests = { test0, test1, test2, test3 };
    int test = 3;

    pTests[test]();

    return 0;
}