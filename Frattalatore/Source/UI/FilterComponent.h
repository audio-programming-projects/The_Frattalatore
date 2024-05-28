/*
  ==============================================================================

    FilterComponent.h
    Created: 4 May 2022 5:27:45pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuiComponent.h"
//==============================================================================
/*
*/
class FilterComponent  : public GuiComponent
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, 
        juce::String filterTypeSelectorId, 
        juce::String filterCutOffId, juce::String filterResId);
    ~FilterComponent() override;

    void resized() override;

private:
    juce::ComboBox typeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    SliderWithLabel cutOff;
    SliderWithLabel resonance;

    static constexpr int dialWidth = 70;
    static constexpr int dialHeight = 70;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
