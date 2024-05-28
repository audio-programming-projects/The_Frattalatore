/*
  ==============================================================================

    FliterData.h
    Created: 4 May 2022 4:43:30pm
    Author:  claud

  ==============================================================================
*/

#pragma once
#include "OscData.h"
#include <JuceHeader.h>

class FilterData : public juce::dsp::StateVariableTPTFilter<float>
{
public:
    FilterData();
    void FilterData::prepareToPlay (double sampleRate, int samplePerBlock, int numChannels);
    void FilterData::updateParameters(const int filterType, const float cutOff, const float resonance);
    void FilterData::processNextBlock(juce::AudioBuffer<float>& buffer);
    float FilterData::processNextSample(int channel, float input);
    void FilterData::resetFilter();
private:
    juce::dsp::Oscillator<float> lfo{ [](float x) { return std::sin(x); } };
    void FilterData::selectFilterType(const int filterType);
    bool isPrepared{ false };
};