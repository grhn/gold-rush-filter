#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <cmath>

#include "../JuceLibraryCode/JuceHeader.h"
#include "FloatParameter.h"
#include "Filters/ResonantLowPassFilter.h"
#include "Utility/LinearInterpolator.h"

class GoldRushAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    GoldRushAudioProcessor();
    ~GoldRushAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    friend class GoldRushAudioProcessorEditor;
    
private:
    //==============================================================================
    static const unsigned char knobCount = 2;
    static const unsigned char buttonCount = 1;

    AudioProcessorEditor* editor = nullptr;
    LinearInterpolator interpolator[knobCount];
    ResonantLowPassFilter resonantLowPassFilter;

    AudioProcessorParameter* parameters[knobCount];
    bool buttonValues[buttonCount] = {false};

    float smoothedKnobValues[knobCount] = {0.0};
    
    float& loPass           = smoothedKnobValues[0];
    float& resonance        = smoothedKnobValues[1];
    bool& filterSteep       = buttonValues[0];

    bool valueHasChanged;
    double sampleRate;
    double sample;
    float* channelBuffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GoldRushAudioProcessor)

};


#endif  // PLUGINPROCESSOR_H_INCLUDED
