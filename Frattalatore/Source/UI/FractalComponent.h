/*
  ==============================================================================

    FractalComponent.h
    Created: 9 May 2022 11:53:16am
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuiComponent.h"

//==============================================================================
/*
*/
class FractalComponent  : public juce::Component
{
public:
    FractalComponent();
    ~FractalComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    static constexpr int windowWidth{ 600 };
    static constexpr int windowHeight{ 600 };
    juce::ComboBox fractalChoiceBox;
    juce::ComboBox numPointsChoice;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FractalComponent)
};
