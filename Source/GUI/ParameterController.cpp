//
//  ParameterController.cpp
//  GoldRush
//
//  Created by Tommi Gröhn on 25.10.2015.
//
//

#include "ParameterController.h"

void ParameterController::bindToParameter (AudioProcessorParameter* target)
{
    this->target = target;
}

AudioProcessorParameter* ParameterController::getTargetParameter()
{
    return target;
}
