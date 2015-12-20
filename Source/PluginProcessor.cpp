#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>
#include <string>
#include <algorithm>


GoldRushAudioProcessor::GoldRushAudioProcessor()
{
    sampleRate = getSampleRate();
    resonantLowPassFilter.bindSampleRate (&sampleRate);
    
    addParameter (parameters[0] = new FloatParameter (0.0, 0.0, "Hi Cut", "Hz"));
    addParameter (parameters[1] = new FloatParameter (0.0, 0.0, "Resonance"));
    
    // Set number of interpolation steps for parameter value interpolation
    for (auto& i : interpolator)
    {
        i.setInterpolationSteps (2048);
    }
}

GoldRushAudioProcessor::~GoldRushAudioProcessor()
{
}

const String GoldRushAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

const String GoldRushAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String GoldRushAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool GoldRushAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool GoldRushAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool GoldRushAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GoldRushAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GoldRushAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double GoldRushAudioProcessor::getTailLengthSeconds() const
{
    return 1.0;
}

int GoldRushAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GoldRushAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GoldRushAudioProcessor::setCurrentProgram (int index)
{
}

const String GoldRushAudioProcessor::getProgramName (int index)
{
    return String();
}

void GoldRushAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void GoldRushAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Set current sample rate
    this->sampleRate = sampleRate;
}

void GoldRushAudioProcessor::releaseResources()
{
}

void GoldRushAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // Process all samples in all channels
    for (unsigned int i = 0, numInputChannels = getNumInputChannels(), numOfSamples = buffer.getNumSamples(); i < numOfSamples; ++i)
    {
        // Interpolate adjustments made in parameter values to avoid clicks in audio
        valueHasChanged = false;
        for (unsigned int k = 0; k < knobCount; ++k)
        {
            valueHasChanged |= interpolator[k].interpolate (parameters[k]->getValue(), smoothedKnobValues[k]);
        }
        
        if (valueHasChanged)
        {
            // Apply interpolated parameter adjustments
            resonantLowPassFilter.setCornerFrequency (loPass > 1.0e-5 ? 40.0 * std::pow (10.0, (1.0 - loPass) * 3.0) : 120.0e3);
            resonantLowPassFilter.setResonance (loPass > 1.0e-5 ? resonance : 0.0);
        }
        
        resonantLowPassFilter.setPoles (filterSteep ? 8 : 4);
        
        // Processing
        for (unsigned int channel = 0; channel < numInputChannels; ++channel)
        {
            // Read sample to buffer
            channelBuffer = buffer.getWritePointer (channel);
            sample = channelBuffer[i];
            
            // Apply filter
            resonantLowPassFilter.process (sample, channel);
            channelBuffer[i] = sample;
        }
    }
}

bool GoldRushAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* GoldRushAudioProcessor::createEditor()
{
    return new GoldRushAudioProcessorEditor (*this);
}

void GoldRushAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml ("MYPLUGINSETTINGS");
    
    for (int i = 0; i < knobCount; ++i)
    {
        const std::string attributeName = "parameter" + std::to_string(i);
        xml.setAttribute (Identifier(attributeName), parameters[i]->getValue());
    }
    
    for (int i = 0; i < buttonCount; ++i)
    {
        const std::string attributeName = "button" + std::to_string(i);
        xml.setAttribute (Identifier(attributeName), buttonValues[i]);
    }
    
    copyXmlToBinary (xml, destData);
}

void GoldRushAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            for (int i = 0; i < knobCount; ++i)
            {
                const std::string attributeName = "parameter" + std::to_string(i);
                parameters[i]->setValue (xmlState->getDoubleAttribute (StringRef(attributeName), 0));
            }
            
            for (int i = 0; i < buttonCount; ++i)
            {
                const std::string attributeName = "button" + std::to_string(i);
                buttonValues[i] = xmlState->getBoolAttribute (StringRef(attributeName), false);
            }
        }
    }
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GoldRushAudioProcessor();
}
