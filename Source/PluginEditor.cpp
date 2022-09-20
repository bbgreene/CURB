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
    inputAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "input", input);
    addAndMakeVisible(input);
    
    threshold1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    thres1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "thres 1", threshold1);
    addAndMakeVisible(threshold1);
    ratio1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    ratio1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ratio 1", ratio1);
    addAndMakeVisible(ratio1);
    attack1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    attack1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "attack 1", attack1);
    addAndMakeVisible(attack1);
    release1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    release1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "release 1", release1);
    addAndMakeVisible(release1);
    gain1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    gain1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "gain1", gain1);
    addAndMakeVisible(gain1);
    mix1.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    mix1Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "fb1mix", mix1);
    addAndMakeVisible(mix1);
    
    threshold2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    thres2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "thres 2", threshold2);
    addAndMakeVisible(threshold2);
    ratio2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    ratio2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ratio 2", ratio2);
    addAndMakeVisible(ratio2);
    attack2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    attack2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "attack 2", attack2);
    addAndMakeVisible(attack2);
    release2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    release2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "release 2", release2);
    addAndMakeVisible(release2);
    gain2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    gain2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "gain2", gain2);
    addAndMakeVisible(gain2);
    mix2.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    mix2Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "fb2mix", mix2);
    addAndMakeVisible(mix2);
    
    threshold3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    thres3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "thres 3", threshold3);
    addAndMakeVisible(threshold3);
    ratio3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    ratio3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ratio 3", ratio3);
    addAndMakeVisible(ratio3);
    attack3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    attack3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "attack 3", attack3);
    addAndMakeVisible(attack3);
    release3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    release3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "release 3", release3);
    addAndMakeVisible(release3);
    gain3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    gain3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "gain3", gain3);
    addAndMakeVisible(gain3);
    mix3.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    mix3Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "fb3mix", mix3);
    addAndMakeVisible(mix3);
    
    threshold4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    thres4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "thres 4", threshold4);
    addAndMakeVisible(threshold4);
    ratio4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    ratio4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ratio 4", ratio4);
    addAndMakeVisible(ratio4);
    attack4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    attack4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "attack 4", attack4);
    addAndMakeVisible(attack4);
    release4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    release4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "release 4", release4);
    addAndMakeVisible(release4);
    gain4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    gain4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "gain4", gain4);
    addAndMakeVisible(gain4);
    mix4.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    mix4Attachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "fb4mix", mix4);
    addAndMakeVisible(mix4);
    
    output.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    outputAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "output", output);
    addAndMakeVisible(output);
    
    mainMix.setDialStyle(bbg_gui::bbg_Dial::DialStyle::kDialModernStyle);
    mainMixAttachement = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "main mix", mainMix);
    addAndMakeVisible(mainMix);
    
    // BORDERS
    band1Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    addAndMakeVisible(band1Border);
    
    band1TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    addAndMakeVisible(band1TopBorder);

    band2Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    addAndMakeVisible(band2Border);
    
    band2TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    addAndMakeVisible(band2TopBorder);
    
    band3Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    addAndMakeVisible(band3Border);
    
    band3TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    addAndMakeVisible(band3TopBorder);
    
    band4Border.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    addAndMakeVisible(band4Border);
    
    band4TopBorder.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::grey);
    addAndMakeVisible(band4TopBorder);
    
    
    //LABEL ATTACHMENTS
    inputLabel.attachToComponent(&input, false);
    
    bandLabel1.attachToComponent(&band1TopBorder, false);
    thresholdLabel1.attachToComponent(&threshold1, false);
    ratioLabel1.attachToComponent(&ratio1, false);
    attackLabel1.attachToComponent(&attack1, false);
    releaseLabel1.attachToComponent(&release1, false);
    gainLabel1.attachToComponent(&gain1, false);
    mixLabel1.attachToComponent(&mix1, false);
    
    bandLabel2.attachToComponent(&band2TopBorder, false);
    thresholdLabel2.attachToComponent(&threshold2, false);
    ratioLabel2.attachToComponent(&ratio2, false);
    attackLabel2.attachToComponent(&attack2, false);
    releaseLabel2.attachToComponent(&release2, false);
    gainLabel2.attachToComponent(&gain2, false);
    mixLabel2.attachToComponent(&mix2, false);
    
    bandLabel3.attachToComponent(&band3TopBorder, false);
    thresholdLabel3.attachToComponent(&threshold3, false);
    ratioLabel3.attachToComponent(&ratio3, false);
    attackLabel3.attachToComponent(&attack3, false);
    releaseLabel3.attachToComponent(&release3, false);
    gainLabel3.attachToComponent(&gain3, false);
    mixLabel3.attachToComponent(&mix3, false);
    
    bandLabel4.attachToComponent(&band4TopBorder, false);
    thresholdLabel4.attachToComponent(&threshold4, false);
    ratioLabel4.attachToComponent(&ratio4, false);
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

    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1260, 400);
}

