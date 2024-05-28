/*
  ==============================================================================

    OscData.cpp
    Created: 3 May 2022 12:17:35pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    prepare(spec);
    fmOsc.prepare(spec);
    gain.prepare(spec);

}

void OscData::setOscWaveType(const int choice)
{
    switch (choice)
    {
    case 0: //sine wave
        initialise([](float x) { return std::sin(x); },100);
        break;
    case 1: //saw wave
        initialise([](float x) { return x / (juce::MathConstants<float>::pi); },100);
        break;
    case 2: //square wave
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; },100);
        break;
    default: //error
        jassertfalse;
        break;
    }
}

void OscData::setGain(const float levelDb)
{
    gain.setGainDecibels(levelDb);
}


void OscData::setPitch(const int pitch)
{
    lastPitch = pitch;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz((lastMidiNote + lastPitch) + fmMod));
}


void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + lastPitch) + fmMod);
    lastMidiNote = midiNoteNumber;
}


void OscData::updateFm(const float depth, const float freq)
{
    fmDepth = depth;
    fmOsc.setFrequency(freq);
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz((lastMidiNote + lastPitch) + fmMod);
    setFrequency(currentFreq >= 0 ? currentFreq : currentFreq * -1.0f);
}

void OscData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    jassert(audioBlock.getNumSamples() > 0);
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

float OscData::processNextSample(float input)
{
    fmMod = fmOsc.processSample(input) * std::abs(fmDepth);
    return gain.processSample(this->processSample(input));
}

void OscData::setParams(const int oscChoice, const float oscGain, const int oscPitch, const float fmFreq, const float fmDepth)
{
    setOscWaveType(oscChoice);
    setGain(oscGain);
    setPitch(oscPitch);
    updateFm(fmDepth, fmFreq);
}

void OscData::resetOsc()
{
    reset();
    fmOsc.reset();
    gain.reset();

}



