/*
  ==============================================================================

    LinearInterpolator.cpp
    Created: 16 Oct 2015 12:16:12pm
    Author:  Tommi Gröhn

  ==============================================================================
*/

#include "LinearInterpolator.h"

void LinearInterpolator::setInterpolationSteps (unsigned int steps) noexcept
{
    interpolationSteps = steps;
}

inline bool LinearInterpolator::interpolate (float input, float& output) noexcept
{
    if (inputBuffer != input)
    {
        counter = 0;
        step = (input - output) / interpolationSteps;
        inputBuffer = input;
    }
    
    if (counter < interpolationSteps)
    {
        output += step;
        counter++;
        return true;
    }
    else
    {
        return false;
    }
}
