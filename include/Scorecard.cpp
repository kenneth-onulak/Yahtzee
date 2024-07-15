/******************************************************************************/
/*!
\file   Scorecard.cpp
\author Kenneth Onulak
\par    email: kenneth.onulakjr\@digipen.edu
\par    DigiPen login: kenneth.onulakjr
\par    Course: $COURSE
\par    Term: $TERM 2024
\par    Section: $SECTION
\par    Assignment #Yahtzee
\date   07/11/2024
\brief
    This file contains the implementation of the Scorecard class.
*/
/******************************************************************************/

#include "Scorecard.h"
#include <algorithm> // std::sort
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
// Public Methods

void Scorecard::updateScore(Category category, const std::vector<int> &dice)
{
    // Since most scoring functions use the count of the dice for checking the
    // score, it is beneficial to just count the dice once then pass it along
    // when computing the score
    std::map<int, int> counts = countDice(dice);

    switch (category)
    {
        case ACES: mAces = scoreForValue(counts, 1); break;
        case TWOS: mTwos = scoreForValue(counts, 2); break;
        case THREES: mThrees = scoreForValue(counts, 3); break;
        case FOURS: mFours = scoreForValue(counts, 4); break;
        case FIVES: mFives = scoreForValue(counts, 5); break;
        case SIXES: mSixes = scoreForValue(counts, 6); break;
        case PAIR: mPair = scorePair(counts); break;
        case TWO_PAIRS: mTwoPairs = scoreTwoPairs(counts); break;
        case THREE_OF_A_KIND: mThreeOfAKind = scoreThreeOfAKind(counts); break;
        case FOUR_OF_A_KIND: mFourOfAKind = scoreFourOfAKind(counts); break;
        case FULL_HOUSE: mFullHouse = scoreFullHouse(counts); break;
        case SMALL_STRAIGHT: mSmallStraight = scoreSmallStraight(counts); break;
        case LARGE_STRAIGHT: mLargeStraight = scoreLargeStraight(counts); break;
        case YAHTZEE: mYahtzee = scoreYahtzee(counts); break;
        case CHANCE: mChance = scoreChance(dice); break;
    }

    mCategoryFilled[category - 1] = true;
    calculateTotals();
}

int Scorecard::getTotalScore() const
{
    return mGrandTotal;
}

bool Scorecard::isCategoryFilled(Category category) const
{
    // Using an enum for the category removes the need for a range check
    return mCategoryFilled[category - 1];
}

std::map<int, int> Scorecard::countDice(const std::vector<int>& dice)
{
    std::map<int, int> counts;
    for (int die : dice) {
        counts[die]++;
    }
    return counts;
}

int Scorecard::getMaxScoreCategory(const std::vector<int> & rolledDice, bool overrideFilledCategory) const
{
    int maxScore = 0;       // The maximum score for the rolled dice
    int bestCategory = -1;  // The category the produces the maximum score
    std::map<int, int> counts = countDice(rolledDice);

    // Check all categories and determine the best one
    for (int category = ACES; category <= CHANCE; ++category)
    {
        int score = 0;
        if (overrideFilledCategory || !isCategoryFilled(static_cast<Category>(category)))
        {
            switch (category)
            {
                case ACES: score = scoreForValue(counts, 1); break;
                case TWOS: score = scoreForValue(counts, 2); break;
                case THREES: score = scoreForValue(counts, 3); break;
                case FOURS: score = scoreForValue(counts, 4); break;
                case FIVES: score = scoreForValue(counts, 5); break;
                case SIXES: score = scoreForValue(counts, 6); break;
                case PAIR: score = scorePair(counts); break;
                case TWO_PAIRS: score = scoreTwoPairs(counts); break;
                case THREE_OF_A_KIND: score = scoreThreeOfAKind(counts); break;
                case FOUR_OF_A_KIND: score = scoreFourOfAKind(counts); break;
                case FULL_HOUSE: score = scoreFullHouse(counts); break;
                case SMALL_STRAIGHT: score = scoreSmallStraight(counts); break;
                case LARGE_STRAIGHT: score = scoreLargeStraight(counts); break;
                case YAHTZEE: score = scoreYahtzee(counts); break;
                // case CHANCE: score = scoreChance(rolledDice); break;
            }

            if (score > maxScore)
            {
                maxScore = score;
                bestCategory = category;
            }
        }
    }

    return bestCategory;
}

