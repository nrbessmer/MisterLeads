/*
  ==============================================================================
    Mister Leads - PluginEditor.h
    (c)(p) 2026 Tully EDM Vibe
  ==============================================================================
*/
#pragma once
#include "PluginProcessor.h"

class MisterLeadsEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit MisterLeadsEditor (MisterLeadsProcessor&);
    ~MisterLeadsEditor() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;   // public so tests / the video renderer can drive it

    MisterLeadsProcessor& proc;
    tui::LnF lnf;
    juce::Image logo;
    tui::PresetBar presetBar;
    tui::Scope scope;
    tui::SynthPanel panel;
    juce::MidiKeyboardComponent keyboard;
    juce::TooltipWindow tooltips { this, 500 };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MisterLeadsEditor)
};
