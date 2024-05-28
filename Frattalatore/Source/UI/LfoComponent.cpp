/*
  ==============================================================================

    LfoComponent.cpp
    Created: 6 May 2022 12:41:18pm
    Author:  claud

  ==============================================================================
*/
#include <JuceHeader.h>
#include "LfoComponent.h"

//==============================================================================
LfoComponent::LfoComponent(juce::AudioProcessorValueTreeState& apvts, 
    juce::String lfoFreqId, 
    juce::String lfoDepthId):
        lfoFreq("LFO Freq", lfoFreqId, apvts, dialWidth, dialHeight),
        lfoDepth("LFO Depth", lfoDepthId, apvts, dialWidth, dialHeight)
{
    addAndMakeVisible(lfoFreq);
    addAndMakeVisible(lfoDepth);
}

LfoComponent::~LfoComponent()
{
}

void LfoComponent::resized()
{
    const auto width = 70;
    const auto height = 88;
    const auto startX = getWidth()/2.0 - 40;
    const auto startY = getHeight()/2.0 - height/2.0 + 5;

    lfoFreq.setBounds(startX - width / 2.0, startY, width, height);
    lfoDepth.setBounds(startX + width / 2.0 + 5, startY, width, height);
}