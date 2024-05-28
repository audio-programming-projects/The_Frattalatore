/*
  ==============================================================================

    AdsrData.h
    Created: 2 May 2022 9:44:11am
    Author:  claud
    Encapsulating the ADSR functionalities in the class
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;

};