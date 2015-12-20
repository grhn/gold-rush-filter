//
//  LowPassFilter.cpp
//  GoldRush
//
//  Created by Tommi Gröhn on 2.10.2015.
//
//

#include <cmath>

#include "LowPassFilter.h"

LowPassFilter::LowPassFilter ()
{
    poles = 1;
    setCornerFrequency(1.0e5);
}

LowPassFilter::LowPassFilter(const unsigned int poles) : AnalogFilter ()
{
    this->poles = poles;
    setCornerFrequency(1.0e5);
}

LowPassFilter::LowPassFilter (const unsigned int poles, const double cornerFrequency) : AnalogFilter ()
{
    this->poles = poles;
    this->cornerFrequency = cornerFrequency;
    setCornerFrequency(cornerFrequency);
}

void LowPassFilter::setPoles(unsigned int p) noexcept
{
    if (p > 0 and p <= 32 and p % 2 == 0) poles = p;
    setCornerFrequency (cornerFrequency);
}

inline void LowPassFilter::setCornerFrequency (double frequency) noexcept
{
    cornerFrequency = frequency;
    // tau = 1.0 / (1.0 + frequency / (0.5 * poles)) * (44100.0 / (sampleRate ? *sampleRate : 44100.0));
    
    if (poles > 0)
    {
        tau = 1.0 / (2.0 * pi * cornerFrequency)
                   * (sampleRate ? *sampleRate : 44100.0)
                   * std::sqrt (std::pow (2.0, 1.0 / poles) - 1.0);
    }
}

inline void LowPassFilter::process (double& sample, unsigned int channel) noexcept
{
    cap_ptr = caps[channel];
    for (int p = 0; p < poles; p++, cap_ptr++)
    {
        *cap_ptr += (sample - *cap_ptr) / (1.0 + tau);
        sample = *cap_ptr;
    }
}

