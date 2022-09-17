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
    
    threshold2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(threshold2);
    ratio2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(ratio2);
    attack2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(attack2);
    release2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(release2);
    gain2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(gain2);
    mix2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(mix2);
    
    threshold3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(threshold3);
    ratio3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(ratio3);
    attack3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(attack3);
    release3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(release3);
    gain3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(gain3);
    mix3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(mix3);
    
    threshold4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(threshold4);
    ratio4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(ratio4);
    attack4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(attack4);
    release4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(release4);
    gain4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(gain4);
    mix4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    addAndMakeVisible(mix4);
    
    //DIAL LABEL ATTACHMENTS
    thresholdLabel1.attachToComponent(&threshold1, false);
    ratioLabel1.attachToComponent(&ratio1, false);
    attackLabel1.attachToComponent(&attack1, false);
    releaseLabel1.attachToComponent(&release1, false);
    gainLabel1.attachToComponent(&gain1, false);
    mixLabel1.attachToComponent(&mix1, false);
    
    thresholdLabel2.attachToComponent(&threshold2, false);
    ratioLabel2.attachToComponent(&ratio2, false);
    attackLabel2.attachToComponent(&attack2, false);
    releaseLabel2.attachToComponent(&release2, false);
    gainLabel2.attachToComponent(&gain2, false);
    mixLabel2.attachToComponent(&mix2, false);
    
    thresholdLabel3.attachToComponent(&threshold3, false);
    ratioLabel3.attachToComponent(&ratio3, false);
    attackLabel3.attachToComponent(&attack3, false);
    releaseLabel3.attachToComponent(&release3, false);
    gainLabel3.attachToComponent(&gain3, false);
    mixLabel3.attachToComponent(&mix3, false);
    
    thresholdLabel4.attachToComponent(&threshold4, false);
    ratioLabel4.attachToComponent(&ratio4, false);
    attackLabel4.attachToComponent(&attack4, false);
    releaseLabel4.attachToComponent(&release4, false);
    gainLabel4.attachToComponent(&gain4, false);
    mixLabel4.attachToComponent(&mix4, false);
    
    
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
    auto mainBorderHeight = getHeight() *  0.6; //280
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
    
    auto dialSize = getWidth() * 0.05;
    auto dialtopRowY = getHeight() * 0.287877;
    auto dialbottomRowY = getHeight() * 0.513981;

    auto dialLeftXone = band1Border.getX() + 8;
    auto dialRightXone = band1Border.getX() + 116;
    auto dialLeftXtwo = band2Border.getX() + 8;
    auto dialRightXtwo = band2Border.getX() + 116;
    auto dialLeftXthree = band3Border.getX() + 8;
    auto dialRightXthree = band3Border.getX() + 116;
    auto dialLeftXfour = band4Border.getX() + 8;
    auto dialRightXfour = band4Border.getX() + 116;
    
    
    auto dialRightGap = getWidth() * 0.045;

    threshold1.setBounds(dialLeftXone, dialtopRowY, dialSize, dialSize);
    ratio1.setBounds(dialLeftXone, dialbottomRowY, dialSize, dialSize);
    attack1.setBounds(dialRightXone, dialtopRowY, dialSize, dialSize);
    release1.setBounds(dialRightXone + dialRightGap, dialtopRowY, dialSize, dialSize);
    gain1.setBounds(dialRightXone, dialbottomRowY, dialSize, dialSize);
    mix1.setBounds(dialRightXone + dialRightGap, dialbottomRowY, dialSize, dialSize);
    
    threshold2.setBounds(dialLeftXtwo, dialtopRowY, dialSize, dialSize);
    ratio2.setBounds(dialLeftXtwo, dialbottomRowY, dialSize, dialSize);
    attack2.setBounds(dialRightXtwo, dialtopRowY, dialSize, dialSize);
    release2.setBounds(dialRightXtwo + dialRightGap, dialtopRowY, dialSize, dialSize);
    gain2.setBounds(dialRightXtwo, dialbottomRowY, dialSize, dialSize);
    mix2.setBounds(dialRightXtwo + dialRightGap, dialbottomRowY, dialSize, dialSize);

    threshold3.setBounds(dialLeftXthree, dialtopRowY, dialSize, dialSize);
    ratio3.setBounds(dialLeftXthree, dialbottomRowY, dialSize, dialSize);
    attack3.setBounds(dialRightXthree, dialtopRowY, dialSize, dialSize);
    release3.setBounds(dialRightXthree + dialRightGap, dialtopRowY, dialSize, dialSize);
    gain3.setBounds(dialRightXthree, dialbottomRowY, dialSize, dialSize);
    mix3.setBounds(dialRightXthree + dialRightGap, dialbottomRowY, dialSize, dialSize);

    threshold4.setBounds(dialLeftXfour, dialtopRowY, dialSize, dialSize);
    ratio4.setBounds(dialLeftXfour, dialbottomRowY, dialSize, dialSize);
    attack4.setBounds(dialRightXfour, dialtopRowY, dialSize, dialSize);
    release4.setBounds(dialRightXfour + dialRightGap, dialtopRowY, dialSize, dialSize);
    gain4.setBounds(dialRightXfour, dialbottomRowY, dialSize, dialSize);
    mix4.setBounds(dialRightXfour + dialRightGap, dialbottomRowY, dialSize, dialSize);
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
