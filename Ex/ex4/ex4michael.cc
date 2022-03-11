/*
 * File: ex4c.cc
 * Find loops in a series
 * Written by: Michael Shustin, id = 209349034, login = shustinmi
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * Receives 8 numbers that form a series, and print the first loop in the series
 * When treating the values as references to another index in the series,
 * A loop when the series of values created by jumping to the referenced indices
 * creates an infinitely repeating series.
 * The first loop is the loop that contains the lowest index.
 *
 * Compile: g++ -o ex4c -Wall -Wextra -Werror ex4c.cc
 * Run: ./ex4c
 * Input: 8 Integers that form a series
 * Input Example: 2 5 4 5 18 6 3 99
 * Output: The first loop
 * Output Example: 3 5 6
 */
//-------------- include section --------------
#include <iostream>
#include <cstdlib>

//-------------- using section --------------
using std::cout;

//-------------- const and enum section --------------
const int SERIES_LENGTH = 8;


//-------------- main --------------
int main()
{
    // Store the series the user inputs
    int series[SERIES_LENGTH];

    // Store which values we went over, to prevent looping infinitely
    bool occurred[SERIES_LENGTH] = { false };

    // Store the index we're currently traversing through
    int seriesIndex;

    // Store th first index in the loop.
    // This is important to identify the first loop.
    int firstIndex;

    // Exit flag that indicates the loop was found
    bool loopFound = false;

    // Iterate over the array and fill it with user input
    for (int i = 0; i < SERIES_LENGTH; i++)
    {
        std::cin >> series[i];
    }

    for (int i = 0; i < SERIES_LENGTH; i++)
    {
        firstIndex = i;
        seriesIndex = i;
        // Index is out of scope - so we're not in a loop
        while (seriesIndex >= 0 && seriesIndex < SERIES_LENGTH) {
            // Set true to indicate we've been here
            occurred[seriesIndex] = true;
            // Traverse to the next value
            seriesIndex = series[seriesIndex];

            // Only say we found the loop if it has firstIndex in it.
            // This ensures that we always return the first loop
            if (seriesIndex == firstIndex)
            {
                loopFound = true;
                break;
            }
            // If this value occurred before, we found a loop that
            // isn't the first, so we don't set loopFound
            else if (occurred[seriesIndex])
            {
                break;
            }
        }

        // If the loop was found, we already know its starting index
        if (loopFound)
        {
            // Start traversing through the series, but this time we know
            // that we are traversing through a closed loop.
            seriesIndex = firstIndex;
            do {
                // Print the index we're currently on
                cout << seriesIndex << " ";
                // Traverse to the next index
                seriesIndex = series[seriesIndex];
            // We can assume that it's the first loop,
            // this means we can end when we get to the firstIndex
            } while (seriesIndex != firstIndex);

            // End the line and break the main loop.
            cout << std::endl;
            break;
        }

        // Reset the occurred array because we haven't found the lowest loop,
        // and we're going to try again
        for (int j = 0; j < SERIES_LENGTH; j++)
        {
            occurred[j] = false;
        }
    }

    return EXIT_SUCCESS;
}
