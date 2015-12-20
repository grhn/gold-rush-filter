#ifndef GoldRush_AnalogFilterTemplates_h
#define GoldRush_AnalogFilterTemplates_h

template <typename SampleType>
inline SampleType AnalogFilter::getProcessed (SampleType sample, unsigned int channel) noexcept
{
    double sample2 = sample;
    process (sample2, channel);
    return sample2;
}

#endif
