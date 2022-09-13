/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class CURBAudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    CURBAudioProcessor();
    ~CURBAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState treeState;
    
private:
    
    juce::dsp::Compressor<float> compressor1;
    juce::dsp::Compressor<float> compressor2;
    juce::dsp::Compressor<float> compressor3;
    juce::dsp::Compressor<float> compressor4;
    
    using Filter = juce::dsp::LinkwitzRileyFilter<float>;
    
    Filter  LP0,    AP1a,   AP2a,
            HP0,    LP1,    AP2b,
                    HP1,    LP2,
                    AP1b,   HP2;
    
    float lowBand { 0.0 };
    float midBand { 0.0 };
    float highBand { 0.0 };
    
    std::array<int, 4> soloBand;
    
    bool bypass1 { false };
    bool bypass2 { false };
    bool bypass3 { false };
    bool bypass4 { false };
    
    std::array<juce::AudioBuffer<float>, 4> filterBuffers;
    
    //parameter layout and change functions
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CURBAudioProcessor)
};
/*Filter layout/flow
 
              low x     mid x            high x
 buffer0       LP0------>AP1a------------>AP2a--->Comp1---+
         
 buffer1       HP0------>LP1------------->AP2b--->Comp2---+
                      |
 buffer2              |->HP1------------->LP2---->Comp3---+
                      |
 buffer3              |->AP1b------------>HP2---->Comp4---+
 */
