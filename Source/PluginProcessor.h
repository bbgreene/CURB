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
    //Individual mixers
    std::array<juce::dsp::DryWetMixer<float>, 5> mixModule;
    std::array<float, 5> mixValue;
    
    //Input, output and individual band gains
    std::array<juce::dsp::Gain<float>, 6> gain; // 5[4] is input, 6[5] is output
    std::array<float, 6> gainValue;
    
    //Filters and variables
    using Filter = juce::dsp::LinkwitzRileyFilter<float>;
    
    Filter  LP0,    AP1a,   AP2a,
            HP0,    LP1,    AP2b,
                    HP1,    LP2,
                    AP1b,   HP2;
    
    float lowBand { 0.0 };
    float midBand { 0.0 };
    float highBand { 0.0 };
    
    //Compressors
    std::array<juce::dsp::Compressor<float>, 4> compressor;
    
    //Solo and bypasses
    std::array<int, 4> soloBand;
    std::array<int, 4> bypass;
    
    //Band buffers
    std::array<juce::AudioBuffer<float>, 4> filterBuffers;
    
    //functions
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    void updateParameters();
    void splitBandsAndComp(const juce::AudioBuffer<float>& inputBuffer);
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
