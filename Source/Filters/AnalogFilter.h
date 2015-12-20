//
//  AnalogFilters.h
//  GoldRush
//
//  Created by Tommi Gröhn on 2.10.2015.
//
//

#ifndef __GoldRush__AnalogFilters__
#define __GoldRush__AnalogFilters__

class AnalogFilter {
public:
    AnalogFilter() {}
    
    AnalogFilter(const unsigned int p) : poles(p) {}
    
    AnalogFilter(const unsigned int p, const double cf) : poles(p), cornerFrequency(cf) {}

    virtual ~AnalogFilter() {}

    void bindSampleRate (double* sampleRate) { this->sampleRate = sampleRate; }
    
    virtual void setPoles (unsigned int p) noexcept = 0;
    
    virtual void setCornerFrequency (double frequency) noexcept = 0;
    
    virtual void process (double& buffer, unsigned int channel) noexcept = 0;
    
    template <typename SampleType>
    SampleType getProcessed (SampleType sample, unsigned int channel) noexcept;

protected:
    double* sampleRate = nullptr;
    double tau = 0.0;
    unsigned int poles = 1.0;
    double cornerFrequency = 1.0;
    double caps[32][32] = {0.0};
    double* cap_ptr;
    double sampleDelta = 0.0;
    double pi = 3.1415926535;
};

#include "AnalogFilterTemplates.h"


#endif /* defined(__GoldRush__AnalogFilters__) */
