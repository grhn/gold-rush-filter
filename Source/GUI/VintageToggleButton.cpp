//
//  VintageToggleButton.cpp
//  GoldRush
//
//  Created by Tommi Gröhn on 26.10.2015.
//
//

#include "VintageToggleButton.h"

VintageToggleButton::VintageToggleButton (Colour baseColour, Colour switchColour) : baseColour (baseColour), switchColour (switchColour)
{
}

void VintageToggleButton::setLabel (String s)
{
    label = s;
}


void VintageToggleButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    const float w = getWidth();
    const float h = getHeight();
    const float rounding = 2.0f;
    const float edgeSize = 2.0f;
    
    // Draw base
    {
        Path p;
        g.setGradientFill(ColourGradient(Colours::darkgrey, 0, 0,
                                         Colours::black, 0 + w / 8.0, h,
                                         false));
        p.addRoundedRectangle (0, 0, w, h,
                               rounding, rounding,
                               rounding, rounding,
                               rounding, rounding);
        g.fillPath (p);
        g.fillPath (p);
    }
    
    // Draw button
    {
        Path p;
        if (getToggleState())
        {
            g.setGradientFill(ColourGradient(Colours::red, w / 2, h / 3,
                                             Colours::darkred.darker(), 0, h,
                                             true));
            p.addRoundedRectangle (edgeSize, edgeSize, w - edgeSize * 2.0, h - edgeSize * 2.0,
                                   rounding, rounding,
                                   rounding, rounding,
                                   rounding, rounding);
            g.fillPath (p);
        }
        else
        {
            g.setGradientFill(ColourGradient(Colours::red.withBrightness (0.3), 0, 0,
                                             Colours::red.withBrightness (0.1), 0, h,
                                             false));
            p.addRoundedRectangle (edgeSize, edgeSize, w - edgeSize * 2.0, h - edgeSize * 2.0,
                                   rounding, rounding,
                                   rounding, rounding,
                                   rounding, rounding);
            g.fillPath (p);
        }
    }
    
    // Draw label on top of button
    {
        const float margin = 2.0;
        g.setFont (goldRushFonts::logoFont.withHeight(14.0f));
        g.setColour (Colours::antiquewhite);
        g.drawFittedText (getName(), Rectangle<int> (margin, margin, getWidth() - 2.0 * margin, getHeight() - 2.0 * margin),
                          Justification::centred,
                          2);
    }
  
}
