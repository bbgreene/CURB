/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "../Source/bbg_gui/Dial.h"
#include "../Source/bbg_gui/SliderHorizontal.h"
#include "../Source/bbg_gui/Toggle.h"
#include "../Source/bbg_gui/PushButton.h"
#include "../Source/bbg_gui/Menu.h"
#include "../Source/bbg_gui/Label.h"
#include <../Source/bbg_gui/VerticalGradientMeter.h>
#include <../Source/bbg_gui/VerticalDiscreteMeter.h>

//==============================================================================
/**
*/
class CURBAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CURBAudioProcessorEditor (CURBAudioProcessor&);
    ~CURBAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void mouseEnter (const juce::MouseEvent& event) override;
    void mouseExit (const juce::MouseEvent& event) override;

private:
    // DIALS, BUTTONS AND MENUS
    bbg_gui::bbg_Dial input;// { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_PushButton band1SoloButton { "S" };
    bbg_gui::bbg_PushButton band1BypassButton { "BYP" };
    bbg_gui::bbg_Dial threshold1;// { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio1;// { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack1;// { "", 1.0, 150.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial release1;// { "", 2.0, 300.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain1;// { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix1;// { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_SliderHorizontal lowBandSlider;// { "", 40.0, 250.0, 1.0, 0.0, 0.0 };
    
    bbg_gui::bbg_PushButton band2SoloButton { "S" };
    bbg_gui::bbg_PushButton band2BypassButton { "BYP" };
    bbg_gui::bbg_Dial threshold2;// { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio2;// { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack2;// { "", 1.0, 150.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial release2;// { "", 2.0, 300.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain2;// { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix2;// { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_SliderHorizontal midBandSlider;// { "", 251.0, 6000.0, 1.0, 0.0, 0.0 };
    
    bbg_gui::bbg_PushButton band3SoloButton { "S" };
    bbg_gui::bbg_PushButton band3BypassButton { "BYP" };
    bbg_gui::bbg_Dial threshold3;// { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio3;// { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack3;// { "", 1.0, 150.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial release3;// { "", 2.0, 300.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain3;// { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix3;//{ "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_SliderHorizontal highBandSlider;// { "", 6001.0, 16000.0, 1.0, 0.0, 0.0 };
    
    bbg_gui::bbg_PushButton band4SoloButton { "S" };
    bbg_gui::bbg_PushButton band4BypassButton { "BYP" };
    bbg_gui::bbg_Dial threshold4;// { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio4;// { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack4;// { "", 1.0, 150.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial release4;// { "", 2.0, 300.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain4;// { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix4;// { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_Dial output;// { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_SliderHorizontal  mainMix;// { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Menu preset;
    juce::TextButton presetPrevButton;
    juce::TextButton presetNextButton;
 
    // ATTACHMENTS
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputAttachement;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> band1SoloAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> band1BypassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thres1Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratio1Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attack1Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> release1Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gain1Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mix1Attachement;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowAttachement;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> band2SoloAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> band2BypassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thres2Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratio2Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attack2Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> release2Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gain2Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mix2Attachement;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> midAttachement;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> band3SoloAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> band3BypassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thres3Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratio3Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attack3Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> release3Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gain3Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mix3Attachement;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highAttachement;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> band4SoloAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> band4BypassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thres4Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratio4Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attack4Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> release4Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gain4Attachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mix4Attachement;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputAttachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mainMixAttachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> presetAttachment;
    
    // BORDERS
    juce::GroupComponent inputBorder;
    juce::GroupComponent inputTopBorder;
    juce::GroupComponent band1Border;
    juce::GroupComponent band1TopBorder;
    juce::GroupComponent band2Border;
    juce::GroupComponent band2TopBorder;
    juce::GroupComponent band3Border;
    juce::GroupComponent band3TopBorder;
    juce::GroupComponent band4Border;
    juce::GroupComponent band4TopBorder;
    juce::GroupComponent outputBorder;
    juce::GroupComponent outputTopBorder;
    
    // LABELS
    
    bbg_gui::bbg_dialLabel inputLabel { "Input" };
    
    bbg_gui::bbg_borderLabelMiddle bandLabel1 { "1" };
    bbg_gui::bbg_dialLabel thresholdLabel1 { "Threshold" };
    bbg_gui::bbg_dialLabel ratioLabel1 { "Ratio" };
    bbg_gui::bbg_meterLabel band1MeterLabel { "GR" };
    bbg_gui::bbg_dialLabel attackLabel1 { "Att" };
    bbg_gui::bbg_dialLabel releaseLabel1 { "Rel" };
    bbg_gui::bbg_dialLabel gainLabel1 { "Gain" };
    bbg_gui::bbg_dialLabel mixLabel1 { "Mix" };
    
    bbg_gui::bbg_horizontalSliderLabel lowLabel { "Low" };
    
    bbg_gui::bbg_borderLabelMiddle bandLabel2 { "2" };
    bbg_gui::bbg_dialLabel thresholdLabel2 { "Threshold" };
    bbg_gui::bbg_dialLabel ratioLabel2 { "Ratio" };
    bbg_gui::bbg_meterLabel band2MeterLabel { "GR" };
    bbg_gui::bbg_dialLabel attackLabel2 { "Att" };
    bbg_gui::bbg_dialLabel releaseLabel2 { "Rel" };
    bbg_gui::bbg_dialLabel gainLabel2 { "Gain" };
    bbg_gui::bbg_dialLabel mixLabel2 { "Mix" };
    
    bbg_gui::bbg_horizontalSliderLabel midLabel { "Mid" };
    
    bbg_gui::bbg_borderLabelMiddle bandLabel3 { "3" };
    bbg_gui::bbg_dialLabel thresholdLabel3 { "Threshold" };
    bbg_gui::bbg_dialLabel ratioLabel3 { "Ratio" };
    bbg_gui::bbg_meterLabel band3MeterLabel { "GR" };
    bbg_gui::bbg_dialLabel attackLabel3 { "Att" };
    bbg_gui::bbg_dialLabel releaseLabel3 { "Rel" };
    bbg_gui::bbg_dialLabel gainLabel3 { "Gain" };
    bbg_gui::bbg_dialLabel mixLabel3 { "Mix" };
    
    bbg_gui::bbg_horizontalSliderLabel highLabel { "High" };
    
    bbg_gui::bbg_borderLabelMiddle bandLabel4 { "4" };
    bbg_gui::bbg_dialLabel thresholdLabel4 { "Threshold" };
    bbg_gui::bbg_dialLabel ratioLabel4 { "Ratio" };
    bbg_gui::bbg_meterLabel band4MeterLabel { "GR" };
    bbg_gui::bbg_dialLabel attackLabel4 { "Att" };
    bbg_gui::bbg_dialLabel releaseLabel4 { "Rel" };
    bbg_gui::bbg_dialLabel gainLabel4 { "Gain" };
    bbg_gui::bbg_dialLabel mixLabel4 { "Mix" };
    
    bbg_gui::bbg_dialLabel outputLabel { "Output" };
    bbg_gui::bbg_horizontalSliderLabel mainMixLabel { "Mix" };
    
    bbg_gui::bbg_dialLabel olumay { "Olumay dsp" };
    bbg_gui::bbg_dialLabel curbTitle { "C U R B" };
    bbg_gui::bbg_dialLabel curbVersion { "version 1.1" };
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CURBAudioProcessor& audioProcessor;
    
    // METERS
    bbg_gui::VerticalGradientMeter inputMeterL, inputMeterR;
    bbg_gui::VerticalDiscreteMeter band1Meter, band2Meter, band3Meter, band4Meter;
    bbg_gui::VerticalGradientMeter outputMeterL, outputMeterR;
    
    juce::String inputTip = { "Input: boost or attenuate the level of the incoming before it undergoes dynamic processing" };
    juce::String thresholdTip = { "Threshold: sets where compression begins for this particular band. Signals above the threshold are attenuated by an amount specified by the Ratio parameter" };
    juce::String ratioTip = { "Ratio: sets the ratio between the input and output signal of this band. Settings below 1:1 will mean upward compression for this band" };
    juce::String attackTip = { "Attack: defines how long it takes to reach maximum compression once the signal exceeds the threshold" };
    juce::String releaseTip = { "Release: sets how long it takes for the compressor to return to normal operation after the signal falls below the threshold" };
    juce::String gainTip = { "Gain: the output level for a band post dynamic processing. With no dynamic processing, consider this as a band boost or cut" };
    juce::String mixTip = { "Mix: adjusts the balance between the compressed and uncompressed signals for this band" };
    juce::String outputTip = { "Output: boost or attenuate the level of the signal post dynamic processing" };
    
    juce::String soloTip = { "Solo: listen to this band post processing" };
    juce::String bypassTip = { "Bypass: returns the entire band to a unity gain status with no processing at all" };
    
    juce::String lowBandTip = { "Low: crossover point between Band 1 and 2. Frequencies below this number are processed in Band 1. Frequencies above it are processed in Band 2" };
    juce::String midBandTip = { "Mid: crossover point between Band 2 and 3. Frequencies below this number are processed in Band 2. Frequencies above it are processed in Band 3" };
    juce::String highBandTip = { "High: crossover point between Band 3 and 4. Frequencies below this number are processed in Band 3. Frequencies above it are processed in Band 4" };
    juce::String mainMixTip = { "Mix: adjusts the overall balance between the processed and unprocessed signals" };
    
    juce::String inputMeterTip = { "Input meter displaying stereo information" };
    juce::String outputMeterTip = { "Output meter displaying stereo information" };
    
    juce::String bandMeterTip = { "GR: displays gain reduction for this band. Each LED represent 3dB of gain reduction" };
    
    juce::String presetTip = { "Preset: various presets to get you started" };
    juce::String presetStepTip = { "Preset Step: step through the various presets" };
    
    juce::Label toolTip;
    
    //set of pointers in a vector that point to dials for tips
    std::vector<bbg_gui::bbg_Dial*> sliderPointer =     { &input,
                                                        &threshold1, &ratio1, &attack1, &release1, &gain1, &mix1,
                                                        &threshold2, &ratio2, &attack2, &release2, &gain2, &mix2,
                                                        &threshold3, &ratio3, &attack3, &release3, &gain3, &mix3,
                                                        &threshold4, &ratio4, &attack4, &release4, &gain4, &mix4,
                                                        &output};
    //set of labels in a vector holding strings
    std::vector<juce::String> sliderLabel =             { inputTip,
                                                        thresholdTip, ratioTip, attackTip, releaseTip, gainTip, mixTip,
                                                        thresholdTip, ratioTip, attackTip, releaseTip, gainTip, mixTip,
                                                        thresholdTip, ratioTip, attackTip, releaseTip, gainTip, mixTip,
                                                        thresholdTip, ratioTip, attackTip, releaseTip, gainTip, mixTip,
                                                        outputTip};
    
    //set of pointers in a vector that point to buttons for tips
    std::vector<bbg_gui::bbg_PushButton*> buttonPointer =   { &band1SoloButton, &band2SoloButton, &band3SoloButton, &band4SoloButton,
                                                            &band1BypassButton, &band2BypassButton, &band3BypassButton, &band4BypassButton };
    
    //set of labels in a vector holding strings
    std::vector<juce::String> buttonLabel =     { soloTip, soloTip, soloTip, soloTip,
                                                bypassTip, bypassTip, bypassTip, bypassTip };
    
    //set of pointers in a vector that point to buttons for tips NOT WORKING
    std::vector<bbg_gui::bbg_SliderHorizontal*> horizontalSliderPointer =   { &lowBandSlider, &midBandSlider, &highBandSlider, &mainMix };
    
    //set of labels in a vector holding strings
    std::vector<juce::String> horizontalLabel =     { lowBandTip, midBandTip, highBandTip, mainMixTip };
    
    //set of pointers in a vector that point to vertical meters for tips
    std::vector<bbg_gui::VerticalGradientMeter*> verticalMeterPointer =   { &inputMeterL, &inputMeterR, &outputMeterL, &outputMeterR };
    
    //set of labels in a vector holding strings
    std::vector<juce::String> verticalMeterLabel =     { inputMeterTip, inputMeterTip, outputMeterTip, outputMeterTip };
    
    //set of pointers in a vector that point to discrete meters for tips NOT WORKING
    std::vector<bbg_gui::VerticalDiscreteMeter*> bandMeterPointer =   { &band1Meter, &band2Meter, &band3Meter, &band4Meter };
    
    //set of labels in a vector holding strings
    std::vector<juce::String> bandMeterLabel =     { bandMeterTip, bandMeterTip, bandMeterTip, bandMeterTip };
    
    //set of pointers in a vector that point to preset for tips//only 1, just testing! NOT WORKING
    std::vector<bbg_gui::bbg_Menu*> presetPointer = { &preset };
    std::vector<juce::String> presetLabelTip = { presetTip };
    
    std::vector<juce::TextButton*> presetStepPointer = { &presetPrevButton, &presetNextButton };
    std::vector<juce::String> presetStepLabel = { presetStepTip, presetStepTip };
    
    void setPreset(float newThres1, float newRatio1, float newAttack1, float newRelease1, float newGain1, float newMix1, bool newSolo1, bool newBypass1,
                   float newThres2, float newRatio2, float newAttack2, float newRelease2, float newGain2, float newMix2, bool newSolo2, bool newBypass2,
                   float newThres3, float newRatio3, float newAttack3, float newRelease3, float newGain3, float newMix3, bool newSolo3, bool newBypass3,
                   float newThres4, float newRatio4, float newAttack4, float newRelease4, float newGain4, float newMix4, bool newSolo4, bool newBypass4,
                   float newInput, float newLowBand, float newMidBand, float newHighBand, float newOutput, float newMainMix);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CURBAudioProcessorEditor)
};
