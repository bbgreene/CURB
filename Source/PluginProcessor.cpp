/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CURBAudioProcessor::CURBAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    treeState.addParameterListener("low mid freq", this);
    treeState.addParameterListener("mid high freq", this);
    treeState.addParameterListener("type", this);
    treeState.addParameterListener("threshold", this);
    treeState.addParameterListener("ratio", this);
    treeState.addParameterListener("attack", this);
    treeState.addParameterListener("release", this);
}

CURBAudioProcessor::~CURBAudioProcessor()
{
    treeState.removeParameterListener("low mid freq", this);
    treeState.removeParameterListener("type", this);
    treeState.removeParameterListener("threshold", this);
    treeState.removeParameterListener("ratio", this);
    treeState.removeParameterListener("attack", this);
    treeState.removeParameterListener("release", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout CURBAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    juce::StringArray typeSelector = {"low", "band", "high"};

    auto plowMidFreq = std::make_unique<juce::AudioParameterFloat>("low mid freq", "Low Mid Freq", juce::NormalisableRange<float> (20.0, 999.0, 1.0, 1.0), 400);
    auto pmidHighFreq = std::make_unique<juce::AudioParameterFloat>("mid high freq", "Mid High Freq", juce::NormalisableRange<float> (1000.0, 20000.0, 1.0, 1.0), 2000.0);

    auto pFilterTypeSelection = std::make_unique<juce::AudioParameterChoice>("type", "Type", typeSelector, 0);

    auto pThres = std::make_unique<juce::AudioParameterFloat>("threshold", "Threshold", -70.0, 0.0, 0.0);
    auto pRatio = std::make_unique<juce::AudioParameterFloat>("ratio", "Ratio", 1.0, 10.0, 1.0);
    auto pAtt = std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 0.0, 200.0, 10.0);
    auto pRel = std::make_unique<juce::AudioParameterFloat>("release", "Release", 0.0, 300.0, 100.0);

    params.push_back(std::move(plowMidFreq));
    params.push_back(std::move(pmidHighFreq));
    params.push_back(std::move(pFilterTypeSelection));
    params.push_back(std::move(pThres));
    params.push_back(std::move(pRatio));
    params.push_back(std::move(pAtt));
    params.push_back(std::move(pRel));

    return { params.begin(), params.end() };
}

void CURBAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == "low mid freq")
    {
        lowMidFreq = newValue;
        LP1.setCutoffFrequency(lowMidFreq);
        HP1.setCutoffFrequency(lowMidFreq);
    }
    if (parameterID == "mid high freq")
    {
        midHighFreq = newValue;
        AP2.setCutoffFrequency(midHighFreq);
        LP2.setCutoffFrequency(midHighFreq);
        HP2.setCutoffFrequency(midHighFreq);
    }
    if (parameterID == "type")
    {
        filterTypeSelection = newValue;
    }
    compressor.setThreshold(treeState.getRawParameterValue("threshold")->load());
    compressor.setRatio(treeState.getRawParameterValue("ratio")->load());
    compressor.setAttack(treeState.getRawParameterValue("attack")->load());
    compressor.setRelease(treeState.getRawParameterValue("release")->load());
    
}

//==============================================================================
const juce::String CURBAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CURBAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CURBAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CURBAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CURBAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CURBAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CURBAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CURBAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CURBAudioProcessor::getProgramName (int index)
{
    return {};
}

void CURBAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CURBAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    LP1.prepare(spec);
    LP1.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    LP1.setCutoffFrequency(treeState.getRawParameterValue("low mid freq")->load());

    HP1.prepare(spec);
    HP1.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    HP1.setCutoffFrequency(treeState.getRawParameterValue("low mid freq")->load());

    AP2.prepare(spec);
    AP2.setType(juce::dsp::LinkwitzRileyFilterType::allpass);
    AP2.setCutoffFrequency(treeState.getRawParameterValue("mid high freq")->load());

    LP2.prepare(spec);
    LP2.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    LP2.setCutoffFrequency(treeState.getRawParameterValue("mid high freq")->load());

    HP2.prepare(spec);
    HP2.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    HP2.setCutoffFrequency(treeState.getRawParameterValue("mid high freq")->load());

    for ( auto& buffer : filterBuffers )
    {
        buffer.setSize(spec.numChannels, samplesPerBlock);
    }
    
    compressor.prepare(spec);
    compressor.setThreshold(treeState.getRawParameterValue("threshold")->load());
    compressor.setRatio(treeState.getRawParameterValue("ratio")->load());
    compressor.setAttack(treeState.getRawParameterValue("attack")->load());
    compressor.setRelease(treeState.getRawParameterValue("release")->load());
}

void CURBAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CURBAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void CURBAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for ( auto& fb : filterBuffers )
    {
        fb = buffer;
    }
    
    auto fb0Block = juce::dsp::AudioBlock<float> (filterBuffers[0]);
    auto fb1Block = juce::dsp::AudioBlock<float> (filterBuffers[1]);
    auto fb2Block = juce::dsp::AudioBlock<float> (filterBuffers[2]);
    
    auto fb0Ctx = juce::dsp::ProcessContextReplacing<float>(fb0Block);
    auto fb1Ctx = juce::dsp::ProcessContextReplacing<float>(fb1Block);
    auto fb2Ctx = juce::dsp::ProcessContextReplacing<float>(fb2Block);
    
    LP1.process(fb0Ctx);
    AP2.process(fb0Ctx);
    
    HP1.process(fb1Ctx);
    filterBuffers[2] = filterBuffers[1]; //copying filter buffer 1 (processed by HP1) to filter buffer 2 in order to use 2nd hp.
    LP2.process(fb1Ctx);

    HP2.process(fb2Ctx);

    switch (filterTypeSelection)
    {
        case 0:
            compressor.process(fb0Ctx);
            break;
        case 1:
            compressor.process(fb1Ctx);
            break;
        case 2:
            compressor.process(fb2Ctx);
            break;
        default:
            compressor.process(fb0Ctx);
            break;
    }
    
    auto numSamples = buffer.getNumSamples();
    auto numChannels = buffer.getNumChannels();
    
    buffer.clear();
    
    auto addFilterBand = [nc = numChannels, ns = numSamples](auto& inputBuffer, const auto& source)
    {
        for ( auto i = 0; i < nc; ++i )
        {
            inputBuffer.addFrom(i, 0, source, i, 0, ns);
        }
    };
    
    addFilterBand(buffer, filterBuffers[0]);
    addFilterBand(buffer, filterBuffers[1]);
    addFilterBand(buffer, filterBuffers[2]);
}

//==============================================================================
bool CURBAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CURBAudioProcessor::createEditor()
{
//    return new CURBAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void CURBAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Save params
    juce::MemoryOutputStream stream(destData, false);
    treeState.state.writeToStream(stream);
}

void CURBAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Recall params
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
           
    if(tree.isValid())
    {
        treeState.replaceState(tree);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CURBAudioProcessor();
}
