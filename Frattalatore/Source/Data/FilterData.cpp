/*
  ==============================================================================

    FilterData.cpp
    Created: 4 May 2022 4:43:30pm
    Author:  claud

  ==============================================================================
*/

#include "FilterData.h"

FilterData::FilterData()
{
    setType(juce::dsp::StateVariableTPTFilterType::lowpass);
}

void FilterData::updateParameters(const int filterType, const float cutOff, const float resonance)
{
    selectFilterType(filterType);
    setCutoffFrequency(cutOff);
    setResonance(resonance);
}


void FilterData::prepareToPlay(double sampleRate, int samplePerBlock, int numChannels)
{
    resetFilter();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplePerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    prepare(spec);
    lfo.prepare(spec);
    isPrepared = true;

}

void FilterData::selectFilterType(const int filterType)
{
    switch (filterType)
    {
    case 0:
        setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    case 1:
        setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;
    case 2:
        setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;
    default:
        setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    }
}

void FilterData::resetFilter()
{
    reset();
    lfo.reset();
}

void FilterData::processNextBlock(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block{ buffer };
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

float FilterData::processNextSample(int channel, float input)
{
    lfo.processSample(input);
    return processSample(channel, input);
}


