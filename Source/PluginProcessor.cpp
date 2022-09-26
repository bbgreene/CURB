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
    
    treeState.addParameterListener("fb1mix", this);
    
    treeState.addParameterListener("gain1", this);
    treeState.addParameterListener("thres 1", this);
    treeState.addParameterListener("ratio 1", this);
    treeState.addParameterListener("attack 1", this);
    treeState.addParameterListener("release 1", this);
    
    treeState.addParameterListener("fb2mix", this);
    
    treeState.addParameterListener("gain2", this);
    treeState.addParameterListener("thres 2", this);
    treeState.addParameterListener("ratio 2", this);
    treeState.addParameterListener("attack 2", this);
    treeState.addParameterListener("release 2", this);
    
    treeState.addParameterListener("fb3mix", this);
    
    treeState.addParameterListener("gain3", this);
    treeState.addParameterListener("thres 3", this);
    treeState.addParameterListener("ratio 3", this);
    treeState.addParameterListener("attack 3", this);
    treeState.addParameterListener("release 3", this);
    
    treeState.addParameterListener("fb4mix", this);
    
    treeState.addParameterListener("gain4", this);
    treeState.addParameterListener("thres 4", this);
    treeState.addParameterListener("ratio 4", this);
    treeState.addParameterListener("attack 4", this);
    treeState.addParameterListener("release 4", this);
    
    treeState.addParameterListener("output", this);
    treeState.addParameterListener("main mix", this);
    treeState.addParameterListener("preset", this);
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
    
    treeState.removeParameterListener("fb1mix", this);
    
    treeState.removeParameterListener("gain1", this);
    treeState.removeParameterListener("thres 1", this);
    treeState.removeParameterListener("ratio 1", this);
    treeState.removeParameterListener("attack 1", this);
    treeState.removeParameterListener("release 1", this);
    
    treeState.removeParameterListener("fb2mix", this);
    
    treeState.removeParameterListener("gain2", this);
    treeState.removeParameterListener("thres 2", this);
    treeState.removeParameterListener("ratio 2", this);
    treeState.removeParameterListener("attack 2", this);
    treeState.removeParameterListener("release 2", this);
    
    treeState.removeParameterListener("fb3mix", this);
    
    treeState.removeParameterListener("gain3", this);
    treeState.removeParameterListener("thres 3", this);
    treeState.removeParameterListener("ratio 3", this);
    treeState.removeParameterListener("attack 3", this);
    treeState.removeParameterListener("release 3", this);
    
    treeState.removeParameterListener("fb4mix", this);
    
    treeState.removeParameterListener("gain4", this);
    treeState.removeParameterListener("thres 4", this);
    treeState.removeParameterListener("ratio 4", this);
    treeState.removeParameterListener("attack 4", this);
    treeState.removeParameterListener("release 4", this);
    
    treeState.removeParameterListener("output", this);
    treeState.removeParameterListener("main mix", this);
    treeState.removeParameterListener("preset", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout CURBAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

    auto gainRange = juce::NormalisableRange<float> (-24.0f, 24.0f, 0.1f, 1.0f);
    auto thresholdRange = juce::NormalisableRange<float> (-50.0f, 0.0f, 0.1f, 1.0f);
    auto ratioRange = juce::NormalisableRange<float> (0.5f, 10.0f, 0.01f, 0.5f);
    auto attackRange = juce::NormalisableRange<float> (1.0f, 150.0f, 1.0f, 1.0f);
    auto releaseRange = juce::NormalisableRange<float> (2.0f, 300.0f, 1.0f, 1.0f);
    auto mixRange = juce::NormalisableRange<float> (0.0, 100.0, 0.01, 1.0);
    
    auto pInput = std::make_unique<juce::AudioParameterFloat>("input", "Input", gainRange, 0.0f, juce::String(),
                                                              juce::AudioProcessorParameter::genericParameter,
                                                              [](float value, int) {return (value > -10.0f && value < 10.0f) ? juce::String (value, 2) + " dB" : juce::String (value, 1) + " dB";},
                                                              [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pSolo1 = std::make_unique<juce::AudioParameterBool>("solo 1", "Solo 1", 0);
    auto pSolo2 = std::make_unique<juce::AudioParameterBool>("solo 2", "Solo 2", 0);
    auto pSolo3 = std::make_unique<juce::AudioParameterBool>("solo 3", "Solo 3", 0);
    auto pSolo4 = std::make_unique<juce::AudioParameterBool>("solo 4", "Solo 4", 0);
    
    auto pBypass1 = std::make_unique<juce::AudioParameterBool>("bypass 1", "Bypass 1", 0);
    auto pBypass2 = std::make_unique<juce::AudioParameterBool>("bypass 2", "Bypass 2", 0);
    auto pBypass3 = std::make_unique<juce::AudioParameterBool>("bypass 3", "Bypass 3", 0);
    auto pBypass4 = std::make_unique<juce::AudioParameterBool>("bypass 4", "Bypass 4", 0);
    
    auto pFb1Mix = std::make_unique<juce::AudioParameterFloat>("fb1mix", "Fb1mix", mixRange,
                                                               100.0,
                                                               juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return (value < 100.0) ? juce::String (value, 1) + " %" : juce::String (value, 0) + " %";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pGain1 = std::make_unique<juce::AudioParameterFloat>("gain1", "Gain1", gainRange, 0.0f, juce::String(),
                                                              juce::AudioProcessorParameter::genericParameter,
                                                              [](float value, int) {return (value > -10.0f && value < 10.0f) ? juce::String (value, 2) + " dB" : juce::String (value, 1) + " dB";},
                                                              [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p1Thres = std::make_unique<juce::AudioParameterFloat>("thres 1", "Threshold 1", thresholdRange, 0.0f, juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return juce::String (value, 1) + " dB";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});;
    
    auto p1Ratio = std::make_unique<juce::AudioParameterFloat>("ratio 1", "Ratio 1", ratioRange, 1.0f, juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return (value == 1.0) ? juce::String (value, 0) + ":1" :  juce::String (value, 1) + ":1";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p1Att = std::make_unique<juce::AudioParameterFloat>("attack 1", "Attack 1",   attackRange, 20.0f, juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             [](float value, int) {return juce::String (value, 0) + " ms";},
                                                             [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p1Rel = std::make_unique<juce::AudioParameterFloat>("release 1", "Release 1", releaseRange, 40.0f, juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             [](float value, int) {return (value < 1000) ? juce::String (value, 0) + " ms" : juce::String (value / 1000, 2) + " s";},
                                                             [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pLowBand = std::make_unique<juce::AudioParameterFloat>("low", "Low", juce::NormalisableRange<float> (40.0, 250.0, 1.0, 1.0), 100, juce::String(),
                                                                juce::AudioProcessorParameter::genericParameter,
                                                                [](float value, int) {return juce::String (value, 0) + " Hz";},
                                                                [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});;
    
    auto pFb2Mix = std::make_unique<juce::AudioParameterFloat>("fb2mix", "Fb2mix", mixRange,
                                                               100.0,
                                                               juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return (value < 100.0) ? juce::String (value, 1) + " %" : juce::String (value, 0) + " %";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pGain2 = std::make_unique<juce::AudioParameterFloat>("gain2", "Gain2", gainRange, 0.0f, juce::String(),
                                                              juce::AudioProcessorParameter::genericParameter,
                                                              [](float value, int) {return (value > -10.0f && value < 10.0f) ? juce::String (value, 2) + " dB" : juce::String (value, 1) + " dB";},
                                                              [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p2Thres = std::make_unique<juce::AudioParameterFloat>("thres 2", "Threshold 2", thresholdRange, 0.0f,  juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return juce::String (value, 1) + " dB";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p2Ratio = std::make_unique<juce::AudioParameterFloat>("ratio 2", "Ratio 2", ratioRange, 1.0f, juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return (value == 1.0) ? juce::String (value, 0) + ":1" :  juce::String (value, 1) + ":1";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p2Att = std::make_unique<juce::AudioParameterFloat>("attack 2", "Attack 2", attackRange, 20.0f, juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             [](float value, int) {return juce::String (value, 0) + " ms";},
                                                             [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p2Rel = std::make_unique<juce::AudioParameterFloat>("release 2", "Release 2", releaseRange, 40.0f, juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             [](float value, int) {return (value < 1000) ? juce::String (value, 0) + " ms" : juce::String (value / 1000, 2) + " s";},
                                                             [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pMidBand = std::make_unique<juce::AudioParameterFloat>("mid", "Mid", juce::NormalisableRange<float> (251.0, 6000.0, 1.0, 1.0), 1000.0, juce::String(),
                                                                juce::AudioProcessorParameter::genericParameter,
                                                                [](float value, int) {return juce::String (value, 0) + " Hz";},
                                                                [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});;
    
    auto pFb3Mix = std::make_unique<juce::AudioParameterFloat>("fb3mix", "Fb3mix", mixRange,
                                                               100.0,
                                                               juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return (value < 100.0) ? juce::String (value, 1) + " %" : juce::String (value, 0) + " %";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pGain3 = std::make_unique<juce::AudioParameterFloat>("gain3", "Gain3", gainRange, 0.0f, juce::String(),
                                                              juce::AudioProcessorParameter::genericParameter,
                                                              [](float value, int) {return (value > -10.0f && value < 10.0f) ? juce::String (value, 2) + " dB" : juce::String (value, 1) + " dB";},
                                                              [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p3Thres = std::make_unique<juce::AudioParameterFloat>("thres 3", "Threshold 3", thresholdRange, 0.0f,  juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return juce::String (value, 1) + " dB";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p3Ratio = std::make_unique<juce::AudioParameterFloat>("ratio 3", "Ratio 3",ratioRange, 1.0f, juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return (value == 1.0) ? juce::String (value, 0) + ":1" :  juce::String (value, 1) + ":1";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p3Att = std::make_unique<juce::AudioParameterFloat>("attack 3", "Attack 3", attackRange, 20.0f, juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             [](float value, int) {return juce::String (value, 0) + " ms";},
                                                             [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p3Rel = std::make_unique<juce::AudioParameterFloat>("release 3", "Release 3", releaseRange, 40.0f, juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             [](float value, int) {return (value < 1000) ? juce::String (value, 0) + " ms" : juce::String (value / 1000, 2) + " s";},
                                                             [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pHighBand = std::make_unique<juce::AudioParameterFloat>("high", "High", juce::NormalisableRange<float> (6001.0, 16000.0, 1.0, 1.0), 12000.0, juce::String(),
                                                                 juce::AudioProcessorParameter::genericParameter,
                                                                 [](float value, int) {return juce::String (value, 0) + " Hz";},
                                                                 [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});;
    
    auto pFb4Mix = std::make_unique<juce::AudioParameterFloat>("fb4mix", "Fb4mix", mixRange,
                                                               100.0,
                                                               juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return (value < 100.0) ? juce::String (value, 1) + " %" : juce::String (value, 0) + " %";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pGain4 = std::make_unique<juce::AudioParameterFloat>("gain4", "Gain4", gainRange, 0.0f, juce::String(),
                                                              juce::AudioProcessorParameter::genericParameter,
                                                              [](float value, int) {return (value > -10.0f && value < 10.0f) ? juce::String (value, 2) + " dB" : juce::String (value, 1) + " dB";},
                                                              [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p4Thres = std::make_unique<juce::AudioParameterFloat>("thres 4", "Threshold 4", thresholdRange, 0.0f, juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return juce::String (value, 1) + " dB";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p4Ratio = std::make_unique<juce::AudioParameterFloat>("ratio 4", "Ratio 4", ratioRange, 1.0f, juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return (value == 1.0) ? juce::String (value, 0) + ":1" :  juce::String (value, 1) + ":1";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p4Att = std::make_unique<juce::AudioParameterFloat>("attack 4", "Attack 4", attackRange, 20.0f, juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             [](float value, int) {return juce::String (value, 0) + " ms";},
                                                             [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto p4Rel = std::make_unique<juce::AudioParameterFloat>("release 4", "Release 4", releaseRange, 40.0f, juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             [](float value, int) {return (value < 1000) ? juce::String (value, 0) + " ms" : juce::String (value / 1000, 2) + " s";},
                                                             [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pOutput = std::make_unique<juce::AudioParameterFloat>("output", "Output", gainRange, 0.0f, juce::String(),
                                                               juce::AudioProcessorParameter::genericParameter,
                                                               [](float value, int) {return (value > -10.0f && value < 10.0f) ? juce::String (value, 2) + " dB" : juce::String (value, 1) + " dB";},
                                                               [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pMainMix = std::make_unique<juce::AudioParameterFloat>("main mix", "Main Mix", mixRange,
                                                                100.0,
                                                                juce::String(),
                                                                juce::AudioProcessorParameter::genericParameter,
                                                                [](float value, int) {return (value < 100.0) ? juce::String (value, 1) + " %" : juce::String (value, 0) + " %";},
                                                                [](juce::String text) {return text.dropLastCharacters (3).getFloatValue();});
    
    auto pPreset = std::make_unique<juce::AudioParameterInt>("preset", "Preset", 0, 14, 0);
    
    params.push_back(std::move(pInput));
    
    params.push_back(std::move(pSolo1));
    params.push_back(std::move(pBypass1));
    params.push_back(std::move(pFb1Mix));
    params.push_back(std::move(pGain1));
    params.push_back(std::move(p1Thres));
    params.push_back(std::move(p1Ratio));
    params.push_back(std::move(p1Att));
    params.push_back(std::move(p1Rel));
    
    params.push_back(std::move(pLowBand));
    
    params.push_back(std::move(pSolo2));
    params.push_back(std::move(pBypass2));
    params.push_back(std::move(pFb2Mix));
    params.push_back(std::move(pGain2));
    params.push_back(std::move(p2Thres));
    params.push_back(std::move(p2Ratio));
    params.push_back(std::move(p2Att));
    params.push_back(std::move(p2Rel));
    
    params.push_back(std::move(pMidBand));
    
    params.push_back(std::move(pSolo3));
    params.push_back(std::move(pBypass3));
    params.push_back(std::move(pFb3Mix));
    params.push_back(std::move(pGain3));
    params.push_back(std::move(p3Thres));
    params.push_back(std::move(p3Ratio));
    params.push_back(std::move(p3Att));
    params.push_back(std::move(p3Rel));
    
    params.push_back(std::move(pHighBand));
    
    params.push_back(std::move(pSolo4));
    params.push_back(std::move(pBypass4));
    params.push_back(std::move(pFb4Mix));
    params.push_back(std::move(pGain4));
    params.push_back(std::move(p4Thres));
    params.push_back(std::move(p4Ratio));
    params.push_back(std::move(p4Att));
    params.push_back(std::move(p4Rel));
    
    params.push_back(std::move(pOutput));
    params.push_back(std::move(pMainMix));
    params.push_back(std::move(pPreset));

    return { params.begin(), params.end() };
}

void CURBAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    updateParameters();
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
    
    LP0.prepare(spec);
    LP0.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    HP0.prepare(spec);
    HP0.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    AP1a.prepare(spec);
    AP1a.setType(juce::dsp::LinkwitzRileyFilterType::allpass);
    LP1.prepare(spec);
    LP1.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    HP1.prepare(spec);
    HP1.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    AP1b.prepare(spec);
    AP1b.setType(juce::dsp::LinkwitzRileyFilterType::allpass);
    AP2a.prepare(spec);
    AP2a.setType(juce::dsp::LinkwitzRileyFilterType::allpass);
    AP2b.prepare(spec);
    AP2b.setType(juce::dsp::LinkwitzRileyFilterType::allpass);
    LP2.prepare(spec);
    LP2.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    HP2.prepare(spec);
    HP2.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    
    for ( auto& buffer : filterBuffers )
    {
        buffer.setSize(spec.numChannels, samplesPerBlock);
    }
    
    for(size_t i = 0; i < gainValue.size(); ++i)
    {
        gainValue[i].reset(sampleRate, 0.0001f);
    }
    
    for(size_t i = 0; i < gain.size(); ++i)
    {
        gain[i].prepare(spec);
    }
    
    for(size_t i = 0; i < compressor.size(); ++i)
    {
        compressor[i].prepare(spec);
        compressor[i].reset();
    }
    
    for ( auto& mix : mixModule )
    {
        mix.prepare(spec);
        mix.setMixingRule(juce::dsp::DryWetMixingRule::sin6dB);
        mix.reset();
    }
    
//    rmsLevelInputLeft.reset(sampleRate, 0.5);
//    rmsLevelInputRight.reset(sampleRate, 0.5);
//
//    rmsLevelInputLeft.setCurrentAndTargetValue(-100.f);
//    rmsLevelInputRight.setCurrentAndTargetValue(-100.f);
//
//    rmsLevelOutputLeft.reset(sampleRate, 0.5);
//    rmsLevelOutputRight.reset(sampleRate, 0.5);
//
//    rmsLevelOutputLeft.setCurrentAndTargetValue(-100.f);
//    rmsLevelOutputRight.setCurrentAndTargetValue(-100.f);
    
    for ( auto& rms : rmsLevel )
    {
        rms.reset(sampleRate, 0.5);
        rms.setCurrentAndTargetValue(-100.f);
    }
    
    updateParameters();
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

void CURBAudioProcessor::splitBandsAndComp(const juce::AudioBuffer<float> &inputBuffer)
{
    for ( auto& fb : filterBuffers )
    {
        fb = inputBuffer;
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
    
    // rms values pre processing
    float band1InLeft = juce::Decibels::gainToDecibels(filterBuffers[0].getRMSLevel(0, 0, filterBuffers[0].getNumSamples()));
    float band1InRight = juce::Decibels::gainToDecibels(filterBuffers[0].getRMSLevel(1, 0, filterBuffers[0].getNumSamples()));
    
    float band2InLeft = juce::Decibels::gainToDecibels(filterBuffers[1].getRMSLevel(0, 0, filterBuffers[1].getNumSamples()));
    float band2InRight = juce::Decibels::gainToDecibels(filterBuffers[1].getRMSLevel(1, 0, filterBuffers[1].getNumSamples()));
    
    float band3InLeft = juce::Decibels::gainToDecibels(filterBuffers[2].getRMSLevel(0, 0, filterBuffers[2].getNumSamples()));
    float band3InRight = juce::Decibels::gainToDecibels(filterBuffers[2].getRMSLevel(1, 0, filterBuffers[2].getNumSamples()));
    
    float band4InLeft = juce::Decibels::gainToDecibels(filterBuffers[3].getRMSLevel(0, 0, filterBuffers[3].getNumSamples()));
    float band4InRight = juce::Decibels::gainToDecibels(filterBuffers[3].getRMSLevel(1, 0, filterBuffers[3].getNumSamples()));
    
    const auto& fb0Dry = fb0Ctx.getInputBlock();
    const auto& fb0Wet = fb0Ctx.getOutputBlock();
    mixModule[0].pushDrySamples(fb0Dry);
    if(bypass[0]) { fb0Ctx.isBypassed = true; };
    compressor[0].process(fb0Ctx);
    rmsLevelSmoothingAverage(band1InLeft, band1InRight, filterBuffers[0], 2, 0); // band 1 meter averaged to mono
    gain[0].process(fb0Ctx);
    mixModule[0].mixWetSamples(fb0Wet);
    
    const auto& fb1Dry = fb1Ctx.getInputBlock();
    const auto& fb1Wet = fb1Ctx.getOutputBlock();
    mixModule[1].pushDrySamples(fb1Dry);
    if(bypass[1]) { fb1Ctx.isBypassed = true; };
    compressor[1].process(fb1Ctx);
    rmsLevelSmoothingAverage(band2InLeft, band2InRight, filterBuffers[1], 3, 0); // band 2 meter averaged to mono
    gain[1].process(fb1Ctx);
    mixModule[1].mixWetSamples(fb1Wet);
    
    const auto& fb2Dry = fb2Ctx.getInputBlock();
    const auto& fb2Wet = fb2Ctx.getOutputBlock();
    mixModule[2].pushDrySamples(fb2Dry);
    if(bypass[2]) { fb2Ctx.isBypassed = true; };
    compressor[2].process(fb2Ctx);
    rmsLevelSmoothingAverage(band3InLeft, band3InRight, filterBuffers[2], 4, 0); // band 3 meter averaged to mono
    gain[2].process(fb2Ctx);
    mixModule[2].mixWetSamples(fb2Wet);
    
    const auto& fb3Dry = fb3Ctx.getInputBlock();
    const auto& fb3Wet = fb3Ctx.getOutputBlock();
    mixModule[3].pushDrySamples(fb3Dry);
    if(bypass[3]) { fb3Ctx.isBypassed = true; };
    compressor[3].process(fb3Ctx);
    rmsLevelSmoothingAverage(band4InLeft, band4InRight, filterBuffers[3], 5, 0); // band 4 meter averaged to mono
    gain[3].process(fb3Ctx);
    mixModule[3].mixWetSamples(fb3Wet);
}

void CURBAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    updateParameters();
    
    auto blockIn = juce::dsp::AudioBlock<float> (buffer);
    auto inCtx = juce::dsp::ProcessContextReplacing<float>(blockIn);
    const auto& inputBlock = inCtx.getInputBlock();
    const auto& outputBlock = inCtx.getOutputBlock();
    
    mixModule[4].pushDrySamples(inputBlock); //dry to main mix module
    
    gain[4].process(juce::dsp::ProcessContextReplacing<float>(inCtx)); // input gain
    
    // input meter stereo pair (0 and 1)
    rmsLevelSmoothing(buffer, 0, 0); // meter 0, left channel
    rmsLevelSmoothing(buffer, 1, 1); // meter 1, right channel

    splitBandsAndComp(buffer);
    
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
    
    gain[5].process(juce::dsp::ProcessContextReplacing<float>(inCtx)); //output gain
    
    mixModule[4].mixWetSamples(outputBlock); //wet to main mix module
    
    // output meter stereo pair (6 and 7)
    rmsLevelSmoothing(buffer, 6, 0); // meter 6, left channel
    rmsLevelSmoothing(buffer, 7, 1); // meter 7, right channel
}

void CURBAudioProcessor::updateParameters()
{
    LP0.setCutoffFrequency(treeState.getRawParameterValue("low")->load());
    HP0.setCutoffFrequency(treeState.getRawParameterValue("low")->load());
    
    AP1a.setCutoffFrequency(treeState.getRawParameterValue("mid")->load());
    LP1.setCutoffFrequency(treeState.getRawParameterValue("mid")->load());
    HP1.setCutoffFrequency(treeState.getRawParameterValue("mid")->load());
    AP1b.setCutoffFrequency(treeState.getRawParameterValue("mid")->load());

    AP2a.setCutoffFrequency(treeState.getRawParameterValue("high")->load());
    AP2b.setCutoffFrequency(treeState.getRawParameterValue("high")->load());
    LP2.setCutoffFrequency(treeState.getRawParameterValue("high")->load());
    HP2.setCutoffFrequency(treeState.getRawParameterValue("high")->load());
    
    soloBand[0] = treeState.getRawParameterValue("solo 1")->load();
    soloBand[1] = treeState.getRawParameterValue("solo 2")->load();
    soloBand[2] = treeState.getRawParameterValue("solo 3")->load();
    soloBand[3] = treeState.getRawParameterValue("solo 4")->load();
    
    bypass[0] = treeState.getRawParameterValue("bypass 1")->load();
    bypass[1] = treeState.getRawParameterValue("bypass 2")->load();
    bypass[2] = treeState.getRawParameterValue("bypass 3")->load();
    bypass[3] = treeState.getRawParameterValue("bypass 4")->load();

    gainValue[0].setTargetValue(treeState.getRawParameterValue("gain1")->load());
    gainValue[1].setTargetValue(treeState.getRawParameterValue("gain2")->load());
    gainValue[2].setTargetValue(treeState.getRawParameterValue("gain3")->load());
    gainValue[3].setTargetValue(treeState.getRawParameterValue("gain4")->load());
    gainValue[4].setTargetValue(treeState.getRawParameterValue("input")->load());
    gainValue[5].setTargetValue(treeState.getRawParameterValue("output")->load());
    
    DBG(gainValue[5].getNextValue());
    
    for(size_t i = 0; i < gain.size(); ++i)
    {
        gain[i].setGainDecibels(gainValue[i].getNextValue());
    }
    
    compressor[0].setThreshold(treeState.getRawParameterValue("thres 1")->load());
    compressor[0].setRatio(treeState.getRawParameterValue("ratio 1")->load());
    compressor[0].setAttack(treeState.getRawParameterValue("attack 1")->load());
    compressor[0].setRelease(treeState.getRawParameterValue("release 1")->load());
    
    compressor[1].setThreshold(treeState.getRawParameterValue("thres 2")->load());
    compressor[1].setRatio(treeState.getRawParameterValue("ratio 2")->load());
    compressor[1].setAttack(treeState.getRawParameterValue("attack 2")->load());
    compressor[1].setRelease(treeState.getRawParameterValue("release 2")->load());

    compressor[2].setThreshold(treeState.getRawParameterValue("thres 3")->load());
    compressor[2].setRatio(treeState.getRawParameterValue("ratio 3")->load());
    compressor[2].setAttack(treeState.getRawParameterValue("attack 3")->load());
    compressor[2].setRelease(treeState.getRawParameterValue("release 3")->load());
    
    compressor[3].setThreshold(treeState.getRawParameterValue("thres 4")->load());
    compressor[3].setRatio(treeState.getRawParameterValue("ratio 4")->load());
    compressor[3].setAttack(treeState.getRawParameterValue("attack 4")->load());
    compressor[3].setRelease(treeState.getRawParameterValue("release 4")->load());
    
    mixValue[0] = treeState.getRawParameterValue("fb1mix")->load();
    mixValue[1] = treeState.getRawParameterValue("fb2mix")->load();
    mixValue[2] = treeState.getRawParameterValue("fb3mix")->load();
    mixValue[3] = treeState.getRawParameterValue("fb4mix")->load();
    mixValue[4] = treeState.getRawParameterValue("main mix")->load();
    
    for(size_t i = 0; i < mixModule.size(); ++i)
    {
        mixModule[i].setWetMixProportion(juce::jmap(mixValue[i], 0.0f, 100.0f, 0.0f, 1.0f));
    }
}

void CURBAudioProcessor::rmsLevelSmoothing(const juce::AudioBuffer<float> &inputBuffer, const int meter, const int channel)
{
    rmsLevel[meter].skip(inputBuffer.getNumSamples());
    {
        const auto value = juce::Decibels::gainToDecibels(inputBuffer.getRMSLevel(channel, 0, inputBuffer.getNumSamples()));
        if(value < rmsLevel[meter].getCurrentValue())
            rmsLevel[meter].setTargetValue(value);
        else
            rmsLevel[meter].setCurrentAndTargetValue(value);
    }
}

void CURBAudioProcessor::rmsLevelSmoothingAverage(float inputRMSLeft, float inputRMSRight, const juce::AudioBuffer<float> &outputBuffer, const int meter, const int channel)
{
    rmsLevel[meter].skip(outputBuffer.getNumSamples());
    {
        const auto valueInLeft = inputRMSLeft;
        const auto valueInRight = inputRMSRight;
        const auto averageValueIn = (valueInLeft + valueInRight) / 2.0;
        
        const auto valueOutLeft = juce::Decibels::gainToDecibels(outputBuffer.getRMSLevel(channel, 0, outputBuffer.getNumSamples()));
        const auto valueOutRight = juce::Decibels::gainToDecibels(outputBuffer.getRMSLevel(channel + 1, 0, outputBuffer.getNumSamples()));
        const auto averageValueOut = (valueOutLeft + valueOutRight) / 2.0;
        
        const auto gainReductionAverage = averageValueIn - averageValueOut;
                
        if(gainReductionAverage < rmsLevel[meter].getCurrentValue())
            rmsLevel[meter].setTargetValue(gainReductionAverage);
        else
            rmsLevel[meter].setCurrentAndTargetValue(gainReductionAverage);
    }
}

float CURBAudioProcessor::getRmsValue(const int meter) const
{
    return rmsLevel[meter].getCurrentValue();
}

//==============================================================================
bool CURBAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CURBAudioProcessor::createEditor()
{
    return new CURBAudioProcessorEditor (*this);
//    return new juce::GenericAudioProcessorEditor (*this);
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
