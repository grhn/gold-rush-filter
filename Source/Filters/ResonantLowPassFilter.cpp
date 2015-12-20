//
//  ResonantLowPassFilter.cpp
//  GoldRush
//
//  Created by Tommi Gröhn on 10.10.2015.
//
//

#include "ResonantLowPassFilter.h"
#include <cmath>

ResonantLowPassFilter::ResonantLowPassFilter () : LowPassFilter()
{
    resonance = 0.0;
    tau = 1.0;
}

inline void ResonantLowPassFilter::process (double& sample, unsigned int channel) noexcept {

    sample -= resonance * sampleFeedbackBuffer[channel];
    LowPassFilter::process(sample, channel);
    sampleFeedbackBuffer[channel] = sample;
    sample *= 1.0 + resonance;

}

void ResonantLowPassFilter::setResonance (double res) noexcept {
    resonance = res * 0.99;
}