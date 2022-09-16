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
    // SET DEFAULT FONT
    juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("Avenir Next");
       
    // DIALS, BUTTONS, MENUS & PARAMETER ATTACHMENTS
    threshold1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(threshold1);
    ratio1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(ratio1);
    attack1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(attack1);
    release1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(release1);
    gain1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(gain1);
    mix1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(mix1);
    
    //DIAL LABEL ATTACHMENTS
    thresholdLabel1.attachToComponent(&threshold1, false);
    ratioLabel1.attachToComponent(&ratio1, false);
    attackLabel1.attachToComponent(&attack1, false);
    releaseLabel1.attachToComponent(&release1, false);
    gainLabel1.attachToComponent(&gain1, false);
    mixLabel1.attachToComponent(&mix1, false);
    
    
    // BORDERS
    inputBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    inputBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    inputBorder.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(inputBorder);
    
    inputTopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    inputTopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    inputTopBorder.setTextLabelPosition(juce::Justification::centred);
    inputTopBorder.setText("Input");
    addAndMakeVisible(inputTopBorder);
    
    band1Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band1Border.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band1Border.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(band1Border);
    
    band1TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band1TopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band1TopBorder.setTextLabelPosition(juce::Justification::centred);
    band1TopBorder.setText("Band 1");
    addAndMakeVisible(band1TopBorder);

    band2Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band2Border.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band2Border.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(band2Border);
    
    band2TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band2TopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band2TopBorder.setTextLabelPosition(juce::Justification::centred);
    band2TopBorder.setText("Band 2");
    addAndMakeVisible(band2TopBorder);
    
    band3Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band3Border.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band3Border.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(band3Border);
    
    band3TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band3TopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band3TopBorder.setTextLabelPosition(juce::Justification::centred);
    band3TopBorder.setText("Band 3");
    addAndMakeVisible(band3TopBorder);
    
    band4Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band4Border.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band4Border.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(band4Border);
    
    band4TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band4TopBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    band4TopBorder.setTextLabelPosition(juce::Justification::centred);
    band4TopBorder.setText("Band 4");
    addAndMakeVisible(band4TopBorder);
    
    outputBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    outputBorder.setColour(juce::GroupComponent::ColourIds::textColourId, CustomColours::creamWhite.darker());
    outputBorder.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(outputBorder);
    
    outputTopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
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
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colours::darkred, getHeight() - getHeight(), juce::Colours::red.darker(), getHeight()));
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
    
    auto bigDialSize = getWidth() * 0.06;
    auto smallDialSize = getWidth() * 0.04;

    auto dialtopRowY = getHeight() * 0.313055;
    auto dialbottomRowY = getHeight() * 0.556191;

    auto bigDialXOne = band1Border.getX() * 1.08681;
    auto smallDialXOne = band1Border.getX() * 1.8352;
    auto smallDailGap = getWidth() * 0.042;

    threshold1.setBounds(bigDialXOne, dialtopRowY, bigDialSize, bigDialSize);
    ratio1.setBounds(bigDialXOne, dialbottomRowY, bigDialSize, bigDialSize);
    attack1.setBounds(smallDialXOne, dialtopRowY, smallDialSize, smallDialSize);
    release1.setBounds(smallDialXOne + smallDailGap, dialtopRowY, smallDialSize, smallDialSize);
    gain1.setBounds(smallDialXOne, dialbottomRowY, smallDialSize, smallDialSize);
    mix1.setBounds(smallDialXOne + smallDailGap, dialbottomRowY, smallDialSize, smallDialSize);
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
