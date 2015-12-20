#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "juce_Timer.h"
#include "GUI/CustomLookAndFeel.h"
#include "GUI/ParameterController.h"
#include "GUI/VintageToggleButton.h"
#include "Fonts/goldRushFonts.h"

class GoldRushAudioProcessorEditor  : public AudioProcessorEditor,
                                      private ParameterController::Listener,
                                      private Button::Listener,
                                      private Timer
{
public:
    GoldRushAudioProcessorEditor (GoldRushAudioProcessor&);
    ~GoldRushAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void lookAndFeelChanged () override;
    void sliderValueChanged (Slider* slider) override;
    void sliderDragStarted (Slider* slider) override;
    void sliderDragEnded (Slider* slider) override;
    void buttonClicked (Button* button);
    void timerCallback() override;

private:
    GoldRushAudioProcessor& processor;
    CustomLookAndFeel lookAndFeel;

    static const unsigned int editorWidth = 400;
    static const unsigned int editorHeight = 300;
    static const unsigned int logoX = 50;
    static const unsigned int logoY = 30;
        
    static const unsigned char knobsOnRow = 3;
    static const unsigned char knobsOnColumn = 3;
    static const unsigned char knobCount = 2;
    static const unsigned int knobSize = 80;
    static const unsigned int horizontalKnobSpacing = 1.5 * knobSize;
    static const unsigned int verticalKnobSpacing = 2.0 * knobSize;
    static const unsigned int knobTopLeftX = 50;
    static const unsigned int knobTopLeftY = 160;
    
    static const unsigned char buttonCount = 1;
    static const unsigned int buttonSize = 25;
    static const unsigned int buttonSpacing = buttonSize * 2 + 10;
    static const unsigned int buttonTopLeftX = 300;
    static const unsigned int buttonTopLeftY = 180;
    
    ParameterController knobs[knobCount];
    VintageToggleButton buttons[buttonCount];
    Label knobLabels[knobCount];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GoldRushAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
