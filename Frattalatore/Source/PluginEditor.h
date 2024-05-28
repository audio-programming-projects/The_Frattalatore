/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/CustomLookAndFeel.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/AdsrComponent.h"
#include "UI/LfoComponent.h"


//==============================================================================
/**
*/
class FrattalatoreAudioProcessorEditor  :   public juce::AudioProcessorEditor,
                                            private juce::Timer
{
public:
    FrattalatoreAudioProcessorEditor (FrattalatoreAudioProcessor&);
    ~FrattalatoreAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    FrattalatoreAudioProcessor& audioProcessor;
    OscComponent osc1, osc2, osc3, osc4, osc5;
    FilterComponent filter;
    AdsrComponent adsr;
    LfoComponent lfo;

    CustomLookAndFeel customLookAndFeel;
    juce::Image logoCapr, backgroundImage;

    void timerCallback() override;
    juce::MidiKeyboardComponent keyboardComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrattalatoreAudioProcessorEditor)
};


