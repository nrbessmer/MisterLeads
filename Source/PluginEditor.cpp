/*
  ==============================================================================
    Mister Leads - PluginEditor.cpp
    (c)(p) 2026 Tully EDM Vibe
  ==============================================================================
*/
#include "PluginEditor.h"
#include "BinaryData.h"

MisterLeadsEditor::MisterLeadsEditor (MisterLeadsProcessor& p)
    : AudioProcessorEditor (&p), proc (p),
      presetBar (mld::presets()), scope (p.scope, tui::Col::pink), panel (p.apvts),
      keyboard (p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    setLookAndFeel (&lnf);
    logo = juce::ImageCache::getFromMemory (BinaryData::TullyLogo_png, BinaryData::TullyLogo_pngSize);

    presetBar.getCurrent = [this] { return proc.getCurrentPreset(); };
    presetBar.load = [this] (int i) { proc.loadPreset (i); };
    presetBar.sync();

    keyboard.setAvailableRange (24, 108);
    keyboard.setLowestVisibleKey (24);
    keyboard.setScrollButtonsVisible (false);
    keyboard.setColour (juce::MidiKeyboardComponent::whiteNoteColourId, juce::Colour (0xffd9e1ea));
    keyboard.setColour (juce::MidiKeyboardComponent::blackNoteColourId, juce::Colour (0xff13171d));
    keyboard.setColour (juce::MidiKeyboardComponent::keySeparatorLineColourId, juce::Colour (0xff2a323d));
    keyboard.setColour (juce::MidiKeyboardComponent::keyDownOverlayColourId, tui::Col::pink);
    keyboard.setColour (juce::MidiKeyboardComponent::mouseOverKeyOverlayColourId, tui::Col::cyan.withAlpha (0.35f));
    keyboard.setColour (juce::MidiKeyboardComponent::shadowColourId, juce::Colours::transparentBlack);
    keyboard.setColour (juce::MidiKeyboardComponent::upDownButtonBackgroundColourId, tui::Col::panelHi);

    for (juce::Component* c : std::initializer_list<juce::Component*> { &presetBar, &scope, &panel, &keyboard })
        addAndMakeVisible (c);

    setSize (1100, 680);
    startTimerHz (30);
}

MisterLeadsEditor::~MisterLeadsEditor() { stopTimer(); setLookAndFeel (nullptr); }

void MisterLeadsEditor::timerCallback()
{
    scope.refresh();
    presetBar.sync();
}

void MisterLeadsEditor::paint (juce::Graphics& g)
{
    g.fillAll (tui::Col::bg);
    tui::paintHeader (g, logo, "MISTER LEADS", "supersaw, psy, acid, FM, pluck + vintage mono", tui::Col::pink);
    tui::paintFooter (g, getLocalBounds().removeFromBottom (18).reduced (12, 0));
}

void MisterLeadsEditor::resized()
{
    auto b = getLocalBounds().reduced (12);
    b.removeFromBottom (12);
    auto header = b.removeFromTop (60);
    scope.setBounds (header.removeFromRight (190).reduced (0, 4));
    header.removeFromRight (12);
    presetBar.setBounds (header.removeFromRight (360).withTrimmedTop (2));
    b.removeFromTop (6);
    keyboard.setBounds (b.removeFromBottom (68));
    keyboard.setKeyWidth ((float) keyboard.getWidth() / 50.0f);   // C1..C8 = 50 white keys
    b.removeFromBottom (8);
    panel.setBounds (b);
}
