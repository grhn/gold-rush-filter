//
//  ResonantLowPassFilter.h
//  GoldRush
//
//  Created by Tommi Gröhn on 10.10.2015.
//
//

#ifndef __GoldRush__ResonantLowPassFilter__
#define __GoldRush__ResonantLowPassFilter__

#include "LowPassFilter.h"

class ResonantLowPassFilter : public LowPassFilter {
public:
    ResonantLowPassFilter();

    ResonantLowPassFilter(const unsigned int poles) : LowPassFilter(poles), resonance(0.0) {}
    
    ResonantLowPassFilter(const unsigned int poles, const double cornerFrequency)
        : LowPassFilter(poles),
          resonance(0.0)
    {
        setCornerFrequency (cornerFrequency);
    }

    void process (double& sample, unsigned int channel) noexcept override;
    
    void setResonance (double res) noexcept;
    
protected:
    double resonance;
    double sampleFeedbackBuffer[32] = {0.0};
};

#endif /* defined(__GoldRush__ResonantLowPassFilter__) */
