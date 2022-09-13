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
    treeState.addParameterListener("input", this);
    
    treeState.addParameterListener("solo 1", this);
    treeState.addParameterListener("solo 2", this);
    treeState.addParameterListener("solo 3", this);
    treeState.addParameterListener("solo 4", this);
    
    treeState.addParameterListener("bypass 1", this);
    treeState.addParameterListener("bypass 2", this);
    treeState.addParameterListener("bypass 3", this);
    treeState.addParameterListener("bypass 4", this);
    
    treeState.addParameterListener("low", this);
    treeState.addParameterListener("mid", this);
    treeState.addParameterListener("high", this);
    
    treeState.addParameterListener("gain1", this);
    treeState.addParameterListener("thres 1", this);
    treeState.addParameterListener("ratio 1", this);
    treeState.addParameterListener("attack 1", this);
    treeState.addParameterListener("release 1", this);
    
    treeState.addParameterListener("gain2", this);
    treeState.addParameterListener("thres 2", this);
    treeState.addParameterListener("ratio 2", this);
    treeState.addParameterListener("attack 2", this);
    treeState.addParameterListener("release 2", this);
    
    treeState.addParameterListener("gain3", this);
    treeState.addParameterListener("thres 3", this);
    treeState.addParameterListener("ratio 3", this);
    treeState.addParameterListener("attack 3", this);
    treeState.addParameterListener("release 3", this);
    
    treeState.addParameterListener("gain4", this);
    treeState.addParameterListener("thres 4", this);
    treeState.addParameterListener("ratio 4", this);
    treeState.addParameterListener("attack 4", this);
    treeState.addParameterListener("release 4", this);
    
    treeState.addParameterListener("output", this);
}

