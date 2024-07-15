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

// Enum to make using the scorecard easier
enum Category {
    ACES = 1,
    TWOS,
    THREES,
    FOURS,
    FIVES,
    SIXES,
    PAIR,
    TWO_PAIRS,
    THREE_OF_A_KIND,
    FOUR_OF_A_KIND,
    FULL_HOUSE,
    SMALL_STRAIGHT,
    LARGE_STRAIGHT,
    YAHTZEE,
    CHANCE
};

// Keeps track of all scores placed in each category while playing
class Scorecard
{
  public:
    // Initialize the scorecard
    Scorecard() = default;
    // Update the score of a given category
    void updateScore(Category category, const std::vector<int>& dice);
    // Compute the total score of the scorecard
    [[nodiscard]] int getTotalScore() const;
    // Check if a category has already been filled
    bool isCategoryFilled(Category category) const;
    // Helper function to count the values of each dice
    static std::map<int, int> countDice(const std::vector<int>& dice) ;
    // Get the category with the best scoring potential
    int getMaxScoreCategory(const std::vector<int> & rolledDice, bool overrideFilledCategory) const;
    // Get the points for a specific category
    int getScore(Category category) const;

    // Getter methods for each category
    int getAces() const { return mAces; }
    int getTwos() const { return mTwos; }
    int getThrees() const { return mThrees; }
    int getFours() const { return mFours; }
    int getFives() const { return mFives; }
    int getSixes() const { return mSixes; }
    int getPair() const { return mPair; }
    int getTwoPairs() const { return mTwoPairs; }
    int getUpperSectionTotal() const { return mUpperSectionTotal; }
    int getUpperSectionBonus() const { return mUpperSectionBonus; }
    int getThreeOfAKind() const { return mThreeOfAKind; }
    int getFourOfAKind() const { return mFourOfAKind; }
    int getFullHouse() const { return mFullHouse; }
    int getSmallStraight() const { return mSmallStraight; }
    int getLargeStraight() const { return mLargeStraight; }
    int getYahtzee() const { return mYahtzee; }
    int getChance() const { return mChance; }

  private:
    // Upper section                Category
    int mAces = 0;               // 1
    int mTwos = 0;               // 2
    int mThrees = 0;             // 3
    int mFours = 0;              // 4
    int mFives = 0;              // 5
    int mSixes = 0;              // 6

    int mUpperSectionTotal = 0;
    int mUpperSectionBonus = 0;

    // Additional scores based on coding challenge
    int mPair = 0;               // 7
    int mTwoPairs = 0;           // 8

    // Lower section
    int mThreeOfAKind = 0;       // 9
    int mFourOfAKind = 0;        // 10
    int mFullHouse = 0;          // 11
    int mSmallStraight = 0;      // 12
    int mLargeStraight = 0;      // 13
    int mYahtzee = 0;            // 14
    int mChance = 0;             // 15

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
    // Helper function for getting score for Aces through Sixes
    static int scoreForValue(const std::map<int, int>& counts, int value) ;
    // Compute the score for pair
    static int scorePair(const std::map<int, int>& counts) ;
    // Compute the score for two pairs
    static int scoreTwoPairs(const std::map<int, int>& counts) ;
    // Compute the score for three of a kind
    static int scoreThreeOfAKind(const std::map<int, int>& counts) ;
    // Compute the score for four of a kind
    static int scoreFourOfAKind(const std::map<int, int>& counts) ;
    // Compute the score of full house
    static int scoreFullHouse(const std::map<int, int>& counts) ;
    // Compute the score for small straight
    static int scoreSmallStraight(const std::map<int, int>& counts) ;
    // Compute the score for large straight
    static int scoreLargeStraight(const std::map<int, int>& counts) ;
    // Compute the score for yahtzee
    static int scoreYahtzee(const std::map<int, int>& counts) ;
    // Compute the score for chance
    static int scoreChance(const std::vector<int>& dice) ;
};

#endif // YAHTZEE_SCORECARD_H
