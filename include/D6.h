/******************************************************************************/
/*!
\file   D6.h
\author Kenneth Onulak
\par    Yahtzee
\date   07/11/2024
\brief
    Standard six sided dice.
*/
/******************************************************************************/
#ifndef YAHTZEE_D6_H
#define YAHTZEE_D6_H

#include "Dice.h"
#include <random>

// Standard D6 dice
class D6 : public Dice
{
  public:
    // Seeds the generator
    D6();
    // Generates a random value representing a roll
    void roll() override;
    // Get the last value rolled
    [[nodiscard]] int getValue() const override;

  private:
    int value;                                     // Last value rolled
    std::random_device mRandomDevice;              // Used to obtain a random number
    std::mt19937 mGenerator;                       // Seed the generator
    std::uniform_int_distribution<> mDistribution; // Defined range of random numbers

};
#endif // YAHTZEE_D6_H
