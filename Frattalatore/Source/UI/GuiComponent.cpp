/*
  ==============================================================================

    GuiComponent.cpp
    Created: 6 May 2022 1:25:41pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GuiComponent.h"

//===============IMPLEMENTATION OF SliderWithLabel===================================

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

SliderWithLabel::SliderWithLabel(juce::String labelName, juce::String paramId, juce::AudioProcessorValueTreeState& apvts, 
    const int width, const int height, SliderStyle style)
{
    sliderWidth = width;
    sliderHeight = height;


    guiSlider.setSliderStyle(style);
    guiSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, textBoxWidth, textBoxHeight);
    guiSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(guiSlider);

    guiLabel.setFont(fontSize);
    guiLabel.setText(labelName, juce::dontSendNotification);
    guiLabel.setJustificationType(juce::Justification::centred);
    //guiLabel.setColour(juce::Label::textColourId, juce::Colours::antiquewhite);
    addAndMakeVisible(guiLabel);

    guiSliderAttachment = std::make_unique<SliderAttachment>(apvts, paramId, guiSlider);
}


void SliderWithLabel::resized()
{
    const auto dialToLabelRatio = 15;
    const auto labelHeight = 18;

    jassert(sliderWidth > 0);
    jassert(sliderHeight > 0);

    guiLabel.setBounds(0, 0, sliderWidth, labelHeight);
    guiSlider.setBounds(0, 0 + dialToLabelRatio, sliderWidth, sliderHeight);
}

//===============IMPLEMENTATION OF GuiComponent===================================
GuiComponent::GuiComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

GuiComponent::~GuiComponent()
{
}

void GuiComponent::paint(juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
    g.setFont(juce::Font("Algerian", 20.0f, juce::Font::bold));
    auto bounds = getLocalBounds();
    g.setColour(boundsColour);
    g.drawRoundedRectangle(bounds.toFloat().reduced(10.0f), 5.0f, 3.5f);
    
    g.setColour(juce::Colours::orangered);
    g.setFont(fontSize);
    g.setFont(g.getCurrentFont().boldened());

    jassert(guiComponentName.isNotEmpty());
    g.drawText(guiComponentName, getWidth()/2.0 - 50, 15, 100, 25, juce::Justification::centred);
}

void GuiComponent::resized()
{
}

