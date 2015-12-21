//
//  ParameterController.h
//  GoldRush
//
//  Created by Tommi Gröhn on 25.10.2015.
//
//

#ifndef __GoldRush__ParameterController__
#define __GoldRush__ParameterController__

#include "../JuceLibraryCode/JuceHeader.h"

class ParameterController : public Slider
{
public:
    void bindToParameter (AudioProcessorParameter* target);
    
    AudioProcessorParameter* getTargetParameter();
    
private:
    AudioProcessorParameter* target;
    Colour headColour;

};

#endif /* defined(__GoldRush__ParameterController__) */
