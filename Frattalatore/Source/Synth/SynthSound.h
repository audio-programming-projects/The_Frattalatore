/*
  ==============================================================================

    SynthSound.h
    Created: 30 Apr 2022 11:11:57am
    Author:  claud

  ==============================================================================
*/

#pragma once

// calling juce projects
#include <JuceHeader.h>
class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; };
    bool appliesToChannel(int midiChannel) override { return true; };
    
};