/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CURBAudioProcessorEditor::CURBAudioProcessorEditor (CURBAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
inputMeterL([&](){ return  audioProcessor.getRmsValue(0);}),
inputMeterR([&](){ return audioProcessor.getRmsValue(1);}),
band1Meter([&](){ return audioProcessor.getRmsValue(2);}),
band2Meter([&](){ return audioProcessor.getRmsValue(3);}),
band3Meter([&](){ return audioProcessor.getRmsValue(4);}),
band4Meter([&](){ return audioProcessor.getRmsValue(5);}),
outputMeterL([&](){ return audioProcessor.getRmsValue(6);}),
outputMeterR([&](){ return audioProcessor.getRmsValue(7);})

{
    // SET DEFAULT FONT
    juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("Avenir Next");
       
    // DIALS, BUTTONS, MENUS & PARAMETER ATTACHMENTS
    input.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    input.addMouseListener(this, false);
    inputAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "input", input);
    addAndMakeVisible(input);

    band1SoloAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "solo 1", band1SoloButton);
    addAndMakeVisible(band1SoloButton);
    band1BypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "bypass 1", band1BypassButton);
    addAndMakeVisible(band1BypassButton);
    
    threshold1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    threshold1.addMouseListener(this, false);
    thres1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "thres 1", threshold1);
    addAndMakeVisible(threshold1);
    
    ratio1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    ratio1.addMouseListener(this, false);
    ratio1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ratio 1", ratio1);
    addAndMakeVisible(ratio1);
    attack1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    attack1.addMouseListener(this, false);
    attack1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "attack 1", attack1);
    addAndMakeVisible(attack1);
    release1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    release1.addMouseListener(this, false);
    release1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "release 1", release1);
    addAndMakeVisible(release1);
    gain1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    gain1.addMouseListener(this, false);
    gain1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "gain1", gain1);
    addAndMakeVisible(gain1);
    mix1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    mix1.addMouseListener(this, false);
    mix1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "fb1mix", mix1);
    addAndMakeVisible(mix1);
    
    lowBandSlider.addMouseListener(this, false);
    lowAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "low", lowBandSlider);
    addAndMakeVisible(lowBandSlider);
    
    band2SoloButton.addMouseListener(this, false);
    band2SoloAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "solo 2", band2SoloButton);
    addAndMakeVisible(band2SoloButton);
    band2BypassButton.addMouseListener(this, false);
    band2BypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "bypass 2", band2BypassButton);
    addAndMakeVisible(band2BypassButton);
    
    threshold2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    threshold2.addMouseListener(this, false);
    thres2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "thres 2", threshold2);
    addAndMakeVisible(threshold2);
    ratio2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    ratio2.addMouseListener(this, false);
    ratio2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ratio 2", ratio2);
    addAndMakeVisible(ratio2);
    attack2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    attack2.addMouseListener(this, false);
    attack2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "attack 2", attack2);
    addAndMakeVisible(attack2);
    release2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    release2.addMouseListener(this, false);
    release2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "release 2", release2);
    addAndMakeVisible(release2);
    gain2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    gain2.addMouseListener(this, false);
    gain2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "gain2", gain2);
    addAndMakeVisible(gain2);
    mix2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    mix2.addMouseListener(this, false);
    mix2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "fb2mix", mix2);
    addAndMakeVisible(mix2);
    
    midBandSlider.addMouseListener(this, false);
    midAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "mid", midBandSlider);
    addAndMakeVisible(midBandSlider);
    
    band3SoloButton.addMouseListener(this, false);
    band3SoloAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "solo 3", band3SoloButton);
    addAndMakeVisible(band3SoloButton);
    band3BypassButton.addMouseListener(this, false);
    band3BypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "bypass 3", band3BypassButton);
    addAndMakeVisible(band3BypassButton);
    
    threshold3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    threshold3.addMouseListener(this, false);
    thres3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "thres 3", threshold3);
    addAndMakeVisible(threshold3);
    ratio3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    ratio3.addMouseListener(this, false);
    ratio3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ratio 3", ratio3);
    addAndMakeVisible(ratio3);
    attack3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    attack3.addMouseListener(this, false);
    attack3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "attack 3", attack3);
    addAndMakeVisible(attack3);
    release3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    release3.addMouseListener(this, false);
    release3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "release 3", release3);
    addAndMakeVisible(release3);
    gain3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    gain3.addMouseListener(this, false);
    gain3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "gain3", gain3);
    addAndMakeVisible(gain3);
    mix3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    mix3.addMouseListener(this, false);
    mix3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "fb3mix", mix3);
    addAndMakeVisible(mix3);
    
    highBandSlider.addMouseListener(this, false);
    highAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "high", highBandSlider);
    addAndMakeVisible(highBandSlider);
    
    band4SoloButton.addMouseListener(this, false);
    band4SoloAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "solo 4", band4SoloButton);
    addAndMakeVisible(band4SoloButton);
    band4BypassButton.addMouseListener(this, false);
    band4BypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "bypass 4", band4BypassButton);
    addAndMakeVisible(band4BypassButton);
    
    threshold4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    threshold4.addMouseListener(this, false);
    thres4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "thres 4", threshold4);
    addAndMakeVisible(threshold4);
    ratio4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    ratio4.addMouseListener(this, false);
    ratio4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ratio 4", ratio4);
    addAndMakeVisible(ratio4);
    attack4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    attack4.addMouseListener(this, false);
    attack4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "attack 4", attack4);
    addAndMakeVisible(attack4);
    release4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    release4.addMouseListener(this, false);
    release4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "release 4", release4);
    addAndMakeVisible(release4);
    gain4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    gain4.addMouseListener(this, false);
    gain4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "gain4", gain4);
    addAndMakeVisible(gain4);
    mix4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    mix4.addMouseListener(this, false);
    mix4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "fb4mix", mix4);
    addAndMakeVisible(mix4);
    
    output.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    output.addMouseListener(this, false);
    outputAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "output", output);
    addAndMakeVisible(output);
    
    mainMix.addMouseListener(this, false);
    mainMixAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "main mix", mainMix);
    addAndMakeVisible(mainMix);
    
    // BORDERS
    auto alpha = 0.2;
    
    band1Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band1Border.setAlpha(alpha);
    addAndMakeVisible(band1Border);
    
    band1TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band1TopBorder.setAlpha(alpha);
    addAndMakeVisible(band1TopBorder);

    band2Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band2Border.setAlpha(alpha);
    addAndMakeVisible(band2Border);
    
    band2TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band2TopBorder.setAlpha(alpha);
    addAndMakeVisible(band2TopBorder);
    
    band3Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band3Border.setAlpha(alpha);
    addAndMakeVisible(band3Border);
    
    band3TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band3TopBorder.setAlpha(alpha);
    addAndMakeVisible(band3TopBorder);
    
    band4Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band4Border.setAlpha(alpha);
    addAndMakeVisible(band4Border);
    
    band4TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    band4TopBorder.setAlpha(alpha);
    addAndMakeVisible(band4TopBorder);
    
    
    //LABEL ATTACHMENTS
    inputLabel.attachToComponent(&input, false);
    
    bandLabel1.attachToComponent(&band1TopBorder, false);
    thresholdLabel1.attachToComponent(&threshold1, false);
    ratioLabel1.attachToComponent(&ratio1, false);
    band1MeterLabel.attachToComponent(&band1Meter, false);
    attackLabel1.attachToComponent(&attack1, false);
    releaseLabel1.attachToComponent(&release1, false);
    gainLabel1.attachToComponent(&gain1, false);
    mixLabel1.attachToComponent(&mix1, false);
    
    lowLabel.attachToComponent(&lowBandSlider, false);
    
    bandLabel2.attachToComponent(&band2TopBorder, false);
    thresholdLabel2.attachToComponent(&threshold2, false);
    ratioLabel2.attachToComponent(&ratio2, false);
    band2MeterLabel.attachToComponent(&band2Meter, false);
    attackLabel2.attachToComponent(&attack2, false);
    releaseLabel2.attachToComponent(&release2, false);
    gainLabel2.attachToComponent(&gain2, false);
    mixLabel2.attachToComponent(&mix2, false);
    
    midLabel.attachToComponent(&midBandSlider, false);

    bandLabel3.attachToComponent(&band3TopBorder, false);
    thresholdLabel3.attachToComponent(&threshold3, false);
    ratioLabel3.attachToComponent(&ratio3, false);
    band3MeterLabel.attachToComponent(&band3Meter, false);
    attackLabel3.attachToComponent(&attack3, false);
    releaseLabel3.attachToComponent(&release3, false);
    gainLabel3.attachToComponent(&gain3, false);
    mixLabel3.attachToComponent(&mix3, false);
    
    highLabel.attachToComponent(&highBandSlider, false);

    bandLabel4.attachToComponent(&band4TopBorder, false);
    thresholdLabel4.attachToComponent(&threshold4, false);
    ratioLabel4.attachToComponent(&ratio4, false);
    band4MeterLabel.attachToComponent(&band4Meter, false);
    attackLabel4.attachToComponent(&attack4, false);
    releaseLabel4.attachToComponent(&release4, false);
    gainLabel4.attachToComponent(&gain4, false);
    mixLabel4.attachToComponent(&mix4, false);
    
    outputLabel.attachToComponent(&output, false);
    mainMixLabel.attachToComponent(&mainMix, false);
    
    // METERS
    addAndMakeVisible(&inputMeterL);
    addAndMakeVisible(&inputMeterR);
    addAndMakeVisible(&band1Meter);
    addAndMakeVisible(&band2Meter);
    addAndMakeVisible(&band3Meter);
    addAndMakeVisible(&band4Meter);
    addAndMakeVisible(&outputMeterL);
    addAndMakeVisible(&outputMeterR);
    
    // TITLE
    curbTitle.setFont(juce::Font (40.0f, juce::Font::plain));
    curbTitle.setJustificationType(juce::Justification::centredLeft);
    curbTitle.setColour(juce::Label::textColourId, juce::Colours::mintcream);
    addAndMakeVisible(curbTitle);
    
    curbVersion.setFont(juce::Font (15.0f, juce::Font::plain));
    curbVersion.setJustificationType(juce::Justification::centredLeft);
    curbVersion.setColour(juce::Label::textColourId, juce::Colours::lightslategrey.brighter());
    addAndMakeVisible(curbVersion);
    
    olumay.setFont(juce::Font (15.0f, juce::Font::plain));
    olumay.setJustificationType(juce::Justification::centredLeft);
    olumay.setColour(juce::Label::textColourId, juce::Colours::steelblue.brighter());
    addAndMakeVisible(olumay);
                         
    toolTip.setFont(juce::Font ("Avenir Next", 15, juce::Font::FontStyleFlags::plain));
    toolTip.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    addAndMakeVisible(toolTip);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1190, 330);
}

