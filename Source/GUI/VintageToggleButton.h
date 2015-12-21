//
//  VintageToggleButton.h
//  GoldRush
//
//  Created by Tommi Gröhn on 26.10.2015.
//
//

#ifndef __GoldRush__VintageToggleButton__
#define __GoldRush__VintageToggleButton__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Fonts/goldRushFonts.h"

class VintageToggleButton : public ToggleButton
{
public:
    VintageToggleButton (Colour baseColour = Colours::black, Colour switchColour = Colours::grey);
    
    void setLabel (String s);
    
    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown) override;

private:
    Colour baseColour, switchColour;
    String label;
};

#endif /* defined(__GoldRush__VintageToggleButton__) */
