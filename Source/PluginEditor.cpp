#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

GoldRushAudioProcessorEditor::GoldRushAudioProcessorEditor (GoldRushAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Set editor size
    setSize (editorWidth, editorHeight);
    
    // Load custom layout and behavior
    setLookAndFeel (&lookAndFeel);
    
    // Editor refresh rate - timerCallback() will be called at given interval
    startTimerHz(30.0);

    // Initialize knobs and labels
    knobLabels[0].setText ("Hi Cut", dontSendNotification);
    knobLabels[1].setText ("Resonance", dontSendNotification);
    knobs[0].setRange (0.0, 1.0, 1e-5);
    knobs[1].setRange (0.0, 0.8, 1e-5);
    buttons[0].setName ("STEEP");
    
    for (unsigned int i = 0; i < knobCount; ++i)
    {
        ParameterController& knob = knobs[i];
        Label& label = knobLabels[i];
        float processorKnobValue = processor.parameters[i]->getValue();
        addAndMakeVisible (&knob);
        addAndMakeVisible (&label);
        knob.bindToParameter (processor.parameters[i]);
        knob.addListener (this);
        knob.setSliderStyle (Slider::RotaryVerticalDrag);
        knob.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
        knob.setPopupDisplayEnabled (false, this);
        knob.setValue (processorKnobValue);
        label.setFont (lookAndFeel.getDefaultLabelFont());
        label.setJustificationType (Justification::centred);
    }

    for (unsigned int i = 0; i < buttonCount; ++i)
    {
        VintageToggleButton& sw = buttons[i];
        bool& processorSwValue = processor.buttonValues[i];
        addAndMakeVisible (&sw);
        sw.addListener (this);
        sw.setToggleState (processorSwValue, dontSendNotification);
    }
}

GoldRushAudioProcessorEditor::~GoldRushAudioProcessorEditor()
{
}

//==============================================================================
void GoldRushAudioProcessorEditor::paint (Graphics& g)
{
    // Editor background
    g.setGradientFill(ColourGradient(Colours::darkgrey.withBrightness (0.3), editorWidth / 2, 0,
                                     Colours::black, editorWidth / 2, editorHeight * 2.0,
                                     true));
    g.fillAll ();
    
    // Logo
    g.setFont (goldRushFonts::logoFont.withHeight (32.0f));
    g.setColour (Colours::antiquewhite);
    g.drawFittedText ("PRIME B L O C K S DSP", Rectangle<int> (logoX, logoY, 300, 50),
                      Justification::centred,
                      1);

    g.setFont (goldRushFonts::handWriteFont.withHeight(72.0f));
    g.setColour (Colours::antiquewhite);
    g.drawFittedText ("Gold Rush Filter", Rectangle<int> (logoX, logoY + 50, 300, 50),
                      Justification::centred,
                      1);
}

void GoldRushAudioProcessorEditor::resized()
{
    // set knob positions
    for (int i = 0; i < knobsOnColumn; ++i)
    {
        for (int j = 0; j < knobsOnRow && i * knobsOnRow + j < knobCount; ++j)
        {
            knobs[i * knobsOnRow + j].setBounds (knobTopLeftX + j * horizontalKnobSpacing,
                                                 knobTopLeftY + i * verticalKnobSpacing,
                                                 knobSize,
                                                 knobSize);
            knobLabels[i * knobsOnRow + j].setBounds (knobTopLeftX + j * horizontalKnobSpacing - knobSize / 2 - 5,
                                                      knobTopLeftY + i * verticalKnobSpacing + knobSize,
                                                      2 * knobSize,
                                                      knobSize / 3);
        }
    }

    // set button positions
    for (int i = 0; i < buttonCount; ++i)
    {
        buttons[i].setBounds (buttonTopLeftX + i * buttonSpacing,
                               buttonTopLeftY,
                               buttonSize * 2,
                               buttonSize * 2);
    }
}

void GoldRushAudioProcessorEditor::lookAndFeelChanged()
{
}


void GoldRushAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    // update parameter values in AudioProcessor
    for (int i = 0; i < knobCount; ++i) processor.parameters[i]->setValueNotifyingHost (knobs[i].getValue());
}

void GoldRushAudioProcessorEditor::sliderDragStarted (Slider* slider)
{
    static_cast<ParameterController*>(slider)->getTargetParameter()->beginChangeGesture();
}

void GoldRushAudioProcessorEditor::sliderDragEnded (Slider* slider)
{
    static_cast<ParameterController*>(slider)->getTargetParameter()->endChangeGesture();
}

void GoldRushAudioProcessorEditor::buttonClicked (Button* button)
{
    for (int i = 0; i < buttonCount; ++i) processor.buttonValues[i] = buttons[i].getToggleState();
}

void GoldRushAudioProcessorEditor::timerCallback()
{
    for (int i = 0; i < knobCount; ++i)
    {
        knobs[i].setValue (processor.parameters[i]->getValue(), dontSendNotification);
    }

    for (int i = 0; i < buttonCount; ++i)
    {
        buttons[i].setToggleState (processor.buttonValues[i], dontSendNotification);
    }
}
