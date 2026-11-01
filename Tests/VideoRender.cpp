// MLVideo: renders the Mister Leads demo offline with the real processor + editor.
// Lead lines play through six presets over a quiet drum bed; captions name each sound.
// Usage: MLVideo bed.wav outDir [scale] -> outDir/f%05d.png + audio.wav + captions.txt
#include <juce_audio_utils/juce_audio_utils.h>
#include "../Source/PluginProcessor.h"
#include "../Source/PluginEditor.h"
#include <cstdio>

struct Host : juce::AudioPlayHead
{
    double bpm = 128.0, ppq = 0.0;
    juce::Optional<PositionInfo> getPosition() const override
    { PositionInfo p; p.setBpm (bpm); p.setPpqPosition (ppq); p.setIsPlaying (true); return p; }
};
struct N { double beat, len; int note; float vel; };

int main (int argc, char** argv)
{
    juce::ScopedJuceInitialiser_GUI init;
    const double SR = 48000.0; const int FPS = 30, spf = 1600, B = 400;
    const juce::File bedFile (argv[1]), outDir (argv[2]);
    const float scale = argc > 3 ? (float) atof (argv[3]) : 1.0f;
    outDir.createDirectory();

    juce::AudioFormatManager fm; fm.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> rd (fm.createReaderFor (bedFile));
    juce::AudioBuffer<float> bed (2, (int) rd->lengthInSamples);
    rd->read (&bed, 0, (int) rd->lengthInSamples, 0, true, true);

    MisterLeadsProcessor proc;
    Host host; proc.setPlayHead (&host);
    proc.setPlayConfigDetails (0, 2, SR, B);
    proc.prepareToPlay (SR, B);
    std::unique_ptr<juce::AudioProcessorEditor> ed (proc.createEditor());
    auto* e = static_cast<MisterLeadsEditor*> (ed.get());
    auto preset = [&] (const char* name)
    {
        const auto& all = mld::presets();
        for (size_t i = 0; i < all.size(); ++i)
            if (juce::String (all[i].name) == name) { e->presetBar.box.setSelectedId ((int) i + 1, juce::sendNotificationSync); return; }
        printf ("missing preset %s\n", name);
    };

    // A minor phrases, 128 BPM. Each segment = 4 bars (16 beats).
    const std::vector<N> trance = { {0,1.5,69,.9f},{1.5,.5,72,.8f},{2,1,76,.9f},{3,.5,74,.8f},{3.5,.5,72,.8f},{4,1.5,71,.9f},{5.5,.5,67,.8f},{6,2,69,.9f},
                                    {8,1.5,69,.9f},{9.5,.5,72,.8f},{10,1,76,.9f},{11,.5,79,.8f},{11.5,.5,77,.8f},{12,2,76,.9f},{14,1,74,.8f},{15,1,72,.8f} };
    std::vector<N> psy; for (int i = 0; i < 32; ++i) { const int pat[8] = { 54, 54, 66, 54, 57, 54, 61, 54 }; psy.push_back ({ i * 0.5, 0.4, pat[i % 8] + (i >= 16 && i % 8 == 6 ? 12 : 0), i % 4 == 0 ? 1.0f : 0.75f }); }
    std::vector<N> acid; { const int pat[16] = { 45, 45, 57, 45, 48, 45, 55, 57, 45, 45, 57, 60, 45, 52, 55, 57 }; const bool slide[16] = { 0,0,1,0,0,0,1,0, 0,0,1,1,0,0,1,0 };
                           for (int i = 0; i < 32; ++i) acid.push_back ({ i * 0.5, slide[i % 16] ? 0.6 : 0.3, pat[i % 16], (i % 4 == 0) ? 1.0f : 0.7f }); }
    const std::vector<N> mini = { {0,2,69,.85f},{2,1,72,.8f},{3,1,74,.8f},{4,3,76,.9f},{7,1,74,.8f},{8,2,72,.85f},{10,1,71,.8f},{11,1,67,.8f},{12,4,69,.9f} };
    std::vector<N> dx = { {0,1,81,.8f},{1,1,79,.7f},{2,1,76,.8f},{3,1,72,.7f},{4,2,74,.8f},{6,2,76,.7f},{8,1,81,.8f},{9,1,84,.7f},{10,1,83,.8f},{11,1,79,.7f},{12,4,81,.8f} };
    std::vector<N> big; { const int roots[4] = { 57, 53, 48, 55 }; const int third[4] = { 3, 4, 4, 4 };
                          for (int b = 0; b < 4; ++b) for (int h : { 0, 3, 6, 8, 10 }) { const double t = b * 4 + h * 0.5 * (h < 8 ? 1 : 1);
                              for (int iv : { 0, third[b], 7, 12 }) big.push_back ({ t, 0.45, roots[b] + 12 + iv, .9f }); } }

    struct Seg { const char* preset; const std::vector<N>* line; const char* cap; };
    const Seg segs[] = {
        { "Trance Supersaw", &trance, "Trance Supersaw  -  14 detuned saws, dotted delay, big hall" },
        { "Psy Screamer",    &psy,    "Psy Screamer  -  driven resonant mono lead" },
        { "Acid 303",        &acid,   "Acid 303  -  squelchy saw with legato slides" },
        { "Mini Lead",       &mini,   "Mini Lead  -  fat vintage mono, ladder drive, late vibrato" },
        { "DX Lead",         &dx,     "DX Lead  -  80s FM with delayed vibrato" },
        { "Big Room Lead",   &big,    "Big Room Lead  -  festival chords" } };
    const int nSeg = 6;
    const double beatSec = 60.0 / 128.0, segBeats = 16.0;
    const double tEnd = nSeg * segBeats * beatSec + 1.5;
    const int nFrames = (int) (tEnd * FPS);

    // all note events in seconds
    struct Ev { double t; int note; bool on; float vel; };
    std::vector<Ev> evs;
    for (int s = 0; s < nSeg; ++s)
        for (auto& n : *segs[s].line)
        {
            const double t0 = (s * segBeats + n.beat) * beatSec;
            evs.push_back ({ t0, n.note, true, n.vel });
            evs.push_back ({ t0 + n.len * beatSec, n.note, false, 0 });
        }
    std::stable_sort (evs.begin(), evs.end(), [] (auto& a, auto& b) { return a.t < b.t || (a.t == b.t && ! a.on && b.on); });

    juce::AudioBuffer<float> out (2, nFrames * spf); out.clear();
    juce::AudioBuffer<float> blk (2, B);
    juce::String caps;
    int cur = -1; size_t ei = 0;
    for (int fr = 0; fr < nFrames; ++fr)
    {
        const double t = (double) fr / FPS;
        const int seg = juce::jmin (nSeg - 1, (int) (t / (segBeats * beatSec)));
        if (seg != cur)
        {
            cur = seg; preset (segs[seg].preset);
            const double s0 = seg * segBeats * beatSec;
            caps << juce::String (s0, 3) << "\t" << juce::String (juce::jmin (tEnd, s0 + segBeats * beatSec), 3) << "\t" << segs[seg].cap << "\n";
        }
        for (int k = 0; k < spf; k += B)
        {
            const int s0 = fr * spf + k;
            juce::MidiBuffer mb;
            while (ei < evs.size() && (int) (evs[ei].t * SR) < s0 + B)
            {
                const auto& ev = evs[ei];
                mb.addEvent (ev.on ? juce::MidiMessage::noteOn (1, ev.note, ev.vel) : juce::MidiMessage::noteOff (1, ev.note), juce::jmax (0, (int) (ev.t * SR) - s0));
                ++ei;
            }
            blk.clear();
            proc.processBlock (blk, mb);
            host.ppq += B / SR * 128.0 / 60.0;
            for (int c = 0; c < 2; ++c)
            {
                out.addFrom (c, s0, blk, c, 0, B);
                if (s0 + B <= bed.getNumSamples()) out.addFrom (c, s0, bed, c, s0, B, 0.32f);
            }
        }
        e->timerCallback();
        auto img = ed->createComponentSnapshot (ed->getLocalBounds(), true, scale);
        juce::File f = outDir.getChildFile (juce::String::formatted ("f%05d.png", fr)); f.deleteFile();
        juce::FileOutputStream fos (f); juce::PNGImageFormat().writeImageToStream (img, fos);
    }
    outDir.getChildFile ("captions.txt").replaceWithText (caps);
    juce::WavAudioFormat wav; auto wf = outDir.getChildFile ("audio.wav"); wf.deleteFile();
    std::unique_ptr<juce::AudioFormatWriter> w (wav.createWriterFor (new juce::FileOutputStream (wf), SR, 2, 24, {}, 0));
    out.applyGain (0.89f / juce::jmax (0.05f, out.getMagnitude (0, out.getNumSamples())));
    w->writeFromAudioSampleBuffer (out, 0, out.getNumSamples());
    printf ("frames %d, %.1f s\n", nFrames, tEnd);
    proc.setPlayHead (nullptr);
    return 0;
}
