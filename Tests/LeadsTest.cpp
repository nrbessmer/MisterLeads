// MLTest: Mister Leads self-test.
//   MLTest [outDir]   -> runs all checks, writes ui.png and preset_levels.txt into outDir
#include <juce_audio_utils/juce_audio_utils.h>
#include "../Source/PluginProcessor.h"
#include "../Source/PluginEditor.h"
#include <chrono>

static int failures = 0;
static void check (bool ok, const juce::String& what, const juce::String& detail = {})
{
    printf ("  [%s] %-52s %s\n", ok ? "PASS" : "FAIL", what.toRawUTF8(), detail.toRawUTF8());
    if (! ok) ++failures;
}

struct Ev { double t; int note; bool on; float vel; };

// renders events through the processor in host-sized blocks, returns stereo audio
static juce::AudioBuffer<float> run (MisterLeadsProcessor& p, const std::vector<Ev>& evs, double seconds, double sr, int block = 512,
                                     int* maxVoices = nullptr)
{
    const int N = (int) (seconds * sr);
    juce::AudioBuffer<float> out (2, N); out.clear();
    juce::AudioBuffer<float> buf (2, block);
    size_t e = 0;
    for (int pos = 0; pos < N; pos += block)
    {
        const int n = juce::jmin (block, N - pos);
        buf.setSize (2, n, false, false, true); buf.clear();
        juce::MidiBuffer mb;
        while (e < evs.size() && (int) (evs[e].t * sr) < pos + n)
        {
            const int at = juce::jmax (0, (int) (evs[e].t * sr) - pos);
            mb.addEvent (evs[e].on ? juce::MidiMessage::noteOn (1, evs[e].note, evs[e].vel) : juce::MidiMessage::noteOff (1, evs[e].note), at);
            ++e;
        }
        p.processBlock (buf, mb);
        if (maxVoices) *maxVoices = juce::jmax (*maxVoices, p.engine.activeVoices());
        for (int c = 0; c < 2; ++c) out.copyFrom (c, pos, buf, c, 0, n);
    }
    return out;
}

static std::vector<Ev> phrase()
{
    // a lead line with overlaps (legato slides) and a held chord at the end
    std::vector<Ev> v;
    const int line[] = { 60, 63, 67, 70, 72, 70, 67, 65 };
    double t = 0.05;
    for (int i = 0; i < 8; ++i) { v.push_back ({ t, line[i], true, 0.85f }); v.push_back ({ t + 0.27, line[i], false, 0 }); t += 0.25; }
    for (int n : { 60, 63, 67 }) v.push_back ({ 2.2, n, true, 0.8f });
    for (int n : { 60, 63, 67 }) v.push_back ({ 3.4, n, false, 0 });
    std::sort (v.begin(), v.end(), [] (auto& a, auto& b) { return a.t < b.t || (a.t == b.t && ! a.on && b.on); });
    return v;
}

static void stats (const juce::AudioBuffer<float>& b, float& peak, float& rmsDb, int& nans)
{
    peak = 0; nans = 0; double acc = 0; int cnt = 0;
    for (int c = 0; c < b.getNumChannels(); ++c)
        for (int i = 0; i < b.getNumSamples(); ++i)
        {
            const float x = b.getSample (c, i);
            if (! std::isfinite (x)) { ++nans; continue; }
            peak = juce::jmax (peak, std::abs (x)); acc += (double) x * x; ++cnt;
        }
    rmsDb = (float) (10.0 * std::log10 (acc / juce::jmax (1, cnt) + 1e-12));
}

