/******************************************************************************/
/*!
\file   D6.cpp
\author Kenneth Onulak
\par    Yahtzee
\date   07/11/2024
\brief
    Implementation of the standard six sided dice.
*/
/******************************************************************************/

#include "D6.h"

D6::D6()
    : value(0) // invlaid until rolled at least once
    , mGenerator(mRandomDevice())
    , mDistribution(1, 6)
{}

void D6::roll()
{
    value = mDistribution(mGenerator);
}

int D6::getValue() const
{
    return value;
}