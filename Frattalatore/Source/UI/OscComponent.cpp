/*
  ==============================================================================
    OscComponent.cpp
    Created: 5 May 2022 4:55:21pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli
  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"
//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts,
    juce::String waveSelectorId,
    juce::String gainId,
    juce::String pitchId,
    juce::String fmFreqId,
    juce::String fmDepthId,
    juce::String fmOSCAddressPattern,
    int port):
        gain("Gain", gainId, apvts, dialWidth, dialHeight),
        pitch("Pitch", pitchId, apvts, dialWidth, dialHeight),
        fmFreq("FM Freq", fmFreqId, apvts, dialWidth, dialHeight),
        fmDepth("FM Depth", fmDepthId, apvts, dialWidth, dialHeight)
{
    //OSC
    if (!connect(port)) showConnectionErrorMessage("Error: could not connect to UDP port");
    addListener(this, fmOSCAddressPattern);
    OSCAddressPattern = fmOSCAddressPattern;

    //GUI Components
    juce::StringArray oscChoices { "Sine", "Saw", "Square" };
    oscTypeSelector.addItemList(oscChoices, 1);
    oscTypeSelector.setSelectedItemIndex(0);
    addAndMakeVisible(oscTypeSelector);

    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscTypeSelector);
    addAndMakeVisible(gain);
    addAndMakeVisible(pitch);
    addAndMakeVisible(fmFreq);
    addAndMakeVisible(fmDepth);
}

OscComponent::~OscComponent()
{
}

void OscComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.getAddressPattern().toString() == OSCAddressPattern)
        if (message.size() == 4
            && message[0].isInt32()
            && message[1].isInt32()
            && message[2].isFloat32()
            && message[3].isFloat32())
        {
            this->fmDepth.getGuiSlider().setValue(juce::jlimit(0.0f,100.0f,convertingIterationsInFMDepthRange(message[1].getInt32(), message[0].getInt32())));
            float freq = computingModulusCoordinatesForFMFreq(message[2].getFloat32(), message[3].getFloat32());
            this->fmFreq.getGuiSlider().setValue(juce::jlimit(0.0f, 20.0f, freq));
        }
}

float OscComponent::convertingIterationsInFMDepthRange(const int iterations, const int maxIterations)
{
    int oldRange = maxIterations - 1;
    float newRange = 100.0f;
    float newValue = (((iterations - 1) * newRange) / oldRange) + 0.0f;
    return newRange - newValue;
}

float OscComponent::computingModulusCoordinatesForFMFreq(float x, float y)
{
    return sqrt((x * x) + (y * y));
}


void OscComponent::showConnectionErrorMessage(const juce::String& messageText)
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
        "Connection error",
        messageText,
        "OK");
}


void OscComponent::resized()
{
    const auto yStart = 15;
    const auto width = 70;
    const auto height = 88;

    oscTypeSelector.setBounds(18, 40, 140, 25);
    gain.setBounds(oscTypeSelector.getX(), oscTypeSelector.getBottom()+10, width, height);
    pitch.setBounds(oscTypeSelector.getX()+70, oscTypeSelector.getBottom()+10, width, height);
    fmFreq.setBounds(oscTypeSelector.getX(), gain.getBottom(), width, height);
    fmDepth.setBounds(oscTypeSelector.getX()+70, pitch.getBottom(), width, height);
}
