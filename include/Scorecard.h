/******************************************************************************/
/*!
\file   Scorecard.h
\author Kenneth Onulak
\par    Yahtzee
\date   07/11/2024
\brief
    Used to track a players individual score.
*/
/******************************************************************************/
#ifndef YAHTZEE_SCORECARD_H
#define YAHTZEE_SCORECARD_H

#include <array>
#include <map>
#include <vector>

// Keeps track of all scores placed in each category while playing
class Scorecard
{
  public:
    // Initialize the scorecard
    Scorecard() = default;
    // Update the score of a given category
    void updateScore(int category, const std::vector<int>& dice);
    // Compute the total score of the scorecard
    [[nodiscard]] int getTotalScore() const;
    // Check if a category has already been filled
    bool isCategoryFilled(unsigned category) const;

  private:
    // Upper section
    int mAces = 0;
    int mTwos = 0;
    int mThrees = 0;
    int mFours = 0;
    int mFives = 0;
    int mSixes = 0;

    int mUpperSectionTotal = 0;
    int mUpperSectionBonus = 0;

    // Additional scores based on coding challenge
    int mPair = 0;
    int mTwoPairs = 0;

    // Lower section
    int mThreeOfAKind = 0;
    int mFourOfAKind = 0;
    int mFullHouse = 0;
    int mSmallStraight = 0;
    int mLargeStraight = 0;
    int mYahtzee = 0;
    int mChance = 0;

    int mYahtzeeBonus = 0;
    int mLowerSectionTotal = 0;

    int mGrandTotal = 0;

    // Track if a category has been filled (accepts scores of 0)
    std::array<bool, 15> mCategoryFilled = {
        false, false, false, false, false,
        false, false, false, false, false,
        false, false, false, false, false,
    };

    ////////////////////////////////////////////////////////////////////////////
    // Private Methods

    // Compute the grand total score
    void calculateTotals();
    // Helper function to count the values of each dice
    std::map<int, int> countDice(const std::vector<int>& dice) const;
    // Helper function for getting score for Aces through Sixes
    int scoreForValue(const std::map<int, int>& counts, int value) const;
    // Compute the score for pair
    int scorePair(const std::map<int, int>& counts) const;
    // Compute the score for two pairs
    int scoreTwoPairs(const std::map<int, int>& counts) const;
    // Compute the score for three of a kind
    int scoreThreeOfAKind(const std::map<int, int>& counts) const;
    // Compute the score for four of a kind
    int scoreFourOfAKind(const std::map<int, int>& counts) const;
    // Compute the score of full house
    int scoreFullHouse(const std::map<int, int>& counts) const;
    // Compute the score for small straight
    int scoreSmallStraight(const std::map<int, int>& counts) const;
    // Compute the score for large straight
    int scoreLargeStraight(const std::map<int, int>& counts) const;
    // Compute the score for yahtzee
    int scoreYahtzee(const std::map<int, int>& counts) const;
    // Compute the score for chance
    int scoreChance(const std::vector<int>& dice) const;






};

#endif // YAHTZEE_SCORECARD_H
