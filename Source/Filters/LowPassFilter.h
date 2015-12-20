//
//  LowPassFilter.h
//  GoldRush
//
//  Created by Tommi Gröhn on 2.10.2015.
//
//

#ifndef __GoldRush__LowPassFilter__
#define __GoldRush__LowPassFilter__

#include "AnalogFilter.h"

class LowPassFilter : public AnalogFilter {
    public:
        LowPassFilter();
        
        LowPassFilter(const unsigned int poles);
    
        LowPassFilter(const unsigned int poles, const double cornerFrequency);
    
        void setPoles (unsigned int p) noexcept override;
    
        void setCornerFrequency(double frequency) noexcept override;
    
        void process (double& sample, unsigned int channel) noexcept override;
    };

#endif /* defined(__GoldRush__LowPassFilter__) */
