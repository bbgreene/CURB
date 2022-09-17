/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "../Source/bbg_gui/Dial.h"
#include "../Source/bbg_gui/Toggle.h"
#include "../Source/bbg_gui/PushButton.h"
#include "../Source/bbg_gui/Menu.h"
#include "../Source/bbg_gui/Label.h"


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
    bbg_gui::bbg_Dial threshold1 { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio1 { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack1 { "", 0.1, 150.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial release1 { "", 2.0, 300.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain1 { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix1 { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_Dial threshold2 { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio2 { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack2 { "", 0.1, 150.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial release2 { "", 2.0, 300.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain2 { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix2 { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_Dial threshold3 { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio3 { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack3 { "", 0.1, 150.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial release3 { "", 2.0, 300.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain3 { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix3 { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
    
    bbg_gui::bbg_Dial threshold4 { "", -50.0, 0.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial ratio4 { "", 0.5, 10.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial attack4 { "", 0.1, 150.0, 0.01, 0.0, 0.0 };
    bbg_gui::bbg_Dial release4 { "", 2.0, 300.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial gain4 { "", -24.0, 24.0, 0.1, 0.0, 0.0 };
    bbg_gui::bbg_Dial mix4 { "", 0.0, 100.0, 0.1, 0.0, 0.0 };
 
    
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
    bbg_gui::bbg_dialLabel thresholdLabel1 { "Threshold" };
    bbg_gui::bbg_dialLabel ratioLabel1 { "Ratio" };
    bbg_gui::bbg_dialLabel attackLabel1 { "Att" };
    bbg_gui::bbg_dialLabel releaseLabel1 { "Rel" };
    bbg_gui::bbg_dialLabel gainLabel1 { "Gain" };
    bbg_gui::bbg_dialLabel mixLabel1 { "Mix" };
    
    bbg_gui::bbg_dialLabel thresholdLabel2 { "Threshold" };
    bbg_gui::bbg_dialLabel ratioLabel2 { "Ratio" };
    bbg_gui::bbg_dialLabel attackLabel2 { "Att" };
    bbg_gui::bbg_dialLabel releaseLabel2 { "Rel" };
    bbg_gui::bbg_dialLabel gainLabel2 { "Gain" };
    bbg_gui::bbg_dialLabel mixLabel2 { "Mix" };
    
    bbg_gui::bbg_dialLabel thresholdLabel3 { "Threshold" };
    bbg_gui::bbg_dialLabel ratioLabel3 { "Ratio" };
    bbg_gui::bbg_dialLabel attackLabel3 { "Att" };
    bbg_gui::bbg_dialLabel releaseLabel3 { "Rel" };
    bbg_gui::bbg_dialLabel gainLabel3 { "Gain" };
    bbg_gui::bbg_dialLabel mixLabel3 { "Mix" };
    
    bbg_gui::bbg_dialLabel thresholdLabel4 { "Threshold" };
    bbg_gui::bbg_dialLabel ratioLabel4 { "Ratio" };
    bbg_gui::bbg_dialLabel attackLabel4 { "Att" };
    bbg_gui::bbg_dialLabel releaseLabel4 { "Rel" };
    bbg_gui::bbg_dialLabel gainLabel4 { "Gain" };
    bbg_gui::bbg_dialLabel mixLabel4 { "Mix" };
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CURBAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CURBAudioProcessorEditor)
};