int main (int argc, char** argv)
{
    juce::ScopedJuceInitialiser_GUI init;
    const juce::File outDir (argc > 1 ? argv[1] : "/tmp/mltest");
    outDir.createDirectory();
    const double sr = 48000.0;

    MisterLeadsProcessor p;
    p.setPlayConfigDetails (0, 2, sr, 512);
    p.prepareToPlay (sr, 512);

    printf ("Presets (%d)\n", (int) mld::presets().size());
    juce::String table;
    int bad = 0;
    std::map<juce::String, int> perCat;
    for (int i = 0; i < (int) mld::presets().size(); ++i)
    {
        p.loadPreset (i);
        p.prepareToPlay (sr, 512);
        auto a = run (p, phrase(), 4.6, sr);
        float pk, rms; int nans; stats (a, pk, rms, nans);
        const auto& pr = mld::presets()[(size_t) i];
        const bool ok = nans == 0 && pk < 1.0f && rms > -36.0f && rms < -8.0f;
        if (! ok) ++bad;
        perCat[pr.category]++;
        table << juce::String (i).paddedLeft ('0', 2) << " " << juce::String (pr.name).paddedRight (' ', 22) << " peak " << juce::String (pk, 3)
              << " rms " << juce::String (rms, 1) << " dB" << (nans ? " NAN" : "") << (ok ? "" : "  <-- out of range") << "\n";
    }
    outDir.getChildFile ("preset_levels.txt").replaceWithText (table);
    printf ("%s", table.toRawUTF8());
    check (bad == 0, "every preset renders clean (no NaN, no clipping, sane level)", juce::String (bad) + " bad");
    check (mld::presets().size() >= 55, "preset count", juce::String ((int) mld::presets().size()));
    juce::String cats; for (auto& kv : perCat) cats << kv.first << " " << kv.second << ", ";
    printf ("  categories: %s\n", cats.toRawUTF8());

    // ---- voice modes
    printf ("\nVoices\n");
    {
        p.loadPreset (0);
        auto setChoice = [&p] (const char* id, int idx) { auto* q = p.apvts.getParameter (id); q->setValueNotifyingHost (q->convertTo0to1 ((float) idx)); };
        setChoice ("voice_mode", tsyn::Poly); p.prepareToPlay (sr, 512);
        std::vector<Ev> ten; for (int k = 0; k < 10; ++k) ten.push_back ({ 0.01 + k * 0.01, 48 + k * 3, true, 0.8f });
        int mv = 0; run (p, ten, 0.6, sr, 512, &mv);
        check (mv == tsyn::kMaxVoices, "poly: 10 held notes -> 8 voices (stealing works)", juce::String (mv));

        setChoice ("voice_mode", tsyn::Legato); p.prepareToPlay (sr, 512);
        mv = 0; auto a = run (p, phrase(), 4.6, sr, 512, &mv);
        check (mv == 1, "legato: one voice for an overlapping line", juce::String (mv));

        setChoice ("voice_mode", tsyn::Mono); p.prepareToPlay (sr, 512);
        mv = 0; run (p, phrase(), 4.6, sr, 512, &mv);
        check (mv == 1, "mono: one voice", juce::String (mv));

        // legato note priority: hold C, press E, release E -> back to C (pitch)
        setChoice ("voice_mode", tsyn::Legato);
        auto* g = p.apvts.getParameter ("glide"); g->setValueNotifyingHost (g->convertTo0to1 (0.0f));
        p.prepareToPlay (sr, 512);
        run (p, { { 0.01, 60, true, 0.8f }, { 0.3, 64, true, 0.8f }, { 0.6, 64, false, 0 } }, 0.9, sr);
        check (p.engine.monoNote() == 60, "legato: releasing the top note falls back to the held one", "note " + juce::String (p.engine.monoNote()));
    }

    // ---- sample rates + block sizes
    printf ("\nRobustness\n");
    for (double rate : { 44100.0, 48000.0, 96000.0 })
        for (int blk : { 32, 441, 2048 })
        {
            p.loadPreset (1); p.prepareToPlay (rate, blk);
            auto a = run (p, phrase(), 4.6, rate, blk);
            float pk, rms; int nans; stats (a, pk, rms, nans);
            if (nans || pk >= 1.0f) check (false, "sr " + juce::String (rate) + " block " + juce::String (blk), juce::String (pk));
        }
    check (true, "44.1/48/96 kHz x block 32/441/2048 render clean");

    // ---- CPU: 8-note chord on the heaviest preset
    {
        int heavy = 1;   // Uplifting Anthem: 7 + 3 unison
        p.loadPreset (heavy); p.prepareToPlay (sr, 512);
        std::vector<Ev> chord; for (int k = 0; k < 8; ++k) chord.push_back ({ 0.0, 48 + k * 4, true, 0.8f });
        const auto t0 = std::chrono::steady_clock::now();
        run (p, chord, 10.0, sr);
        const double secs = std::chrono::duration<double> (std::chrono::steady_clock::now() - t0).count();
        check (secs < 10.0 * 0.35, "CPU: 8 supersaw voices, 10 s of audio", juce::String (secs * 100.0 / 10.0, 1) + "% of one core");
    }

    // ---- state round trip
    {
        p.loadPreset (20);
        juce::MemoryBlock mb; p.getStateInformation (mb);
        MisterLeadsProcessor q; q.setStateInformation (mb.getData(), (int) mb.getSize());
        int diff = 0;
        for (auto* prm : p.getParameters())
            if (auto* rp = dynamic_cast<juce::RangedAudioParameter*> (prm))
                if (std::abs (rp->getValue() - q.apvts.getParameter (rp->getParameterID())->getValue()) > 1e-5f) ++diff;
        check (diff == 0 && q.getCurrentPreset() == 20, "state save / restore", juce::String (diff) + " differences");
    }

    // ---- editor snapshot
    {
        p.loadPreset (0);
        std::unique_ptr<juce::AudioProcessorEditor> ed (p.createEditor());
        ed->setBounds (0, 0, ed->getWidth(), ed->getHeight());
        auto img = ed->createComponentSnapshot (ed->getLocalBounds(), true, 1.0f);
        juce::File f = outDir.getChildFile ("ui.png"); f.deleteFile();
        juce::FileOutputStream os (f); juce::PNGImageFormat().writeImageToStream (img, os);
        check (img.isValid() && ed->getWidth() == 1100, "editor opens and draws", f.getFullPathName());
    }

    printf ("\n%s  (%d failures)\n", failures == 0 ? "ALL TESTS PASSED" : "TESTS FAILED", failures);
    return failures == 0 ? 0 : 1;
}
