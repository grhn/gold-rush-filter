//
//  Interpolator.h
//  GoldRush
//
//  Created by Tommi Gröhn on 18.10.2015.
//
//

#ifndef __GoldRush__Interpolator__
#define __GoldRush__Interpolator__

class Interpolator {
public:
    Interpolator() : interpolationSteps(0), inputBuffer(0.0f) {}
    
    Interpolator(unsigned int steps) : interpolationSteps(steps), inputBuffer(0.0f) {}
    
    virtual ~Interpolator() {}
    
    virtual void setInterpolationSteps (unsigned int steps) = 0;
    
    /* Returns true if output changes, false otherwise. */
    virtual bool interpolate (float input, float& output) = 0;
    
protected:
    unsigned int interpolationSteps;
    unsigned int counter;
    float step;
    float inputBuffer;
};
#endif /* defined(__GoldRush__Interpolator__) */
