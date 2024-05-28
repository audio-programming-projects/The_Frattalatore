/*
  ==============================================================================
    LfoComponent.h
    Created: 06 May 2022 8:12:35pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuiComponent.h"

//==============================================================================
/*
*/
class LfoComponent : public GuiComponent
{
public:
    LfoComponent(juce::AudioProcessorValueTreeState& apvts, juce::String lfoFreqId, juce::String lfoDepthId);
    ~LfoComponent() override;

    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    SliderWithLabel lfoFreq;
    SliderWithLabel lfoDepth;

    static constexpr int dialWidth = 70;
    static constexpr int dialHeight = 70;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LfoComponent)
};