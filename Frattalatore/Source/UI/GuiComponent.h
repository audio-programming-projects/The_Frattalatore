/*
  ==============================================================================

    DesignComponent.h
    Created: 6 May 2022 1:25:41pm
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

static constexpr float fontSize{ 15.0f };

/* class that abstracts the creation of sliders with labels */
class SliderWithLabel : public juce::Component
{
public:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using SliderStyle = juce::Slider::SliderStyle;

    SliderWithLabel(juce::String labelName, juce::String paramId, juce::AudioProcessorValueTreeState& apvts,
        const int width, const int height, SliderStyle style = SliderStyle::RotaryHorizontalVerticalDrag);

    void resized() override;
    juce::Slider& getGuiSlider() { return this->guiSlider; };
    juce::Label& getGuiLabel() { return this->guiLabel; };

private:
    static constexpr int textBoxWidth{ 48 };
    static constexpr int textBoxHeight{ 20 };
    int sliderWidth{ 0 };
    int sliderHeight{ 0 };
    juce::Slider guiSlider;
    juce::Label guiLabel;
    std::unique_ptr<SliderAttachment> guiSliderAttachment;
};


/* General component: parent class of the components of each element */
class GuiComponent : public juce::Component
{
public:
    GuiComponent();
    ~GuiComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void setComponentName(juce::String name) { guiComponentName = name; }
    void setBoundsColour(juce::Colour colour) { boundsColour = colour; }

private:
    juce::String guiComponentName{ "" };
    juce::Colour boundsColour{ juce::Colours::indianred };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiComponent)
};

