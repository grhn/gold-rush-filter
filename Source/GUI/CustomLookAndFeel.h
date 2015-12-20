//
//  CustomLookAndFeel.h
//  GoldRush
//
//  Created by Tommi Gröhn on 13.10.2015.
//
//

#ifndef __GoldRush__CustomLookAndFeel__
#define __GoldRush__CustomLookAndFeel__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Fonts/goldRushFonts.h"

// LookAndFeel
class CustomLookAndFeel : public LookAndFeel_V3 {
public:
    CustomLookAndFeel();
    Font getDefaultLabelFont();
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
private:
    float driveGlow;
    Font defaultLabelFont;
    Colour fadeColour;
    Colour bgColour;
    Colour needleColour;

};

#endif /* defined(__GoldRush__CustomLookAndFeel__) */
