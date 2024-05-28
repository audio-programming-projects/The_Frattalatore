/*
  ==============================================================================

    AdsrData.cpp
    Created: 2 May 2022 9:44:11am
    Author:  claud

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay,
    const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
}
