/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>
#include <iostream>
#include <tuple>

//==============================================================================
FrattalatoreAudioProcessor::FrattalatoreAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    //polyphonic synthesiser
    synth.addSound(new SynthSound());
    for (int v = 0; v < numVoices; v++) 
    {
        synth.addVoice(new SynthVoice());
    }
}

FrattalatoreAudioProcessor::/*destructor*/~FrattalatoreAudioProcessor()
{
}

//==============================================================================
const juce::String FrattalatoreAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FrattalatoreAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FrattalatoreAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FrattalatoreAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FrattalatoreAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FrattalatoreAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FrattalatoreAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FrattalatoreAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FrattalatoreAudioProcessor::getProgramName (int index)
{
    return {};
}

void FrattalatoreAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


void FrattalatoreAudioProcessor::showConnectionErrorMessage(const juce::String& messageText)
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
        "Connection error",
        messageText,
        "OK");
}
//==============================================================================
void FrattalatoreAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        //the next line returns a SynthesiserVoice object that does not have
        // our prepareToPlay definition => cast
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToplay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
}

void FrattalatoreAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FrattalatoreAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FrattalatoreAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    setParams();
    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}
//
////==============================================================================
bool FrattalatoreAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FrattalatoreAudioProcessor::createEditor()
{
    return new FrattalatoreAudioProcessorEditor (*this);
}

//==============================================================================
void FrattalatoreAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FrattalatoreAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FrattalatoreAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout FrattalatoreAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    /////////////////////////////////////OSC select and options//////////////////////////////////////////////////////////////////////
    //OSC1
        params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1TYPE", "Oscillator 1 Type", juce::StringArray
            { "Sine", "Saw", "Square" }, 0));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator 1 Gain", juce::NormalisableRange<float>
        { -60.0f, 0.2f, 0.1f }, 0.1f, "dB"));
        params.push_back(std::make_unique<juce::AudioParameterInt>("OSC1PITCH", "Oscillator 1 Pitch", -24, 24, 0));

    //OSC2
        params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2TYPE", "Oscillator 2 Type", juce::StringArray
            { "Sine", "Saw", "Square" }, 0));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Oscillator 2 Gain", juce::NormalisableRange<float>
        { -60.0f, 0.2f, 0.1f }, 0.1f, "dB"));
        params.push_back(std::make_unique<juce::AudioParameterInt>("OSC2PITCH", "Oscillator 2 Pitch", -24, 24, 0));

    //OSC3
        params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC3TYPE", "Oscillator 3 Type", juce::StringArray
            { "Sine", "Saw", "Square" }, 0));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3GAIN", "Oscillator 3 Gain", juce::NormalisableRange<float>
        { -60.0f, 0.2f, 0.1f }, 0.1f, "dB"));
        params.push_back(std::make_unique<juce::AudioParameterInt>("OSC3PITCH", "Oscillator 3 Pitch", -24, 24, 0));

    //OSC4
        params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC4TYPE", "Oscillator 4 Type", juce::StringArray
            { "Sine", "Saw", "Square" }, 0));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC4GAIN", "Oscillator 4 Gain", juce::NormalisableRange<float>
        { -60.0f, 0.2f, 0.1f }, 0.1f, "dB"));
        params.push_back(std::make_unique<juce::AudioParameterInt>("OSC4PITCH", "Oscillator 4 Pitch", -24, 24, 0));

    //OSC5
        params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC5TYPE", "Oscillator 5 Type", juce::StringArray
            { "Sine", "Saw", "Square" }, 0));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC5GAIN", "Oscillator 5 Gain", juce::NormalisableRange<float>
        { -60.0f, 0.2f, 0.1f }, 0.1f, "dB"));
        params.push_back(std::make_unique<juce::AudioParameterInt>("OSC5PITCH", "Oscillator 5 Pitch", -24, 24, 0));

    ////////////////////////////////////////////FM mod oscillators///////////////////////////////////////////////////////////////////

    //frequencies

    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "OSC 1 FM Frequency", juce::NormalisableRange<float>
    {0.0f, 20.0f, 0.1f}, defaultFMFreq));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2FMFREQ", "OSC 2 FM Frequency", juce::NormalisableRange<float>
    {0.0f, 20.0f, 0.1f}, defaultFMFreq));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3FMFREQ", "OSC 3 FM Frequency", juce::NormalisableRange<float>
    {0.0f, 20.0f, 0.1f}, defaultFMFreq));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC4FMFREQ", "OSC 4 FM Frequency", juce::NormalisableRange<float>
    {0.0f, 20.0f, 0.1f}, defaultFMFreq));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC5FMFREQ", "OSC 5 FM Frequency", juce::NormalisableRange<float>
    {0.0f, 20.0f, 0.1f}, defaultFMFreq));

    //depths

    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "OSC 1 FM Depth", juce::NormalisableRange<float>
    {0.0f, 100.0f, 0.1f, 0.3f}, defaultFMDepth));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2FMDEPTH", "OSC 2 FM Depth", juce::NormalisableRange<float>
    {0.0f, 100.0f, 0.1f, 0.3f}, defaultFMDepth));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3FMDEPTH", "OSC 3 FM Depth", juce::NormalisableRange<float>
    {0.0f, 100.0f, 0.1f, 0.3f}, defaultFMDepth));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC4FMDEPTH", "OSC 4 FM Depth", juce::NormalisableRange<float>
    {0.0f, 100.0f, 0.1f,0.3f}, defaultFMDepth));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC5FMDEPTH", "OSC 5 FM Depth", juce::NormalisableRange<float>
    {0.0f, 100.0f, 0.1f,0.3f}, defaultFMDepth));

    ///////////////////////////////////////////////////////LFO//////////////////////////////////////////////////////////////////

    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFOFREQ", "LFO Frequency", juce::NormalisableRange<float>
    { 0.0f, 20.0f, 0.1f }, 0.0f, "Hz"));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFODEPTH", "LFO Depth", juce::NormalisableRange<float>
    { 0.0f, 10000.0f, 0.1f, 0.3f}, 0.0f, ""));

    //Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", 
        juce::StringArray{ "LPF", "BPF", "HPF" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter CutOff", juce::NormalisableRange<float>
    {20.0f, 20000.0f, 0.1f, 0.6f}, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRESONANCE", "Filter Resonance", juce::NormalisableRange<float>
    {0.1f, 1.0f, 0.1f}, 0.1f));

    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>
    {0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>
    {0.1f, 1.0f, 0.1f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>
    {0.1f, 1.0f, 0.1f, }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>
    {0.1f, 3.0f, 0.1f, }, 0.4f));
    return { params.begin(), params.end() };
}

