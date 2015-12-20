# Gold Rush Filter
Low-pass filter section of analog modeling real-time audio plug-in "Gold Rush", which will be a commercial release during spring 2016. Plug-in implements discrete time approximation of series connected RC-filters.

## Dependencies
+ JUCE framework
+ VST SDK
+ AudioUnit SDK

For actual use, some audio plug-in host supporting some of the VST / VST3 / AudioUnit plug-in formats is required.

## Controls
#### Hi Cut
Adjusts the corner frequency of the filter
#### Resonance
Adjusts the amount of negative feedback in the filter circuit
#### Steep
Toggles the filter steepness between two modes (24 dB / octave and 48 dB / octave or 4th order and 8th order RC-filters, respectively)

## Prototyping
MATLAB prototype of the algorithm and some plots (amplitude and phase response) can be found from the Matlab/ folder.