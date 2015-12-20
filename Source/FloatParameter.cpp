//
//  FloatParameter.cpp
//  GoldRush
//
//  Created by Tommi Gröhn on 25.10.2015.
//
//

#include "FloatParameter.h"

float FloatParameter::getValue() const
{
    return value;
}

void FloatParameter::setValue (float newValue)
{
    value = newValue;
}

float FloatParameter::getDefaultValue() const
{
    return defaultValue;
}

String FloatParameter::getName (int maximumStringLength) const
{
    return name.substring (0, maximumStringLength);
}

String FloatParameter::getLabel() const
{
    return label;
}

float FloatParameter::getValueForText (const String& text) const
{
    return text.getFloatValue();
}
