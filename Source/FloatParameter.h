//
//  FloatParameter.h
//  GoldRush
//
//  Created by Tommi Gröhn on 25.10.2015.
//
//

#ifndef __GoldRush__PluginParameter__
#define __GoldRush__PluginParameter__

#include <string>

#include "../JuceLibraryCode/JuceHeader.h"

class FloatParameter : public AudioProcessorParameter
{
public:
    FloatParameter (float defaultValue = 0.0, float value = 0.0,
                    const String& name = "Unnamed Parameter", const String& label = String())
        : defaultValue  (defaultValue),
          value         (value),
          name          (name),
          label         (label)
    {
    }
    
    float getValue() const override;
 
    void setValue (float newValue) override;

    float getDefaultValue() const override;
    
    /** Returns the name to display for this parameter, which should be made
     to fit within the given string length.
     */
    String getName (int maximumStringLength) const override;
    
    /** Some parameters may be able to return a label string for
     their units. For example "Hz" or "%".
     */
    String getLabel() const override;

    /** Should parse a string and return the appropriate value for it. */
    float getValueForText (const String& text) const override;
    
private:
    float defaultValue;
    float value;
    String name;
    String label;
};

#endif /* defined(__GoldRush__PluginParameter__) */
