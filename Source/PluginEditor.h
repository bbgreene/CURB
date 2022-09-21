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

private:
    // DIALS, BUTTONS AND MENUS
    bbg_gui::bbg_Dial input { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_PushButton band1SoloButton { "S" };
    bbg_gui::bbg_PushButton band1BypassButton { "BYP" };
    bbg_gui::bbg_Dial threshold1 { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio1 { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack1 { "", 1.0, 150.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial release1 { "", 2.0, 300.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain1 { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix1 { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_SliderHorizontal lowBandSlider { "", 40.0, 250.0, 1.0, 0.0, 0.0 };
    
    bbg_gui::bbg_PushButton band2SoloButton { "S" };
    bbg_gui::bbg_PushButton band2BypassButton { "BYP" };
    bbg_gui::bbg_Dial threshold2 { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio2 { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack2 { "", 1.0, 150.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial release2 { "", 2.0, 300.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain2 { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix2 { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_SliderHorizontal midBandSlider { "", 251.0, 6000.0, 1.0, 0.0, 0.0 };
    
    bbg_gui::bbg_PushButton band3SoloButton { "S" };
    bbg_gui::bbg_PushButton band3BypassButton { "BYP" };
    bbg_gui::bbg_Dial threshold3 { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio3 { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack3 { "", 1.0, 150.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial release3 { "", 2.0, 300.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain3 { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix3 { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_SliderHorizontal highBandSlider { "", 6001.0, 16000.0, 1.0, 0.0, 0.0 };
    
    bbg_gui::bbg_PushButton band4SoloButton { "S" };
    bbg_gui::bbg_PushButton band4BypassButton { "BYP" };
    bbg_gui::bbg_Dial threshold4 { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio4 { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack4 { "", 1.0, 150.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial release4 { "", 2.0, 300.0, 1.0, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain4 { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix4 { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_Dial output { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_SliderHorizontal  mainMix { "", 0.0, 100.0, 0.1, 0.0, 0.0 };

 
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CURBAudioProcessorEditor)
};
