/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CURBAudioProcessorEditor::CURBAudioProcessorEditor (CURBAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    // BORDERS
    inputBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    inputBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    inputBorder.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(inputBorder);
    
    inputTopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    inputTopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    inputTopBorder.setTextLabelPosition(juce::Justification::centred);
    inputTopBorder.setText("Input");
    addAndMakeVisible(inputTopBorder);
    
    band1Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    band1Border.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band1Border.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(band1Border);
    
    band1TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    band1TopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band1TopBorder.setTextLabelPosition(juce::Justification::centred);
    band1TopBorder.setText("Band 1");
    addAndMakeVisible(band1TopBorder);

    band2Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    band2Border.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band2Border.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(band2Border);
    
    band2TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    band2TopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band2TopBorder.setTextLabelPosition(juce::Justification::centred);
    band2TopBorder.setText("Band 2");
    addAndMakeVisible(band2TopBorder);
    
    band3Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    band3Border.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band3Border.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(band3Border);
    
    band3TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    band3TopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band3TopBorder.setTextLabelPosition(juce::Justification::centred);
    band3TopBorder.setText("Band 3");
    addAndMakeVisible(band3TopBorder);
    
    band4Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    band4Border.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band4Border.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(band4Border);
    
    band4TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    band4TopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band4TopBorder.setTextLabelPosition(juce::Justification::centred);
    band4TopBorder.setText("Band 4");
    addAndMakeVisible(band4TopBorder);
    
    outputBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    outputBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    outputBorder.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(outputBorder);
    
    outputTopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::purple.brighter());
    outputTopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    outputTopBorder.setTextLabelPosition(juce::Justification::centred);
    outputTopBorder.setText("Output");
    addAndMakeVisible(outputTopBorder);
    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1355, 400);
}

CURBAudioProcessorEditor::~CURBAudioProcessorEditor()
{
}

//==============================================================================
void CURBAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colours::purple.darker(), getHeight() - getHeight(), juce::Colours::purple.darker(), getHeight()));
    g.fillRect(background);
}

void CURBAudioProcessorEditor::resized()
{
    
    /*
     band border width = 250
     band border gaps = 15
     input/output width = 125
     
     4 x band borders = 1000
     7 x band border gaps = 105
     2 x input/output width = 250
     
     */
    auto leftMarginGap = getWidth() * 0.01108; //15
    auto borderWidthGap = getWidth() * 0.01108; //15
    auto smallBorderWidth = getWidth() * 0.09226; //125
    auto largeBorderWidth = getWidth() * 0.18451; //250
    auto mainBorderHeight = getHeight() *  0.7; //280
    auto topBorderHeight = getHeight() * 0.1; //40
    auto borderY = getHeight() * 0.125; //50
    
    inputBorder.setBounds(leftMarginGap, borderY, smallBorderWidth, mainBorderHeight);
    inputTopBorder.setBounds(leftMarginGap, borderY, smallBorderWidth, topBorderHeight);
    
    band1Border.setBounds(inputBorder.getRight() + borderWidthGap, borderY, largeBorderWidth, mainBorderHeight);
    band1TopBorder.setBounds(inputBorder.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    band2Border.setBounds(band1Border.getRight() + borderWidthGap, borderY, largeBorderWidth, mainBorderHeight);
    band2TopBorder.setBounds(band1Border.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    band3Border.setBounds(band2Border.getRight() + borderWidthGap, borderY, largeBorderWidth, mainBorderHeight);
    band3TopBorder.setBounds(band2Border.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    band4Border.setBounds(band3Border.getRight() + borderWidthGap, borderY, largeBorderWidth, mainBorderHeight);
    band4TopBorder.setBounds(band3Border.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    
    outputBorder.setBounds(band4Border.getRight() + borderWidthGap, borderY, smallBorderWidth, mainBorderHeight);
    outputTopBorder.setBounds(band4Border.getRight() + borderWidthGap, borderY, smallBorderWidth, topBorderHeight);
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
