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

// Keeps track of all scores placed in each category while playing
class Scorecard
{
  public:
    // update the score of a given category
    void updateScore(int category, int score);
    // compute the total score of the scorecard
    [[nodiscard]] int getTotalScore() const;

  private:
    // Score tracking variables
    // Aces, Twos, Threes, ... etc. or possible an array of values
    // 0 is a valid score so something to track if a category is used
};

#endif // YAHTZEE_SCORECARD_H
