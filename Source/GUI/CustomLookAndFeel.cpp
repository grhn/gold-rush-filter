//
//  CustomLookAndFeel.cpp
//  GoldRush
//
//  Created by Tommi Gröhn on 13.10.2015.
//
//

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    setColour (Label::textColourId , Colour (Colours::antiquewhite));
    setColour (Slider::rotarySliderFillColourId , Colour (Colours::antiquewhite.withBrightness (0.7)));
    setColour (Slider::rotarySliderOutlineColourId, Colour (Colours::black));

    setColour (Slider::backgroundColourId , Colour (Colours::darkorange));
    setColour (Slider::thumbColourId, Colour (Colours::ivory));
    setColour (Slider::trackColourId, Colour (Colours::transparentBlack));

    defaultLabelFont = goldRushFonts::handWriteFont.withHeight(25.0f);
    defaultLabelFont.setHorizontalScale (1.0f);

    driveGlow = 0.0f;
    fadeColour = Colours::white;
    bgColour = Colours::darkgrey.darker (1.0f);
    needleColour = Colours::antiquewhite;
}

Font CustomLookAndFeel::getDefaultLabelFont()
{
    return defaultLabelFont;
}

void CustomLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                       const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    const float radius = jmin (width / 4, height / 4);
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const float innerRadius = radius * 0.7f;
  
    // Draw base
    {
        g.setGradientFill(ColourGradient(Colours::black, centreX, centreY,
                                         fadeColour, centreX, centreY - radius * 1.5f,
                                         false));

        Path p;
        p.addEllipse(centreX - radius, centreY - radius, rw, rw);
        
        g.fillPath (p);
    }
    
    // Draw "chicken head"
    {
        g.setGradientFill(ColourGradient(slider.findColour (Slider::rotarySliderFillColourId),
                                         centreX, centreY,
                                         fadeColour, centreX, centreY - rw * 1.5f,
                                         false));

        Path p;
        p.startNewSubPath(-innerRadius * 0.7f, rw * 0.8f);
        p.quadraticTo(-rw * 0.2f, -rw, 0.0f, -rw);
        p.quadraticTo(rw * 0.2f , -rw, innerRadius * 0.7f, rw * 0.8f);
        p.closeSubPath();
        p.addEllipse (-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);
        
        g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
    }
    
    // Draw pointer line
    {
        g.setColour(slider.findColour (Slider::rotarySliderOutlineColourId).withAlpha(0.7f));

        Path p;
        p.addLineSegment (Line<float> (0.0f, -radius * 0.5f, 0.0f, -rw), radius * 0.1f);

        g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
    }
}