CURBAudioProcessor::~CURBAudioProcessor()
{
    treeState.removeParameterListener("input", this);
    
    treeState.removeParameterListener("solo 1", this);
    treeState.removeParameterListener("solo 2", this);
    treeState.removeParameterListener("solo 3", this);
    treeState.removeParameterListener("solo 4", this);
    
    treeState.removeParameterListener("bypass 1", this);
    treeState.removeParameterListener("bypass 2", this);
    treeState.removeParameterListener("bypass 3", this);
    treeState.removeParameterListener("bypass 4", this);
    
    treeState.removeParameterListener("low", this);
    treeState.removeParameterListener("mid", this);
    treeState.removeParameterListener("high", this);
    
    treeState.removeParameterListener("gain1", this);
    treeState.removeParameterListener("thres 1", this);
    treeState.removeParameterListener("ratio 1", this);
    treeState.removeParameterListener("attack 1", this);
    treeState.removeParameterListener("release 1", this);
    
    treeState.removeParameterListener("gain2", this);
    treeState.removeParameterListener("thres 2", this);
    treeState.removeParameterListener("ratio 2", this);
    treeState.removeParameterListener("attack 2", this);
    treeState.removeParameterListener("release 2", this);
    
    treeState.removeParameterListener("gain3", this);
    treeState.removeParameterListener("thres 3", this);
    treeState.removeParameterListener("ratio 3", this);
    treeState.removeParameterListener("attack 3", this);
    treeState.removeParameterListener("release 3", this);
    
    treeState.removeParameterListener("gain4", this);
    treeState.removeParameterListener("thres 4", this);
    treeState.removeParameterListener("ratio 4", this);
    treeState.removeParameterListener("attack 4", this);
    treeState.removeParameterListener("release 4", this);
    
    treeState.removeParameterListener("output", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout CURBAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    auto gainRange = juce::NormalisableRange<float> (-24.0f, 24.0f, 0.5f, 1.0f);
    
    auto pInput = std::make_unique<juce::AudioParameterFloat>("input", "Input", gainRange, 0.0f);
    
    auto pSolo1 = std::make_unique<juce::AudioParameterBool>("solo 1", "Solo 1", 0);
    auto pSolo2 = std::make_unique<juce::AudioParameterBool>("solo 2", "Solo 2", 0);
    auto pSolo3 = std::make_unique<juce::AudioParameterBool>("solo 3", "Solo 3", 0);
    auto pSolo4 = std::make_unique<juce::AudioParameterBool>("solo 4", "Solo 4", 0);
    
    auto pBypass1 = std::make_unique<juce::AudioParameterBool>("bypass 1", "Bypass 1", 0);
    auto pBypass2 = std::make_unique<juce::AudioParameterBool>("bypass 2", "Bypass 2", 0);
    auto pBypass3 = std::make_unique<juce::AudioParameterBool>("bypass 3", "Bypass 3", 0);
    auto pBypass4 = std::make_unique<juce::AudioParameterBool>("bypass 4", "Bypass 4", 0);
    
    auto pGain1 = std::make_unique<juce::AudioParameterFloat>("gain1", "Gain1", gainRange, 0.0f);
    auto p1Thres = std::make_unique<juce::AudioParameterFloat>("thres 1", "Threshold 1", -70.0, 0.0, 0.0);
    auto p1Ratio = std::make_unique<juce::AudioParameterFloat>("ratio 1", "Ratio 1", 1.0, 10.0, 1.0);
    auto p1Att = std::make_unique<juce::AudioParameterFloat>("attack 1", "Attack 1", 0.0, 200.0, 10.0);
    auto p1Rel = std::make_unique<juce::AudioParameterFloat>("release 1", "Release 1", 0.0, 300.0, 100.0);
    
    auto pLowBand = std::make_unique<juce::AudioParameterFloat>("low", "Low", juce::NormalisableRange<float> (40.0, 250.0, 1.0, 1.0), 100);
    
    auto pGain2 = std::make_unique<juce::AudioParameterFloat>("gain2", "Gain2", gainRange, 0.0f);
    auto p2Thres = std::make_unique<juce::AudioParameterFloat>("thres 2", "Threshold 2", -70.0, 0.0, 0.0);
    auto p2Ratio = std::make_unique<juce::AudioParameterFloat>("ratio 2", "Ratio 2", 1.0, 10.0, 1.0);
    auto p2Att = std::make_unique<juce::AudioParameterFloat>("attack 2", "Attack 2", 0.0, 200.0, 10.0);
    auto p2Rel = std::make_unique<juce::AudioParameterFloat>("release 2", "Release 2", 0.0, 300.0, 100.0);
    
    auto pMidBand = std::make_unique<juce::AudioParameterFloat>("mid", "Mid", juce::NormalisableRange<float> (251.0, 6000.0, 1.0, 1.0), 1000.0);
    
    auto pGain3 = std::make_unique<juce::AudioParameterFloat>("gain3", "Gain3", gainRange, 0.0f);
    auto p3Thres = std::make_unique<juce::AudioParameterFloat>("thres 3", "Threshold 3", -70.0, 0.0, 0.0);
    auto p3Ratio = std::make_unique<juce::AudioParameterFloat>("ratio 3", "Ratio 3", 1.0, 10.0, 1.0);
    auto p3Att = std::make_unique<juce::AudioParameterFloat>("attack 3", "Attack 3", 0.0, 200.0, 10.0);
    auto p3Rel = std::make_unique<juce::AudioParameterFloat>("release 3", "Release 3", 0.0, 300.0, 100.0);
    
    auto pHighBand = std::make_unique<juce::AudioParameterFloat>("high", "High", juce::NormalisableRange<float> (6001.0, 16000.0, 1.0, 1.0), 12000.0);
    
    auto pGain4 = std::make_unique<juce::AudioParameterFloat>("gain4", "Gain4", gainRange, 0.0f);
    auto p4Thres = std::make_unique<juce::AudioParameterFloat>("thres 4", "Threshold 4", -70.0, 0.0, 0.0);
    auto p4Ratio = std::make_unique<juce::AudioParameterFloat>("ratio 4", "Ratio 4", 1.0, 10.0, 1.0);
    auto p4Att = std::make_unique<juce::AudioParameterFloat>("attack 4", "Attack 4", 0.0, 200.0, 10.0);
    auto p4Rel = std::make_unique<juce::AudioParameterFloat>("release 4", "Release 4", 0.0, 300.0, 100.0);
    
    auto pOutput = std::make_unique<juce::AudioParameterFloat>("output", "Output", gainRange, 0.0f);
    
    params.push_back(std::move(pInput));
    
    params.push_back(std::move(pSolo1));
    params.push_back(std::move(pBypass1));
    params.push_back(std::move(pGain1));
    params.push_back(std::move(p1Thres));
    params.push_back(std::move(p1Ratio));
    params.push_back(std::move(p1Att));
    params.push_back(std::move(p1Rel));
    
    params.push_back(std::move(pLowBand));
    
    params.push_back(std::move(pSolo2));
    params.push_back(std::move(pBypass2));
    params.push_back(std::move(pGain2));
    params.push_back(std::move(p2Thres));
    params.push_back(std::move(p2Ratio));
    params.push_back(std::move(p2Att));
    params.push_back(std::move(p2Rel));
    
    params.push_back(std::move(pMidBand));
    
    params.push_back(std::move(pSolo3));
    params.push_back(std::move(pBypass3));
    params.push_back(std::move(pGain3));
    params.push_back(std::move(p3Thres));
    params.push_back(std::move(p3Ratio));
    params.push_back(std::move(p3Att));
    params.push_back(std::move(p3Rel));
    
    params.push_back(std::move(pHighBand));
    
    params.push_back(std::move(pSolo4));
    params.push_back(std::move(pBypass4));
    params.push_back(std::move(pGain4));
    params.push_back(std::move(p4Thres));
    params.push_back(std::move(p4Ratio));
    params.push_back(std::move(p4Att));
    params.push_back(std::move(p4Rel));
    
    params.push_back(std::move(pOutput));

    return { params.begin(), params.end() };
}

void CURBAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if(parameterID == "input")
    {
        input.setGainDecibels(treeState.getRawParameterValue("input")->load());
    }
    if(parameterID == "low")
    {
        lowBand = newValue;
        LP0.setCutoffFrequency(lowBand);
        HP0.setCutoffFrequency(lowBand);
    }
    if(parameterID == "mid")
    {
        midBand = newValue;
        LP1.setCutoffFrequency(midBand);
        HP1.setCutoffFrequency(midBand);
        AP1b.setCutoffFrequency(midBand);
    }
    if(parameterID == "high")
    {
        highBand = newValue;
        AP2a.setCutoffFrequency(highBand);
        AP2b.setCutoffFrequency(highBand);
        LP2.setCutoffFrequency(highBand);
        HP2.setCutoffFrequency(highBand);
    }
    if (parameterID == "solo 1")
    {
        soloBand[0] = newValue;
    }
    if (parameterID == "solo 2")
    {
        soloBand[1] = newValue;
    }
    if (parameterID == "solo 3")
    {
        soloBand[2] = newValue;
    }
    if (parameterID == "solo 4")
    {
        soloBand[3] = newValue;
    }
    if (parameterID == "bypass 1")
    {
        bypass1 = newValue;
    }
    if (parameterID == "bypass 2")
    {
        bypass2 = newValue;
    }
    if (parameterID == "bypass 3")
    {
        bypass3 = newValue;
    }
    if (parameterID == "bypass 4")
    {
        bypass4 = newValue;
    }
    if(parameterID == "gain1")
    {
        gain1.setGainDecibels(treeState.getRawParameterValue("gain1")->load());
    }
    if(parameterID == "gain2")
    {
        gain2.setGainDecibels(treeState.getRawParameterValue("gain2")->load());
    }
    if(parameterID == "gain3")
    {
        gain3.setGainDecibels(treeState.getRawParameterValue("gain3")->load());
    }
    if(parameterID == "gain4")
    {
        gain4.setGainDecibels(treeState.getRawParameterValue("gain4")->load());
    }
    
    compressor1.setThreshold(treeState.getRawParameterValue("thres 1")->load());
    compressor1.setRatio(treeState.getRawParameterValue("ratio 1")->load());
    compressor1.setAttack(treeState.getRawParameterValue("attack 1")->load());
    compressor1.setRelease(treeState.getRawParameterValue("release 1")->load());
    
    compressor2.setThreshold(treeState.getRawParameterValue("thres 2")->load());
    compressor2.setRatio(treeState.getRawParameterValue("ratio 2")->load());
    compressor2.setAttack(treeState.getRawParameterValue("attack 2")->load());
    compressor2.setRelease(treeState.getRawParameterValue("release 2")->load());
    
    compressor3.setThreshold(treeState.getRawParameterValue("thres 3")->load());
    compressor3.setRatio(treeState.getRawParameterValue("ratio 3")->load());
    compressor3.setAttack(treeState.getRawParameterValue("attack 3")->load());
    compressor3.setRelease(treeState.getRawParameterValue("release 3")->load());
    
    compressor4.setThreshold(treeState.getRawParameterValue("thres 4")->load());
    compressor4.setRatio(treeState.getRawParameterValue("ratio 4")->load());
    compressor4.setAttack(treeState.getRawParameterValue("attack 4")->load());
    compressor4.setRelease(treeState.getRawParameterValue("release 4")->load());
    
    if(parameterID == "output")
    {
        output.setGainDecibels(treeState.getRawParameterValue("output")->load());
    }
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
    
    input.prepare(spec);
    input.setRampDurationSeconds(0.05);
    input.setGainDecibels(treeState.getRawParameterValue("input")->load());
    
    LP0.prepare(spec);
    LP0.setCutoffFrequency(treeState.getRawParameterValue("low")->load());
    LP0.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);

    HP0.prepare(spec);
    HP0.setCutoffFrequency(treeState.getRawParameterValue("low")->load());
    HP0.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    
    AP1a.prepare(spec);
    AP1a.setCutoffFrequency(treeState.getRawParameterValue("mid")->load());
    AP1a.setType(juce::dsp::LinkwitzRileyFilterType::allpass);
    
    LP1.prepare(spec);
    LP1.setCutoffFrequency(treeState.getRawParameterValue("mid")->load());
    LP1.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    
    HP1.prepare(spec);
    HP1.setCutoffFrequency(treeState.getRawParameterValue("mid")->load());
    HP1.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    
    AP1b.prepare(spec);
    AP1b.setCutoffFrequency(treeState.getRawParameterValue("mid")->load());
    AP1b.setType(juce::dsp::LinkwitzRileyFilterType::allpass);
    
    AP2a.prepare(spec);
    AP2a.setCutoffFrequency(treeState.getRawParameterValue("high")->load());
    AP2a.setType(juce::dsp::LinkwitzRileyFilterType::allpass);
    
    AP2b.prepare(spec);
    AP2b.setCutoffFrequency(treeState.getRawParameterValue("high")->load());
    AP2b.setType(juce::dsp::LinkwitzRileyFilterType::allpass);
    
    LP2.prepare(spec);
    LP2.setCutoffFrequency(treeState.getRawParameterValue("high")->load());
    LP2.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    
    HP2.prepare(spec);
    HP2.setCutoffFrequency(treeState.getRawParameterValue("high")->load());
    HP2.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    
    for ( auto& buffer : filterBuffers )
    {
        buffer.setSize(spec.numChannels, samplesPerBlock);
    }
    
    soloBand[0] = treeState.getRawParameterValue("solo 1")->load();
    soloBand[1] = treeState.getRawParameterValue("solo 2")->load();
    soloBand[2] = treeState.getRawParameterValue("solo 3")->load();
    soloBand[3] = treeState.getRawParameterValue("solo 4")->load();
    
    bypass1 = treeState.getRawParameterValue("bypass 1")->load();
    bypass2 = treeState.getRawParameterValue("bypass 2")->load();
    bypass3 = treeState.getRawParameterValue("bypass 3")->load();
    bypass4 = treeState.getRawParameterValue("bypass 4")->load();
    
    compressor1.prepare(spec);
    gain1.prepare(spec);
    gain1.setRampDurationSeconds(0.05);
    gain1.setGainDecibels(treeState.getRawParameterValue("gain1")->load());
    compressor1.setThreshold(treeState.getRawParameterValue("thres 1")->load());
    compressor1.setRatio(treeState.getRawParameterValue("ratio 1")->load());
    compressor1.setAttack(treeState.getRawParameterValue("attack 1")->load());
    compressor1.setRelease(treeState.getRawParameterValue("release 1")->load());
    
    compressor2.prepare(spec);
    gain2.prepare(spec);
    gain2.setRampDurationSeconds(0.05);
    gain2.setGainDecibels(treeState.getRawParameterValue("gain2")->load());
    compressor2.setThreshold(treeState.getRawParameterValue("thres 2")->load());
    compressor2.setRatio(treeState.getRawParameterValue("ratio 2")->load());
    compressor2.setAttack(treeState.getRawParameterValue("attack 2")->load());
    compressor2.setRelease(treeState.getRawParameterValue("release 2")->load());
    
    compressor3.prepare(spec);
    gain3.prepare(spec);
    gain3.setRampDurationSeconds(0.05);
    gain3.setGainDecibels(treeState.getRawParameterValue("gain3")->load());
    compressor3.setThreshold(treeState.getRawParameterValue("thres 3")->load());
    compressor3.setRatio(treeState.getRawParameterValue("ratio 3")->load());
    compressor3.setAttack(treeState.getRawParameterValue("attack 3")->load());
    compressor3.setRelease(treeState.getRawParameterValue("release 3")->load());
    
    compressor4.prepare(spec);
    gain4.prepare(spec);
    gain4.setRampDurationSeconds(0.05);
    gain4.setGainDecibels(treeState.getRawParameterValue("gain4")->load());
    compressor4.setThreshold(treeState.getRawParameterValue("thres 4")->load());
    compressor4.setRatio(treeState.getRawParameterValue("ratio 4")->load());
    compressor4.setAttack(treeState.getRawParameterValue("attack 4")->load());
    compressor4.setRelease(treeState.getRawParameterValue("release 4")->load());
    
    output.prepare(spec);
    output.setRampDurationSeconds(0.05);
    output.setGainDecibels(treeState.getRawParameterValue("output")->load());
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
    
    auto blockIn = juce::dsp::AudioBlock<float> (buffer);
    auto gainCtx = juce::dsp::ProcessContextReplacing<float>(blockIn);
    
    input.process(juce::dsp::ProcessContextReplacing<float>(gainCtx));
    
    for ( auto& fb : filterBuffers )
    {
        fb = buffer;
    }
    
    auto fb0Block = juce::dsp::AudioBlock<float> (filterBuffers[0]);
    auto fb1Block = juce::dsp::AudioBlock<float> (filterBuffers[1]);
    auto fb2Block = juce::dsp::AudioBlock<float> (filterBuffers[2]);
    auto fb3Block = juce::dsp::AudioBlock<float> (filterBuffers[3]);

    auto fb0Ctx = juce::dsp::ProcessContextReplacing<float>(fb0Block);
    auto fb1Ctx = juce::dsp::ProcessContextReplacing<float>(fb1Block);
    auto fb2Ctx = juce::dsp::ProcessContextReplacing<float>(fb2Block);
    auto fb3Ctx = juce::dsp::ProcessContextReplacing<float>(fb3Block);
    
    LP0.process(fb0Ctx);
    AP1a.process(fb0Ctx);
    AP2a.process(fb0Ctx);
    
    HP0.process(fb1Ctx);
    filterBuffers[2] = filterBuffers[1];
    filterBuffers[3] = filterBuffers[1];
    LP1.process(fb1Ctx);
    AP2b.process(fb1Ctx);
    
    HP1.process(fb2Ctx);
    LP2.process(fb2Ctx);
    
    AP1b.process(fb3Ctx);
    HP2.process(fb3Ctx);
    
    if(bypass1) { fb0Ctx.isBypassed = true; };
    compressor1.process(fb0Ctx);
    gain1.process(fb0Ctx);
    
    if(bypass2) { fb1Ctx.isBypassed = true; };
    compressor2.process(fb1Ctx);
    gain2.process(fb1Ctx);
    
    if(bypass3) { fb2Ctx.isBypassed = true; };
    compressor3.process(fb2Ctx);
    gain3.process(fb2Ctx);
    
    if(bypass4) { fb3Ctx.isBypassed = true; };
    compressor4.process(fb3Ctx);
    gain4.process(fb3Ctx);
    
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
        
    auto aBandIsSoloed = false;
    for(size_t i = 0; i < soloBand.size(); ++i)
    {
        if(soloBand[i])
        {
            aBandIsSoloed = true;
            break;
        }
    }
    
    if(aBandIsSoloed)
    {
        for(size_t i = 0; i < soloBand.size(); ++i)
        {
            if(soloBand[i])
            {
                addFilterBand(buffer, filterBuffers[i]);
            }
        }
    }
    else
    {
        for(size_t i = 0; i < soloBand.size(); ++i)
        {
            addFilterBand(buffer, filterBuffers[i]);
        }
    }
    
    output.process(juce::dsp::ProcessContextReplacing<float>(gainCtx));
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
