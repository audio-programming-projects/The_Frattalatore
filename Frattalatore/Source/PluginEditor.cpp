/*-
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
FrattalatoreAudioProcessorEditor::FrattalatoreAudioProcessorEditor (FrattalatoreAudioProcessor& p):
    AudioProcessorEditor (&p),
    audioProcessor (p),
    keyboardComponent(p.getKeyboardState(), juce::MidiKeyboardComponent::horizontalKeyboard),
    osc1(audioProcessor.apvts, "OSC1TYPE", "OSC1GAIN", "OSC1PITCH", "OSC1FMFREQ", "OSC1FMDEPTH","/juce/osc1", 7000),
    osc2(audioProcessor.apvts, "OSC2TYPE", "OSC2GAIN", "OSC2PITCH", "OSC2FMFREQ", "OSC2FMDEPTH","/juce/osc2", 7001),
    osc3(audioProcessor.apvts, "OSC3TYPE", "OSC3GAIN", "OSC3PITCH", "OSC3FMFREQ", "OSC3FMDEPTH","/juce/osc3", 7002),
    osc4(audioProcessor.apvts, "OSC4TYPE", "OSC4GAIN", "OSC4PITCH", "OSC4FMFREQ", "OSC4FMDEPTH","/juce/osc4", 7003),
    osc5(audioProcessor.apvts, "OSC5TYPE", "OSC5GAIN", "OSC5PITCH", "OSC5FMFREQ", "OSC5FMDEPTH","/juce/osc5", 7004),
    filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE"),
    adsr(audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    lfo(audioProcessor.apvts, "LFOFREQ", "LFODEPTH")

{
    logoCapr = juce::ImageCache::getFromMemory(BinaryData::LOGO_Capr_png, BinaryData::LOGO_Capr_pngSize);
    logoCapr = logoCapr.rescaled(160, 160);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(keyboardComponent);

    LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);
    //Oscillator parameters
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc3);
    addAndMakeVisible(osc4);
    addAndMakeVisible(osc5);

    //Filter
    addAndMakeVisible(filter);

    //LFO
    addAndMakeVisible(lfo);

    //adsr sliders
    addAndMakeVisible(adsr);

    osc1.setComponentName("OSCILLATOR1");
    osc2.setComponentName("OSCILLATOR2");
    osc3.setComponentName("OSCILLATOR3");
    osc4.setComponentName("OSCILLATOR4");
    osc5.setComponentName("OSCILLATOR5");
    filter.setComponentName("FILTER");
    lfo.setComponentName("LFO");
    adsr.setComponentName("ADSR");

    auto oscColour = juce::Colours::indianred;
    auto filterColour = oscColour;

    osc1.setBoundsColour(oscColour);
    osc2.setBoundsColour(oscColour);
    osc3.setBoundsColour(oscColour);
    osc4.setBoundsColour(oscColour);
    osc5.setBoundsColour(oscColour);
    filter.setBoundsColour(filterColour);
    lfo.setBoundsColour(filterColour);

    setSize(900, 600);
    startTimer(400);
}

FrattalatoreAudioProcessorEditor::~FrattalatoreAudioProcessorEditor()
{
}

//==============================================================================
void FrattalatoreAudioProcessorEditor::paint(juce::Graphics& g)
{

 //   g.fillAll(juce::Colours::black);
    g.setOpacity(0.4f);
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::mandelbrotBackgroundImg_png, BinaryData::mandelbrotBackgroundImg_pngSize).rescaled(900, 600 - 120);
    g.drawImageAt(backgroundImage,0,0);
    g.setOpacity(1.0f);
    g.drawImageAt(logoCapr, getWidth() / 2.0 - 90, getHeight() / 2.0);

   
    juce::Rectangle<float> border(0, 0, getWidth(), getHeight() - keyboardComponent.getHeight());
    g.setColour(juce::Colours::darkslategrey);
    g.drawRoundedRectangle(border, 8.0f, 5.0f);

    /*juce::Rectangle<float> border2(0, 0, getWidth(), getHeight() - keyboardComponent.getHeight()-2);
    g.setColour(juce::Colours::orangered);
    g.drawRoundedRectangle(border2,3.0f, 1.5f);*/
    
    g.setFont(juce::Font("Algerian", 20.0f, juce::Font::bold));
    g.setColour(juce::Colours::darkorange);
    g.setFont(fontSize);
    g.setFont(g.getCurrentFont().boldened());

    g.drawText("FRATTALATORE", getWidth() / 2.0 - 75.0, getHeight() - 180.0, 150.0, 50.0, juce::Justification::centred);
}

void FrattalatoreAudioProcessorEditor::resized()
{
    //positioning all the graphical components in the right place

    const auto oscWidth = 180;
    const auto oscHeight = 280;
    osc1.setBounds(0, 0, oscWidth, oscHeight);
    osc2.setBounds(osc1.getRight(), 0, oscWidth, oscHeight);
    osc3.setBounds(osc2.getRight(), 0, oscWidth, oscHeight);
    osc4.setBounds(osc3.getRight(), 0, oscWidth, oscHeight);
    osc5.setBounds(osc4.getRight(), 0, oscWidth, oscHeight);

    filter.setBounds(0, osc5.getBottom(), oscWidth, 200);
    lfo.setBounds(filter.getRight(), osc5.getBottom(), oscWidth, 200);
    adsr.setBounds(osc3.getRight(), osc4.getBottom(),oscWidth*2, 200);

    keyboardComponent.setBounds(0,filter.getBottom(), getWidth(), 120);
}

void FrattalatoreAudioProcessorEditor::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}


