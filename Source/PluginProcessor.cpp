/*
  ==============================================================================
    Mister Leads - PluginProcessor.cpp
    (c)(p) 2026 Tully EDM Vibe
  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::AudioProcessorValueTreeState::ParameterLayout MisterLeadsProcessor::createLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout l;
    tsyn::addSynthParameters (l);
    return l;
}

MisterLeadsProcessor::MisterLeadsProcessor()
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMS", createLayout())
{
    reader.attach (apvts);
    loadPreset (0);
}

bool MisterLeadsProcessor::isBusesLayoutSupported (const BusesLayout& l) const
{
    const auto out = l.getMainOutputChannelSet();
    return out == juce::AudioChannelSet::stereo() || out == juce::AudioChannelSet::mono();
}

void MisterLeadsProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    engine.prepare (sampleRate, juce::jmax (1, samplesPerBlock));
    keyboardState.reset();
}

void MisterLeadsProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals nd;
    const int n = buffer.getNumSamples();
    const int nch = buffer.getNumChannels();
    if (n == 0 || nch == 0) return;

    double bpm = 120.0, ppq = 0.0; bool playing = false;
    if (auto* ph = getPlayHead())
        if (auto pos = ph->getPosition())
        {
            if (auto b = pos->getBpm()) bpm = *b;
            if (auto p = pos->getPpqPosition()) ppq = *p;
            playing = pos->getIsPlaying();
        }

    tsyn::Params p; tsyn::FxParams f;
    const double lfoBeats = reader.read (p, f, bpm);
    engine.setParams (p, f);
    engine.setLfoSync (lfoBeats > 0.0 && playing, ppq, lfoBeats);

    keyboardState.processNextMidiBuffer (midi, 0, n, true);   // on-screen keyboard

    float* L = buffer.getWritePointer (0);
    float* R = nch > 1 ? buffer.getWritePointer (1) : nullptr;
    juce::HeapBlock<float> monoR;
    if (R == nullptr) { monoR.allocate ((size_t) n, true); R = monoR.get(); }

    // sample-accurate: render up to each MIDI event, then apply it
    int pos = 0;
    for (const auto meta : midi)
    {
        const int at = juce::jlimit (0, n, meta.samplePosition);
        if (at > pos) { engine.render (L + pos, R + pos, at - pos); pos = at; }
        engine.handleMidi (meta.getMessage());
    }
    if (pos < n) engine.render (L + pos, R + pos, n - pos);

    if (nch == 1) for (int i = 0; i < n; ++i) L[i] = 0.5f * (L[i] + R[i]);
    for (int c = 2; c < nch; ++c) buffer.clear (c, 0, n);
    scope.push (L, nch > 1 ? R : L, n);
    midi.clear();
}

void MisterLeadsProcessor::loadPreset (int index)
{
    if (! juce::isPositiveAndBelow (index, (int) mld::presets().size())) return;
    tsyn::applyPreset (apvts, mld::presets()[(size_t) index]);
    currentPreset = index;
}

void MisterLeadsProcessor::getStateInformation (juce::MemoryBlock& dest)
{
    auto st = apvts.copyState();
    st.setProperty ("preset", currentPreset, nullptr);
    if (auto xml = st.createXml()) copyXmlToBinary (*xml, dest);
}

void MisterLeadsProcessor::setStateInformation (const void* data, int size)
{
    if (auto xml = getXmlFromBinary (data, size))
        if (xml->hasTagName (apvts.state.getType()))
        {
            auto st = juce::ValueTree::fromXml (*xml);
            currentPreset = juce::jlimit (0, getNumPrograms() - 1, (int) st.getProperty ("preset", 0));
            apvts.replaceState (st);
        }
}

juce::AudioProcessorEditor* MisterLeadsProcessor::createEditor() { return new MisterLeadsEditor (*this); }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new MisterLeadsProcessor(); }
