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
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CURBAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CURBAudioProcessorEditor)
};
