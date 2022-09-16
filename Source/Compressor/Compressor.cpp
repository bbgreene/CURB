/*
  ==============================================================================

    Compressor.cpp
    Created: 14 Sep 2022 1:41:09pm
    Author:  Brian Greene

  ==============================================================================
*/

#include "Compressor.h"

namespace bbg_dsp
{

//==============================================================================
template <typename SampleType>
Compressor<SampleType>::Compressor()
{
    update();
}

//==============================================================================
template <typename SampleType>
void Compressor<SampleType>::setThreshold (SampleType newThreshold)
{
    thresholddB = newThreshold;
    update();
}

template <typename SampleType>
void Compressor<SampleType>::setRatio (SampleType newRatio)
{
//    jassert (newRatio >= static_cast<SampleType> (1.0));

    ratio = newRatio;
    update();
}

template <typename SampleType>
void Compressor<SampleType>::setAttack (SampleType newAttack)
{
    attackTime = newAttack;
    update();
}

template <typename SampleType>
void Compressor<SampleType>::setRelease (SampleType newRelease)
{
    releaseTime = newRelease;
    update();
}

//==============================================================================
template <typename SampleType>
void Compressor<SampleType>::prepare (const juce::dsp::ProcessSpec& spec)
{
    jassert (spec.sampleRate > 0);
    jassert (spec.numChannels > 0);

    sampleRate = spec.sampleRate;

    envelopeFilter.prepare (spec);

    update();
    reset();
}

template <typename SampleType>
void Compressor<SampleType>::reset()
{
    envelopeFilter.reset();
}

//==============================================================================
template <typename SampleType>
SampleType Compressor<SampleType>::processSampleDownCompression (int channel, SampleType inputValue)
{
    // Ballistics filter with peak rectifier
    auto env = envelopeFilter.processSample (channel, inputValue);
    auto gain = 1.0;
    // VCA
    if(ratio < 1.0)
    {
        gain = (env > threshold) ? static_cast<SampleType> (1.0)
                                      : std::pow (env * thresholdInverse, ratioInverseUpward - static_cast<SampleType> (1.0));
    }
    else
    {
        gain = (env < threshold) ? static_cast<SampleType> (1.0)
                                      : std::pow (env * thresholdInverse, ratioInverse - static_cast<SampleType> (1.0));
    }
   
    // Output
    return gain * inputValue;
}

template <typename SampleType>
void Compressor<SampleType>::update()
{
    threshold = juce::Decibels::decibelsToGain (thresholddB, static_cast<SampleType> (-200.0));
    thresholdInverse = static_cast<SampleType> (1.0) / threshold;
    ratioInverse     = static_cast<SampleType> (1.0) / ratio;
    ratioInverseUpward = static_cast<SampleType> (1.0) / (1.0 + ((1.5 - 1.0) * (ratio - 1.0)) / (0.5 - 1.0));
                                    //basically a jmap //(targetRangeMin + ((targetRangeMax - targetRangeMin) * (sourceValue - sourceRangeMin)) / (sourceRangeMax - sourceRangeMin));
 
    envelopeFilter.setAttackTime (attackTime);
    envelopeFilter.setReleaseTime (releaseTime);
}

//==============================================================================
template class Compressor<float>;
template class Compressor<double>;

} // namespace bbg_dsp
