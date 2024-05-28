/*
  ==============================================================================

    OscComponent.h
    Created: 3 May 2022 12:41:18pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuiComponent.h"
//==============================================================================
/*
*/
class OscComponent  : public GuiComponent,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, 
    juce::String waveSelectorId,
    juce::String gainId,
    juce::String pitchId,
    juce::String fmFreqId,
    juce::String fmDepthId,
    juce::String fmOSCAddressPattern,
        int OSCPort);
    ~OscComponent() override;
    void resized() override;
    void oscMessageReceived(const juce::OSCMessage& message) override;
    float convertingIterationsInFMDepthRange(const int iterations, const int maxIterations);
    float computingModulusCoordinatesForFMFreq(float x, float y);
    void showConnectionErrorMessage(const juce::String& messageText);

private:
    juce::ComboBox oscTypeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;

    SliderWithLabel gain;
    SliderWithLabel pitch;
    SliderWithLabel fmFreq;
    SliderWithLabel fmDepth;

    juce::String OSCAddressPattern {""};

    static constexpr int dialWidth = 70;
    static constexpr int dialHeight = 70;

protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