CURBAudioProcessorEditor::~CURBAudioProcessorEditor()
{
    for(int i = 0; i < sliderPointer.size(); ++i)
    {
        sliderPointer[i]->setLookAndFeel(nullptr);
    }
    
}

//==============================================================================
void CURBAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colours::gainsboro, getHeight() - getHeight(),juce::Colours::gainsboro.darker(), getHeight()));
    g.fillRect(background);
}



void CURBAudioProcessorEditor::resized()
{
    
    /*
     gradient meter width = 15
     gradient meter gap = 19
     dial size = 67
     
     input area size (band border 1st X) = 80
     band border width = 250
     band border gap = 10
     output area size = 80
     
     Total width:
     Input/output area size x 2 = 160
     4 x band border = 1000
     3 x border gaps = 30
     TOTAL WIDTH = 1190
    
     topborder height = 40
     band border height = 232
     crossoverborderheight = 85
     border y gap = 10
     comment area = 40
     
     4 x border y gap = 40
     1 x crossoverborderheight = 90
     1 x band border height = 232
     1 x comment area = 30
     TOTAL HEIGHT = 392
    */
    
    auto curbTitleX = 6;
    auto curbTitleY = 8;
    auto curbTitleWidth = 120;
    auto curbTitleHeight = 28;
    
    auto curbVersionX = 50;
    auto curbVersionY = 33;
    auto curbVersionWidth = 70;
    auto curbVersionHeight = 18;
    
    auto olumayX = 1112;
    auto olumayY = 27;
    auto olumayWidth = 100;
    auto olumayHeight = 13;
    
    curbTitle.setBounds(curbTitleX, curbTitleY, curbTitleWidth, curbTitleHeight);
    curbVersion.setBounds(curbVersionX, curbVersionY, curbVersionWidth, curbVersionHeight);
    olumay.setBounds(olumayX, olumayY, olumayWidth, olumayHeight);
    
    auto band1X = 80;// 80
    auto borderY = 52;
    auto borderWidthGap = 10; //10
    auto largeBorderWidth = 250; //250
    auto largeBorderHeight = 232; // 232
    auto topBorderHeight = 40; //40
    
    band1Border.setBounds(band1X, borderY, largeBorderWidth, largeBorderHeight);
    band1TopBorder.setBounds(band1X, borderY, largeBorderWidth, topBorderHeight);
    band2Border.setBounds(band1Border.getRight() + borderWidthGap, borderY, largeBorderWidth, largeBorderHeight);
    band2TopBorder.setBounds(band1Border.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    band3Border.setBounds(band2Border.getRight() + borderWidthGap, borderY, largeBorderWidth, largeBorderHeight);
    band3TopBorder.setBounds(band2Border.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    band4Border.setBounds(band3Border.getRight() + borderWidthGap, borderY, largeBorderWidth, largeBorderHeight);
    band4TopBorder.setBounds(band3Border.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    
    auto bandSliderXGap = 26;
    auto bandSliderY = 25;
    auto bandSliderWidth = 61;
    auto bandSliderHeight = 24;

    lowBandSlider.setBounds(band1Border.getRight() - bandSliderXGap, bandSliderY, bandSliderWidth, bandSliderHeight);
    midBandSlider.setBounds(band2Border.getRight() - bandSliderXGap, bandSliderY, bandSliderWidth, bandSliderHeight);
    highBandSlider.setBounds(band3Border.getRight() - bandSliderXGap, bandSliderY, bandSliderWidth, bandSliderHeight);
    
    auto inputOutputMeterX = 26;
    auto inputOutputMeterY = 8;
    auto inputOutputMeterWidth = 12;
    auto inputOutputMeterHeight = 129;
    auto inputOutputMeterXGap = 4;
    
    auto inputOutGapX = 6.5;
    auto dialTopRowGapY = 65;
    auto dialBottomRowGapY = 154;
    auto dialSize = 67;
    
    inputMeterL.setBounds(inputOutputMeterX, band1Border.getY() + inputOutputMeterY, inputOutputMeterWidth, inputOutputMeterHeight);
    inputMeterR.setBounds(inputMeterL.getRight() + inputOutputMeterXGap, band1Border.getY() + inputOutputMeterY, inputOutputMeterWidth, inputOutputMeterHeight);
    input.setBounds(inputOutGapX, band1Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    
    auto soloXGap = 25;
    auto soloBypassYGap = 13;
    auto bypassXGap = 189;
    auto buttonWidth = 35;
    auto buttonHeight = 18;
    auto bandThresRatioXGap = 10;
    auto bandAttGainXGap = 110;
    auto bandRelMixXGap = 173;
    auto bandMeterXGap = 86;
    auto bandMeterYGap = 73;
    auto bandMeterWidth = 26;
    auto bandMeterHeight = 149;
    
    
    band1SoloButton.setBounds(band1Border.getX() + soloXGap, band1Border.getY() + soloBypassYGap, buttonWidth, buttonHeight);
    band1BypassButton.setBounds(band1Border.getX() + bypassXGap, band1Border.getY() + soloBypassYGap, buttonWidth, buttonHeight);
    threshold1.setBounds(band1Border.getX() + bandThresRatioXGap, band1Border.getY() + dialTopRowGapY, dialSize, dialSize);
    ratio1.setBounds(band1Border.getX() + bandThresRatioXGap, band1Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    band1Meter.setBounds(band1Border.getX() + bandMeterXGap, band1Border.getY() + bandMeterYGap, bandMeterWidth, bandMeterHeight);
    attack1.setBounds(band1Border.getX() + bandAttGainXGap, band1Border.getY() + dialTopRowGapY, dialSize, dialSize);
    gain1.setBounds(band1Border.getX() + bandAttGainXGap, band1Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    release1.setBounds(band1Border.getX() + bandRelMixXGap, band1Border.getY() + dialTopRowGapY, dialSize, dialSize);
    mix1.setBounds(band1Border.getX() + bandRelMixXGap, band1Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    
    band2SoloButton.setBounds(band2Border.getX() + soloXGap, band2Border.getY() + soloBypassYGap, buttonWidth, buttonHeight);
    band2BypassButton.setBounds(band2Border.getX() + bypassXGap, band2Border.getY() + soloBypassYGap, buttonWidth, buttonHeight);
    threshold2.setBounds(band2Border.getX() + bandThresRatioXGap, band2Border.getY() + dialTopRowGapY, dialSize, dialSize);
    ratio2.setBounds(band2Border.getX() + bandThresRatioXGap, band2Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    band2Meter.setBounds(band2Border.getX() + bandMeterXGap, band2Border.getY() + bandMeterYGap, bandMeterWidth, bandMeterHeight);
    attack2.setBounds(band2Border.getX() + bandAttGainXGap, band2Border.getY() + dialTopRowGapY, dialSize, dialSize);
    gain2.setBounds(band2Border.getX() + bandAttGainXGap, band2Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    release2.setBounds(band2Border.getX() + bandRelMixXGap, band2Border.getY() + dialTopRowGapY, dialSize, dialSize);
    mix2.setBounds(band2Border.getX() + bandRelMixXGap, band2Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    
    band3SoloButton.setBounds(band3Border.getX() + soloXGap, band3Border.getY() + soloBypassYGap, buttonWidth, buttonHeight);
    band3BypassButton.setBounds(band3Border.getX() + bypassXGap, band3Border.getY() + soloBypassYGap, buttonWidth, buttonHeight);
    threshold3.setBounds(band3Border.getX() + bandThresRatioXGap, band3Border.getY() + dialTopRowGapY, dialSize, dialSize);
    ratio3.setBounds(band3Border.getX() + bandThresRatioXGap, band3Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    band3Meter.setBounds(band3Border.getX() + bandMeterXGap, band3Border.getY() + bandMeterYGap, bandMeterWidth, bandMeterHeight);
    attack3.setBounds(band3Border.getX() + bandAttGainXGap, band3Border.getY() + dialTopRowGapY, dialSize, dialSize);
    gain3.setBounds(band3Border.getX() + bandAttGainXGap, band3Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    release3.setBounds(band3Border.getX() + bandRelMixXGap, band3Border.getY() + dialTopRowGapY, dialSize, dialSize);
    mix3.setBounds(band3Border.getX() + bandRelMixXGap, band3Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    
    band4SoloButton.setBounds(band4Border.getX() + soloXGap, band4Border.getY() + soloBypassYGap, buttonWidth, buttonHeight);
    band4BypassButton.setBounds(band4Border.getX() + bypassXGap, band4Border.getY() + soloBypassYGap, buttonWidth, buttonHeight);
    threshold4.setBounds(band4Border.getX() + bandThresRatioXGap, band4Border.getY() + dialTopRowGapY, dialSize, dialSize);
    ratio4.setBounds(band4Border.getX() + bandThresRatioXGap, band4Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    band4Meter.setBounds(band4Border.getX() + bandMeterXGap, band4Border.getY() + bandMeterYGap, bandMeterWidth, bandMeterHeight);
    attack4.setBounds(band4Border.getX() + bandAttGainXGap, band4Border.getY() + dialTopRowGapY, dialSize, dialSize);
    gain4.setBounds(band4Border.getX() + bandAttGainXGap, band4Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    release4.setBounds(band4Border.getX() + bandRelMixXGap, band4Border.getY() + dialTopRowGapY, dialSize, dialSize);
    mix4.setBounds(band4Border.getX() + bandRelMixXGap, band4Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    
    outputMeterL.setBounds(band4Border.getRight() + inputOutputMeterX, band4Border.getY() + inputOutputMeterY, inputOutputMeterWidth, inputOutputMeterHeight);
    outputMeterR.setBounds(outputMeterL.getRight() + inputOutputMeterXGap, band4Border.getY() + inputOutputMeterY, inputOutputMeterWidth, inputOutputMeterHeight);
    output.setBounds(band4Border.getRight() + inputOutGapX, band4Border.getY() + dialBottomRowGapY, dialSize, dialSize);
    
    auto mainMixXGap = 3;
    auto mainMixYGap = 84;
        
    mainMix.setBounds(output.getX() + mainMixXGap, output.getY() + mainMixYGap, bandSliderWidth, bandSliderHeight);
    
    toolTip.setBounds(20, 300, 700, 30);
}

void CURBAudioProcessorEditor::mouseEnter(const juce::MouseEvent &event)
{
    for(int i = 0; i < sliderPointer.size(); ++i)
    {
        if(event.eventComponent == sliderPointer[i])
        {
            toolTip.setText(sliderLabel[i], juce::dontSendNotification);
        }
    }
    
}
    

void CURBAudioProcessorEditor::mouseExit(const juce::MouseEvent &event)
{
    for(int i = 0; i < sliderPointer.size(); ++i)
    {
        if(event.eventComponent == sliderPointer[i])
        {
            toolTip.setText("", juce::dontSendNotification);
        }
    }
}