void FrattalatoreAudioProcessor::setParams()
{
    setVoiceParams();
    setFilterParams();
}

void FrattalatoreAudioProcessor::setVoiceParams()
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        //check the correct casting for each voice
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice(i)))
        {
            ////////////OSCILLATORS///////////////////////////////////////////
            
            // OSC1 
            auto& osc1WaveChoice = *apvts.getRawParameterValue("OSC1TYPE");
            auto& osc1Gain = *apvts.getRawParameterValue("OSC1GAIN");
            auto& osc1Pitch = *apvts.getRawParameterValue("OSC1PITCH");
            // OSC2
            auto& osc2WaveChoice = *apvts.getRawParameterValue("OSC2TYPE");
            auto& osc2Gain = *apvts.getRawParameterValue("OSC2GAIN");
            auto& osc2Pitch = *apvts.getRawParameterValue("OSC2PITCH");
            // OSC3
            auto& osc3WaveChoice = *apvts.getRawParameterValue("OSC3TYPE");
            auto& osc3Gain = *apvts.getRawParameterValue("OSC3GAIN");
            auto& osc3Pitch = *apvts.getRawParameterValue("OSC3PITCH");
            // OSC4
            auto& osc4WaveChoice = *apvts.getRawParameterValue("OSC4TYPE");
            auto& osc4Gain = *apvts.getRawParameterValue("OSC4GAIN");
            auto& osc4Pitch = *apvts.getRawParameterValue("OSC4PITCH");
            // OS5 
            auto& osc5WaveChoice = *apvts.getRawParameterValue("OSC5TYPE");
            auto& osc5Gain = *apvts.getRawParameterValue("OSC5GAIN");
            auto& osc5Pitch = *apvts.getRawParameterValue("OSC5PITCH");

            ////////////FM MODS///////////////////////////////////////////

            //FM
            auto& fm1Depth = *apvts.getRawParameterValue("OSC1FMDEPTH");
            auto& fm1Freq = *apvts.getRawParameterValue("OSC1FMFREQ");
            //FM
            auto& fm2Depth = *apvts.getRawParameterValue("OSC2FMDEPTH");
            auto& fm2Freq = *apvts.getRawParameterValue("OSC2FMFREQ");
            //FM
            auto& fm3Depth = *apvts.getRawParameterValue("OSC3FMDEPTH");
            auto& fm3Freq = *apvts.getRawParameterValue("OSC3FMFREQ");
            //FM
            auto& fm4Depth = *apvts.getRawParameterValue("OSC4FMDEPTH");
            auto& fm4Freq = *apvts.getRawParameterValue("OSC4FMFREQ");
            //FM
            auto& fm5Depth = *apvts.getRawParameterValue("OSC5FMDEPTH");
            auto& fm5Freq = *apvts.getRawParameterValue("OSC5FMFREQ");

            //ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            //Update oscs params
            
            for (int j = 0; j < getTotalNumOutputChannels(); j++)
            {
                voice->getOscillator1()[j].setParams(osc1WaveChoice, osc1Gain.load(), osc1Pitch, fm1Freq.load(), fm1Depth.load());
                voice->getOscillator2()[j].setParams(osc2WaveChoice, osc2Gain.load(), osc2Pitch, fm2Freq.load(), fm2Depth.load());
                voice->getOscillator3()[j].setParams(osc3WaveChoice, osc3Gain.load(), osc3Pitch, fm3Freq.load(), fm3Depth.load());
                voice->getOscillator4()[j].setParams(osc4WaveChoice, osc4Gain.load(), osc4Pitch, fm4Freq.load(), fm4Depth.load());
                voice->getOscillator5()[j].setParams(osc5WaveChoice, osc5Gain.load(), osc5Pitch, fm5Freq.load(), fm5Depth.load());
            }
            auto& adsr = voice->getAdsr();
            adsr.updateADSR(attack.load(), decay.load(), sustain.load(), release.load()); //the pointer is for a AtomicFloat -> convert it into float iot save 
        }
    }
}


void FrattalatoreAudioProcessor::setFilterParams()
{
    auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
    auto& filterCutOff = *apvts.getRawParameterValue("FILTERCUTOFF");
    auto& filterResonance = *apvts.getRawParameterValue("FILTERRESONANCE");

    auto& lfoFreq = *apvts.getRawParameterValue("LFOFREQ");
    auto& lfoDepth = *apvts.getRawParameterValue("LFODEPTH");

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->updateFilterParams(filterType, filterCutOff, filterResonance, lfoFreq, lfoDepth);
        }
    }
}
