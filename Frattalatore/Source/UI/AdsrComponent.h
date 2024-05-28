/*
  ==============================================================================

    AdsrComponent.h
    Created: 2 May 2022 9:43:01am
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuiComponent.h"
//==============================================================================
/*
*/
class AdsrComponent  : public GuiComponent
{
public:
    AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts, 
        juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId);
    ~AdsrComponent() override;

    void resized() override;
    using SliderStyle = juce::Slider::SliderStyle;

private:

    static constexpr int sliderWidth = 85;
    static constexpr int sliderHeight = 80;

    SliderWithLabel attack;
    SliderWithLabel decay;
    SliderWithLabel sustain;
    SliderWithLabel release;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
