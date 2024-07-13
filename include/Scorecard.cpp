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

void Scorecard::updateScore(unsigned category, const std::vector<int> &dice)
{
    // Range check
    assert(category > 0 && (category - 1) < mCategoryFilled.size() && "updateScore category out of bounds");

    // Since most scoring functions use the count of the dice for checking the
    // score, it is beneficial to just count the dice once then pass it along
    // when computing the score
    std::map<int, int> counts = countDice(dice);

    switch (category) {
        case 1: mAces = scoreForValue(counts, 1); break;
        case 2: mTwos = scoreForValue(counts, 2); break;
        case 3: mThrees = scoreForValue(counts, 3); break;
        case 4: mFours = scoreForValue(counts, 4); break;
        case 5: mFives = scoreForValue(counts, 5); break;
        case 6: mSixes = scoreForValue(counts, 6); break;
        case 7: mPair = scorePair(counts); break;
        case 8: mTwoPairs = scoreTwoPairs(counts); break;
        case 9: mThreeOfAKind = scoreThreeOfAKind(counts); break;
        case 10: mFourOfAKind = scoreFourOfAKind(counts); break;
        case 11: mFullHouse = scoreFullHouse(counts); break;
        case 12: mSmallStraight = scoreSmallStraight(counts); break;
        case 13: mLargeStraight = scoreLargeStraight(counts); break;
        case 14: mYahtzee = scoreYahtzee(counts); break;
        case 15: mChance = scoreChance(dice); break;
    }

    mCategoryFilled[category - 1] = true;
    calculateTotals();
}

int Scorecard::getTotalScore() const
{
    return mGrandTotal;
}

bool Scorecard::isCategoryFilled(unsigned category) const
{
    // Range check
    assert((category - 1) < mCategoryFilled.size() && "isCategoryFilled category out of bounds");
    return mCategoryFilled[category - 1];
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

std::map<int, int> Scorecard::countDice(const std::vector<int>& dice) const
{
    std::map<int, int> counts;
    for (int die : dice) {
        counts[die]++;
    }
    return counts;
}

int Scorecard::scoreForValue(const std::map<int, int>& counts, int value) const
{
    return counts.at(value) * value;
}

int Scorecard::scorePair(const std::map<int, int>& counts) const
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

int Scorecard::scoreTwoPairs(const std::map<int, int>& counts) const
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
        }
        // Account for both 2 and 3 of a kind as well
        if (count >= 2)
        {
            pairsCount++;
            score += dice * 2;
        }
    }
    // If a pair exists return the score, otherwise zero
    return (pairsCount >= 2) ? score : 0;
}

int Scorecard::scoreThreeOfAKind(const std::map<int, int>& counts) const
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

int Scorecard::scoreFourOfAKind(const std::map<int, int>& counts) const
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

int Scorecard::scoreFullHouse(const std::map<int, int>& counts) const
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

int Scorecard::scoreSmallStraight(const std::map<int, int>& counts) const
{
    std::vector<int> uniqueDice;
    // Use the counts to create a unique dice vector
    for (const auto& [dice, count] : counts)
    {
        uniqueDice.push_back(dice);
    }
    // Sort the vector for easier comparison
    std::ranges::sort(uniqueDice);

    // Three options for a small straight
    if (std::vector<int>{1, 2, 3, 4} == uniqueDice ||
        std::vector<int>{2, 3, 4, 5} == uniqueDice ||
        std::vector<int>{3, 4, 5, 6} == uniqueDice)
    {
        return 30;
    }
    // Small straight does not exist
    return 0;
}

int Scorecard::scoreLargeStraight(const std::map<int, int>& counts) const
{
    std::vector<int> uniqueDice;
    // Use the counts to create a unique dice vector
    for (const auto& [dice, count] : counts)
    {
        uniqueDice.push_back(dice);
    }
    // Sort the vector for easier comparison
    std::ranges::sort(uniqueDice);

    // Two options for a large straight
    if (std::vector<int>{1, 2, 3, 4, 5} == uniqueDice ||
        std::vector<int>{2, 3, 4, 5, 6} == uniqueDice)
    {
        return 40;
    }
    // Large straight does not exist
    return 0;
}

int Scorecard::scoreYahtzee(const std::map<int, int>& counts) const
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

int Scorecard::scoreChance(const std::vector<int>& dice) const
{
    int score = 0;
    // Simple summation of all dice
    for (int die : dice)
    {
        score += die;
    }
    return score;
}


