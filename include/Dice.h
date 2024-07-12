/******************************************************************************/
/*!
\file   Dice.h
\author Kenneth Onulak
\par    Yahtzee
\date   07/11/2024
\brief
    Base structure for any dice created.
*/
/******************************************************************************/
#ifndef YAHTZEE_DICE_H
#define YAHTZEE_DICE_H

// Base class for all Dice
class Dice
{
  public:
    // Generates a random value representing a roll
    virtual void roll() = 0;
    // Get the last value rolled
    virtual int getValue() const = 0;

    virtual ~Dice() {}
};

#endif // YAHTZEE_DICE_H
