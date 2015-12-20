/*
  ==============================================================================

    LinearInterpolator.h
    Created: 16 Oct 2015 12:16:12pm
    Author:  Tommi Gröhn

  ==============================================================================
*/

#ifndef LINEARINTERPOLATOR_H_INCLUDED
#define LINEARINTERPOLATOR_H_INCLUDED

#include "Interpolator.h"

class LinearInterpolator : public Interpolator {
public:
    LinearInterpolator() : interpolationSteps(0), inputBuffer(0.0f) {}
   
    LinearInterpolator(unsigned int steps) : interpolationSteps(steps), inputBuffer(0.0f) {}
    
    void setInterpolationSteps (unsigned int steps) noexcept override;
    
    bool interpolate (float input, float& output) noexcept override;
    
private:
    unsigned int interpolationSteps;
    unsigned int counter;
    float step;
    float inputBuffer;
};



#endif  // LINEARINTERPOLATOR_H_INCLUDED