int Scorecard::getScore(Category category) const
{
    switch (category)
    {
        case ACES: return mAces;
        case TWOS: return mTwos;
        case THREES: return mThrees;
        case FOURS: return mFours;
        case FIVES: return mFives;
        case SIXES: return mSixes;
        case PAIR: return mPair;
        case TWO_PAIRS: return mTwoPairs;
        case THREE_OF_A_KIND: return mThreeOfAKind;
        case FOUR_OF_A_KIND: return mFourOfAKind;
        case FULL_HOUSE: return mFullHouse;
        case SMALL_STRAIGHT: return mSmallStraight;
        case LARGE_STRAIGHT: return mLargeStraight;
        case YAHTZEE: return mYahtzee;
        case CHANCE: return mChance;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Private Methods

void Scorecard::calculateTotals()
{
    mUpperSectionTotal = mAces + mTwos + mThrees + mFours + mFives + mSixes;
    mUpperSectionBonus = (mUpperSectionTotal >= 63) ? 35 : 0;
    mLowerSectionTotal = mPair + mTwoPairs + mThreeOfAKind + mFourOfAKind + mFullHouse + mSmallStraight + mLargeStraight + mYahtzee + mChance + mYahtzeeBonus;
    mGrandTotal = mUpperSectionTotal + mUpperSectionBonus + mLowerSectionTotal;
}

int Scorecard::scoreForValue(const std::map<int, int>& counts, int value)
{
    auto iter = counts.find(value);
    return iter != counts.end() ? iter->second * value : 0;
}

int Scorecard::scorePair(const std::map<int, int>& counts)
{
    int highestDiceValue = 0;
    // Find the highest valued pair
    for (const auto& [dice, count] : counts)
    {
        if (count >= 2 && dice > highestDiceValue)
        {
            highestDiceValue = dice;
        }
    }
    // If the pair exists return the score, otherwise 0
    return highestDiceValue * 2;
}

int Scorecard::scoreTwoPairs(const std::map<int, int>& counts)
{
    int pairsCount = 0;
    int score = 0;
    // Check for two pairs
    for (const auto& [dice, count] : counts)
    {
        // Four of a kind+ can be split into two pairs
        if (count >= 4)
        {
            pairsCount += 2;
            score += dice * 4;
        } // Account for both 2 and 3 of a kind as well
        else if (count >= 2)
        {
            pairsCount++;
            score += dice * 2;
        }
    }
    // If a pair exists return the score, otherwise zero
    return (pairsCount >= 2) ? score : 0;
}

int Scorecard::scoreThreeOfAKind(const std::map<int, int>& counts)
{
    for (const auto& [dice, count] : counts)
    {
        // Can treat more than three of a kind as three of a kind
        if (count >= 3) {
            return dice * 3;
        }
    }
    // Three of kind does not exist
    return 0;
}

int Scorecard::scoreFourOfAKind(const std::map<int, int>& counts)
{
    for (const auto& [dice, count] : counts)
    {
        // Can treat more than four of a kind as four of a kind
        if (count >= 4) {
            return dice * 4;
        }
    }
    // Dour of kind does not exist
    return 0;
}

int Scorecard::scoreFullHouse(const std::map<int, int>& counts)
{
    bool hasThree = false;
    bool hasTwo = false;

    for (const auto& [dice, count] : counts)
    {
        // Must use all 5 dice
        if (count == 3) hasThree = true;
        if (count == 2) hasTwo = true;
    }
    // Found a full house
    if (hasThree && hasTwo)
    {
        return 25;
    }
    // Full house does not exist
    return 0;
}

int Scorecard::scoreSmallStraight(const std::map<int, int>& counts)
{
    // A small straight must have at least 4 unique dice
    if (counts.size() < 4)
    {
        return 0;
    }

    // Use the counts to create populate a potential straight
    std::array<int, 6> straight = { 0, 0, 0, 0, 0, 0 };
    for (const auto& [dice, count] : counts)
    {
        straight[dice - 1]++;
    }

    // Check that there are no breaks in the straight
    int length = 0;
    int bestLength = 0;
    for (int const & dice : straight)
    {
        if (dice)
        {
            if (length > 0)
            {   // Continue the straight
                ++length;
            }
            else
            {   // Start a new run
                length = 1;
            }
        }
        else
        {   // No die at this index, reset the straight
            if (length > bestLength)
            {
                bestLength = length;
            }
            length = 0;
        }
    }

    // No straight found
    if (bestLength < 4 && length < 4)
    {
        return 0;
    }

    // Found a valid small straight
    return 30;
}

int Scorecard::scoreLargeStraight(const std::map<int, int>& counts)
{
    // Large straight must use all 5 dice
    if (counts.size() != 5)
    {
        return 0;
    }

    // Use the counts to create a unique dice vector
    std::vector<int> uniqueDice;
    for (const auto& [dice, count] : counts)
    {
        uniqueDice.push_back(dice);
    }
    // Sort the vector for easier comparison
    std::ranges::sort(uniqueDice);

    // Scoring a large straight is easier than scoring a small straight since
    // there are only two possible valid solutions with all dice being used
    if (std::vector<int>{1, 2, 3, 4, 5} == uniqueDice ||
        std::vector<int>{2, 3, 4, 5, 6} == uniqueDice)
    {
        return 40;
    }
    // Large straight does not exist
    return 0;
}

int Scorecard::scoreYahtzee(const std::map<int, int>& counts)
{
    // Could possibly early out when counts size is > 1 but counts max size is 5
    // so just checking all counts has a minimal cost to it
    for (const auto& [dice, count] : counts)
    {
        if (count == 5)
        {
            return 50;
        }
    }
    // Yahtzee does not exist
    return 0;
}

int Scorecard::scoreChance(const std::vector<int>& dice)
{
    int score = 0;
    // Simple summation of all dice
    for (int die : dice)
    {
        score += die;
    }
    return score;
}


