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

int main(/*int argc, char** argv*/)
{
    // Vector of function pointers
    std::vector<void(*)()> pTests = { test0 };
    int test = 0;

    pTests[test]();

    return 0;
}