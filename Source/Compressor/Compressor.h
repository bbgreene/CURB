/*
  ==============================================================================

    Compressor.h
    Created: 14 Sep 2022 1:41:09pm
    Author:  Brian Greene

  ==============================================================================
*/
#include <JuceHeader.h>

namespace bbg_dsp
{

/**
    A simple compressor with standard threshold, ratio, attack time and release time
    controls.

    @tags{DSP}
*/
template <typename SampleType>
class Compressor
{
public:
    //==============================================================================
    /** Constructor. */
    Compressor();

    //==============================================================================
    /** Sets the threshold in dB of the compressor.*/
    void setThreshold (SampleType newThreshold);

    /** Sets the ratio of the compressor (must be higher or equal to 1).*/
    void setRatio (SampleType newRatio);

    /** Sets the attack time in milliseconds of the compressor.*/
    void setAttack (SampleType newAttack);

    /** Sets the release time in milliseconds of the compressor.*/
    void setRelease (SampleType newRelease);
    
    void setCompType (SampleType newCompType);

    //==============================================================================
    /** Initialises the processor. */
    void prepare (const juce::dsp::ProcessSpec& spec);

    /** Resets the internal state variables of the processor. */
    void reset();

    //==============================================================================
    /** Processes the input and output samples supplied in the processing context. */
    template <typename ProcessContext>
    void process (const ProcessContext& context, bool compType) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock      = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples  = outputBlock.getNumSamples();

        jassert (inputBlock.getNumChannels() == numChannels);
        jassert (inputBlock.getNumSamples()  == numSamples);

        if (context.isBypassed)
        {
            outputBlock.copyFrom (inputBlock);
            return;
        }

        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            auto* inputSamples  = inputBlock .getChannelPointer (channel);
            auto* outputSamples = outputBlock.getChannelPointer (channel);

            for (size_t i = 0; i < numSamples; ++i)
            if(!compType)
                outputSamples[i] = processSampleDownCompression ((int) channel, inputSamples[i]);
            else
                outputSamples[i] = processSampleUpCompression ((int) channel, inputSamples[i]);
        }
    }

    /** Performs the processing operation on a single sample at a time. */
    SampleType processSampleDownCompression (int channel, SampleType inputValue);
    SampleType processSampleUpCompression (int channel, SampleType inputValue);

private:
    //==============================================================================
    void update();

    //==============================================================================
    SampleType threshold, thresholdInverse, ratioInverse, ratioInverseUpward;
    juce::dsp::BallisticsFilter<SampleType> envelopeFilter;

    double sampleRate = 44100.0;
    SampleType thresholddB = 0.0, ratio = 1.0, attackTime = 1.0, releaseTime = 100.0;
    SampleType compType = 0;
};


} // namespace bbg_dsp