CURBAudioProcessorEditor::~CURBAudioProcessorEditor()
{
}

//==============================================================================
void CURBAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colours::red.darker(), getHeight() - getHeight(), juce::Colours::lightgoldenrodyellow, getHeight()));
    g.fillRect(background);
}

void CURBAudioProcessorEditor::resized()
{
    
    /*
     band border width = 250
     band border gaps = 10
     input width = 80
     output width = 150
     
     4 x band borders = 1000
     3 x band border gaps = 30
     1 input width = 80
     output width = 150
     
     */
    auto borderWidthGap = getWidth() * 0.00794; //10
    auto largeBorderWidth = getWidth() * 0.19842; //250
    auto mainBorderHeight = getHeight() * .58; //
    auto topBorderHeight = getHeight() * 0.1; //40
    auto band1X = getWidth() * 0.0635;// 80
    auto borderY = getHeight() * 0.125; //50
    
    band1Border.setBounds(band1X, borderY, largeBorderWidth, mainBorderHeight);
    band1TopBorder.setBounds(band1X, borderY, largeBorderWidth, topBorderHeight);
    band2Border.setBounds(band1Border.getRight() + borderWidthGap, borderY, largeBorderWidth, mainBorderHeight);
    band2TopBorder.setBounds(band1Border.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    band3Border.setBounds(band2Border.getRight() + borderWidthGap, borderY, largeBorderWidth, mainBorderHeight);
    band3TopBorder.setBounds(band2Border.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    band4Border.setBounds(band3Border.getRight() + borderWidthGap, borderY, largeBorderWidth, mainBorderHeight);
    band4TopBorder.setBounds(band3Border.getRight() + borderWidthGap, borderY, largeBorderWidth, topBorderHeight);
    
    auto curbTitleX = borderWidthGap;
    auto curbTitleY = 5;
    auto curbTitleWidth = 140;
    auto curbTitleHeight = 30;
    auto versionX = 150;
    auto versionY = 10;
    auto versionWidth = getWidth() * 0.169246;
    auto versionHeight = getHeight() * 0.068969;
    auto olumayX = band4Border.getX() * 1.015;
    
    curbTitle.setBounds(curbTitleX, curbTitleY, curbTitleWidth, curbTitleHeight);
    curbVersion.setBounds(versionX, versionY, versionWidth, versionHeight);
    olumay.setBounds(olumayX, versionY, versionWidth, versionHeight);
    
    auto dialSize = getWidth() * 0.0532; // 67
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
    
    auto inputOutGapX = (band1X - dialSize) / 2;
    input.setBounds(inputOutGapX, dialbottomRowY, dialSize, dialSize);

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
 
    
    
    output.setBounds(band4Border.getRight() + inputOutGapX, dialbottomRowY, dialSize, dialSize);
    
    auto mainMixY = output.getBottom() + 16;
    mainMix.setBounds(band4Border.getRight() + inputOutGapX, mainMixY, dialSize, dialSize);
    
    auto inputMeterX = getWidth() * 0.0114;
    auto outputMeterX = band4Border.getRight() + inputMeterX;
    
    auto gradientMeterHeight = getHeight() * 0.324003;
    auto gradientMeterY = getHeight() * 0.147853;
    auto gradientMeterWidth = getWidth() * 0.018;
    auto gradientMeterGap = gradientMeterWidth * 1.3252;
    
    auto band1MeterX = threshold1.getRight() + 13;
    auto band2MeterX = threshold2.getRight() + 13;
    auto band3MeterX = threshold3.getRight() + 13;
    auto band4MeterX = threshold4.getRight() + 13;
    
    auto bandMeterY = getHeight() * 0.307755;
    auto bandMeterWidth = 20;
    auto bandMeterHeight = mainBorderHeight * 0.588493;

    inputMeterL.setBounds(inputMeterX, gradientMeterY, gradientMeterWidth, gradientMeterHeight);
    inputMeterR.setBounds(inputMeterX + gradientMeterGap, gradientMeterY, gradientMeterWidth, gradientMeterHeight);
    
    band1Meter.setBounds(band1MeterX, bandMeterY, bandMeterWidth, bandMeterHeight);
    band2Meter.setBounds(band2MeterX, bandMeterY, bandMeterWidth, bandMeterHeight);
    band3Meter.setBounds(band3MeterX, bandMeterY, bandMeterWidth, bandMeterHeight);
    band4Meter.setBounds(band4MeterX, bandMeterY, bandMeterWidth, bandMeterHeight);
    
    outputMeterL.setBounds(outputMeterX, gradientMeterY, gradientMeterWidth, gradientMeterHeight);
    outputMeterR.setBounds(outputMeterX + gradientMeterGap, gradientMeterY, gradientMeterWidth, gradientMeterHeight);
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
