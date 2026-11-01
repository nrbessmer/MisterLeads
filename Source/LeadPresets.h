/*
  ==============================================================================
    Mister Leads - LeadPresets.h
    (c)(p) 2026 Tully EDM Vibe

    Each preset lists only what differs from the defaults (see SynthParams.h).
    Times in seconds, cutoff in Hz, volume in dB.
  ==============================================================================
*/
#pragma once
#include "SynthParams.h"

namespace mld
{
    inline const std::vector<tsyn::Preset>& presets()
    {
        static const std::vector<tsyn::Preset> p = {
        // ------------------------------------------------------------------ TRANCE
        { "Trance Supersaw", "Trance", "The classic: 14 detuned saws, airy delay and a big hall.",
          "osc1_wave=SuperSaw osc1_shape=0.6 osc1_detune=0.45 osc2_wave=SuperSaw osc2_oct=1 osc2_level=0.35 osc2_detune=0.35 cutoff=9000 reso=0.15 flt_env=0.15 amp_a=0.004 amp_r=0.35 spread=0.9 chorus=0.2 delay=0.22 delay_time=1/8D delay_fb=0.4 reverb=0.3 reverb_size=0.75 width=1.25 volume=-6.9" },
        { "Uplifting Anthem", "Trance", "Supersaw with an octave saw on top. Made for the drop after the breakdown.",
          "osc1_wave=SuperSaw osc1_shape=0.7 osc1_detune=0.5 osc2_wave=Saw osc2_oct=1 osc2_fine=6 osc2_level=0.35 osc2_unison=3 osc2_detune=0.25 cutoff=11000 flt_env=0.1 amp_r=0.45 spread=1 delay=0.3 delay_time=1/8D delay_fb=0.45 reverb=0.42 reverb_size=0.85 width=1.3 volume=-8.2" },
        { "Hands Up Lead", "Trance", "Bright supersaw with a square an octave up and a touch of drive.",
          "osc1_wave=SuperSaw osc1_shape=0.75 osc1_detune=0.55 osc2_wave=Square osc2_oct=1 osc2_level=0.25 cutoff=7000 reso=0.2 flt_env=0.2 drive_type=Soft drive=0.2 delay=0.25 delay_time=1/8 delay_fb=0.35 reverb=0.25 volume=-5.4" },
        { "Trance Pluck", "Trance", "Short supersaw pluck for rolling trance riffs.",
          "osc1_wave=SuperSaw osc1_detune=0.4 cutoff=800 reso=0.25 flt_env=0.6 flt_d=0.25 flt_s=0 amp_d=0.35 amp_s=0 amp_r=0.3 delay=0.35 delay_time=1/8D delay_fb=0.45 reverb=0.35 spread=0.9 volume=-0.4" },
        { "Euphoric Swell", "Trance", "Slow-attack supersaw lead that blooms into a pad.",
          "osc1_wave=SuperSaw osc1_detune=0.5 osc2_wave=SuperSaw osc2_oct=-1 osc2_level=0.4 amp_a=0.08 amp_r=1.2 cutoff=5000 flt_env=0.1 chorus=0.4 reverb=0.55 reverb_size=0.9 delay=0.15 width=1.3 volume=-7.6" },
        { "Gated Trance", "Trance", "Supersaw chopped in 16ths by the LFO. Hold a chord.",
          "osc1_wave=SuperSaw osc1_detune=0.45 cutoff=8000 lfo_shape=Square lfo_sync=1/16 lfo_amp=0.9 reverb=0.3 delay=0.15 delay_time=1/8D volume=-2.9" },
        { "Detroit Saw Fifths", "Trance", "Saw stack in fifths: one key plays a power chord.",
          "osc1_wave=Saw osc1_unison=5 osc1_detune=0.35 osc2_wave=Saw osc2_semi=7 osc2_level=0.5 osc2_unison=3 osc2_detune=0.3 cutoff=3500 reso=0.25 flt_env=0.3 flt_d=0.5 reverb=0.3 delay=0.2 volume=-6.9" },
        { "Classic JP Lead", "Trance", "90s rack supersaw with chorus and a gentle filter sweep.",
          "osc1_wave=SuperSaw osc1_shape=0.45 osc1_detune=0.4 cutoff=4500 reso=0.25 flt_env=0.35 flt_d=0.5 flt_s=0.4 chorus=0.35 reverb=0.3 delay=0.2 delay_time=1/4D volume=-4.6" },

        // ------------------------------------------------------------------ PSY & ACID
        { "Psy Screamer", "Psy & Acid", "Resonant, driven mono lead for full-on psytrance.",
          "voice_mode=Mono glide=0.04 osc1_wave=Saw osc1_unison=3 osc1_detune=0.2 osc2_wave=Square osc2_oct=1 osc2_level=0.4 cutoff=1200 reso=0.55 flt_env=0.55 flt_d=0.18 flt_s=0.15 drive_type=Hard drive=0.35 delay=0.25 delay_time=1/16D delay_fb=0.45 volume=-1.5" },
        { "Acid 303", "Psy & Acid", "Squelchy saw with slides: play overlapping notes to glide.",
          "voice_mode=Legato glide=0.06 osc1_wave=Saw osc1_level=0.9 cutoff=450 reso=0.8 flt_env=0.7 flt_d=0.2 flt_s=0 flt_key=0.3 amp_d=0.3 amp_s=0.7 drive_type=Soft drive=0.4 delay=0.15 delay_time=1/16D volume=2.5" },
        { "Acid Square", "Psy & Acid", "The square-wave 303 sound: hollow and rubbery.",
          "voice_mode=Legato glide=0.06 osc1_wave=Square osc1_level=0.9 cutoff=400 reso=0.82 flt_env=0.75 flt_d=0.22 flt_s=0 flt_key=0.3 drive_type=Soft drive=0.45 delay=0.12 delay_time=1/16D volume=1.4" },
        { "Goa Lead", "Psy & Acid", "Saw and moving pulse with a slow PWM sweep.",
          "voice_mode=Mono glide=0.03 osc1_wave=Saw osc2_wave=Pulse osc2_shape=0.3 osc2_level=0.6 lfo_rate=0.5 lfo_shapemod=0.4 cutoff=2000 reso=0.4 flt_env=0.4 flt_d=0.3 delay=0.3 delay_time=1/8D reverb=0.2 volume=-4.3" },
        { "Full-On Zap", "Psy & Acid", "FM zap with a fast filter snap for psy riffs.",
          "osc1_wave=FM osc1_shape=0.6 fm_ratio=3:1 cutoff=600 reso=0.5 flt_env=0.8 flt_d=0.12 flt_s=0 amp_d=0.15 amp_s=0.2 delay=0.3 delay_time=1/16D delay_fb=0.4 volume=6.0" },
        { "Dark Psy Twister", "Psy & Acid", "Folded wave modulated by random 16th steps.",
          "voice_mode=Mono osc1_wave=Fold osc1_shape=0.7 lfo_shape=S&H lfo_sync=1/16 lfo_shapemod=0.6 cutoff=1800 reso=0.6 flt_env=0.3 drive_type=Hard drive=0.4 delay=0.2 delay_time=1/16 volume=-3.0" },
        { "Squelch Lead", "Psy & Acid", "Legato saw with an 8th-note filter wobble.",
          "voice_mode=Legato glide=0.08 osc1_wave=Saw osc1_unison=2 osc1_detune=0.1 cutoff=700 reso=0.7 flt_env=0.4 lfo_shape=Triangle lfo_sync=1/8 lfo_cutoff=0.25 drive_type=Soft drive=0.3 volume=2.5" },
        { "Rubber Acid", "Psy & Acid", "Deep, bouncing acid square with long slides.",
          "voice_mode=Legato glide=0.1 osc1_wave=Square cutoff=350 reso=0.85 flt_env=0.8 flt_d=0.3 flt_s=0 drive_type=Soft drive=0.3 volume=3.4" },
        { "Psy Arp Lead", "Psy & Acid", "Tight saw blip with a 16th delay for fast riffs.",
          "osc1_wave=Saw cutoff=1500 reso=0.35 flt_env=0.5 flt_d=0.1 flt_s=0 amp_d=0.12 amp_s=0 amp_r=0.08 delay=0.35 delay_time=1/16 delay_fb=0.5 volume=6.0" },
        { "Hypnotic FM", "Psy & Acid", "Hollow FM line, tempo-synced filter movement.",
          "voice_mode=Mono osc1_wave=FM osc1_shape=0.4 fm_ratio=2:1 cutoff=2200 reso=0.45 lfo_shape=Triangle lfo_sync=1/4 lfo_cutoff=0.3 delay=0.25 delay_time=1/8D volume=2.7" },

        // ------------------------------------------------------------------ EDM
        { "Big Room Lead", "EDM", "Massive supersaw with a saw an octave down. Festival drop.",
          "osc1_wave=SuperSaw osc1_detune=0.6 osc1_shape=0.7 osc2_wave=Saw osc2_oct=-1 osc2_level=0.5 osc2_unison=3 osc2_detune=0.3 cutoff=8000 drive_type=Soft drive=0.3 reverb=0.4 reverb_size=0.8 width=1.3 volume=-6.8" },
        { "Future Bass Saw", "EDM", "Supersaw with a built-in sidechain pump. Hold chords.",
          "osc1_wave=SuperSaw osc1_detune=0.45 cutoff=6000 lfo_shape=Saw lfo_sync=1/4 lfo_amp=0.55 chorus=0.3 glide=0.05 reverb=0.3 width=1.3 volume=-2.7" },
        { "Festival Stab", "EDM", "Short, wide, driven chord stab.",
          "osc1_wave=SuperSaw osc1_detune=0.55 amp_d=0.35 amp_s=0.2 amp_r=0.2 cutoff=10000 drive_type=Hard drive=0.2 reverb=0.4 volume=-1.3" },
        { "Electro Square", "EDM", "Fat unison squares, mono with a quick glide.",
          "voice_mode=Mono glide=0.03 osc1_wave=Square osc1_unison=3 osc1_detune=0.25 osc2_wave=Square osc2_oct=1 osc2_level=0.3 cutoff=3000 reso=0.3 flt_env=0.3 drive_type=Soft drive=0.35 volume=-1.4" },
        { "Bounce Lead", "EDM", "Plucky pulse lead for Melbourne bounce style riffs.",
          "osc1_wave=Pulse osc1_shape=0.25 cutoff=2500 reso=0.3 flt_env=0.5 flt_d=0.1 flt_s=0.1 amp_d=0.2 amp_s=0.3 drive_type=Hard drive=0.25 volume=3.7" },
        { "Dutch Screech", "EDM", "Band-pass screech with fast vibrato and hard drive.",
          "osc1_wave=Saw osc1_unison=5 osc1_detune=0.7 osc2_wave=Saw osc2_semi=7 osc2_level=0.4 flt_type=Band cutoff=2000 reso=0.5 flt_env=0.2 lfo_rate=7 lfo_pitch=0.3 drive_type=Hard drive=0.5 reverb=0.25 volume=-4.2" },
        { "Tropical Pluck", "EDM", "Soft marimba-like pluck for tropical house hooks.",
          "osc1_wave=Sine osc2_wave=Triangle osc2_oct=1 osc2_level=0.4 cutoff=6000 flt_env=0 amp_d=0.3 amp_s=0 amp_r=0.25 reverb=0.35 delay=0.25 delay_time=1/8D volume=-1.6" },
        { "Progressive Lead", "EDM", "Saw and pulse with a long filter sweep and dotted delay.",
          "osc1_wave=Saw osc1_unison=3 osc1_detune=0.3 osc2_wave=Pulse osc2_shape=0.35 osc2_level=0.5 cutoff=2500 reso=0.3 flt_env=0.3 flt_d=0.6 flt_s=0.4 chorus=0.2 delay=0.3 delay_time=1/4D reverb=0.35 volume=-6.2" },

        // ------------------------------------------------------------------ FM & BELLS
        { "FM Bell", "FM & Bells", "Glassy bell with a long ring.",
          "osc1_wave=FM osc1_shape=0.35 fm_ratio=7:1 cutoff=12000 flt_env=0 amp_a=0.002 amp_d=1.5 amp_s=0 amp_r=1.2 reverb=0.4 delay=0.2 volume=-8.1" },
        { "DX Lead", "FM & Bells", "80s FM lead with delayed vibrato. Play legato.",
          "voice_mode=Legato glide=0.04 osc1_wave=FM osc1_shape=0.45 fm_ratio=1:1 osc2_wave=Saw osc2_level=0.2 cutoff=8000 flt_env=0 lfo_rate=5.5 lfo_pitch=0.25 lfo_delay=0.4 reverb=0.25 delay=0.2 volume=-6.9" },
        { "Glass Keys", "FM & Bells", "Bright FM keys layered with a sine.",
          "osc1_wave=FM osc1_shape=0.3 fm_ratio=4:1 osc2_wave=Sine osc2_level=0.5 cutoff=12000 flt_env=0 amp_d=1.2 amp_s=0.2 amp_r=0.6 chorus=0.3 reverb=0.45 volume=-4.6" },
        { "Metallic Lead", "FM & Bells", "Wavefolded tone with an FM edge.",
          "osc1_wave=Fold osc1_shape=0.6 osc2_wave=FM osc2_shape=0.5 osc2_level=0.4 fm_ratio=5:1 cutoff=7000 flt_env=0.1 drive_type=Fold drive=0.2 reverb=0.2 volume=-7.0" },
        { "E-Piano Lead", "FM & Bells", "Soft FM electric piano with tremolo.",
          "osc1_wave=FM osc1_shape=0.25 fm_ratio=1:1 cutoff=9000 flt_env=0 amp_d=1.5 amp_s=0.3 amp_r=0.5 lfo_rate=4.5 lfo_amp=0.2 chorus=0.4 reverb=0.25 volume=-3.7" },
        { "FM Brass", "FM & Bells", "Punchy FM brass that opens on the attack.",
          "osc1_wave=FM osc1_shape=0.5 fm_ratio=1:1 osc2_wave=Saw osc2_level=0.3 amp_a=0.04 flt_a=0.05 flt_env=0.4 cutoff=1800 reso=0.15 reverb=0.25 volume=-8.0" },
        { "Digital Pluck", "FM & Bells", "Sharp FM pluck for arps and hooks.",
          "osc1_wave=FM osc1_shape=0.6 fm_ratio=2:1 cutoff=1500 flt_env=0.5 flt_d=0.15 flt_s=0 amp_d=0.2 amp_s=0 amp_r=0.2 delay=0.25 delay_time=1/8D reverb=0.25 volume=1.2" },
        { "Kalimba", "FM & Bells", "Thumb-piano FM pluck.",
          "osc1_wave=FM osc1_shape=0.2 fm_ratio=5:1 osc2_wave=Sine osc2_level=0.5 cutoff=9000 flt_env=0 amp_d=0.5 amp_s=0 amp_r=0.4 reverb=0.3 volume=-4.2" },

        // ------------------------------------------------------------------ PLUCKS
        { "Saw Pluck", "Plucks", "Classic house and trance pluck.",
          "osc1_wave=Saw osc1_unison=3 osc1_detune=0.2 cutoff=600 reso=0.2 flt_env=0.65 flt_d=0.18 flt_s=0 amp_d=0.35 amp_s=0 amp_r=0.25 reverb=0.3 delay=0.25 delay_time=1/8D volume=0.7" },
        { "Square Pluck", "Plucks", "Woody square pluck.",
          "osc1_wave=Square cutoff=700 reso=0.2 flt_env=0.6 flt_d=0.15 flt_s=0 amp_d=0.3 amp_s=0 amp_r=0.2 reverb=0.25 delay=0.2 volume=-3.2" },
        { "Supersaw Pluck", "Plucks", "Wide supersaw pluck for melodic house.",
          "osc1_wave=SuperSaw osc1_detune=0.4 cutoff=900 flt_env=0.6 flt_d=0.2 flt_s=0 amp_d=0.4 amp_s=0 amp_r=0.3 reverb=0.35 delay=0.25 delay_time=1/8D width=1.3 volume=0.0" },
        { "Harp Pluck", "Plucks", "Soft triangle pluck with a long tail.",
          "osc1_wave=Triangle osc2_wave=Saw osc2_oct=-1 osc2_level=0.2 cutoff=3000 flt_env=0.3 flt_d=0.4 flt_s=0 amp_d=0.8 amp_s=0 amp_r=0.6 reverb=0.45 volume=-4.1" },
        { "Chip Pluck", "Plucks", "Crunchy 8-bit pulse blip.",
          "osc1_wave=Pulse osc1_shape=0.25 cutoff=20000 flt_type=LP_12 flt_env=0 amp_d=0.15 amp_s=0 amp_r=0.05 drive_type=Crush drive=0.3 volume=6.0" },
        { "Bell Pluck", "Plucks", "Sine and FM chime, short and clean.",
          "osc1_wave=Sine osc2_wave=FM osc2_shape=0.3 osc2_level=0.4 fm_ratio=4:1 cutoff=10000 flt_env=0 amp_d=0.4 amp_s=0 amp_r=0.4 reverb=0.35 delay=0.2 delay_time=1/8D volume=-2.9" },
        { "Deep House Pluck", "Plucks", "Dark, round pluck with a little resonance.",
          "osc1_wave=Saw osc2_wave=Square osc2_oct=-1 osc2_level=0.4 cutoff=400 reso=0.35 flt_env=0.5 flt_d=0.25 flt_s=0 amp_d=0.45 amp_s=0 amp_r=0.3 chorus=0.25 reverb=0.3 volume=-0.3" },

        // ------------------------------------------------------------------ VINTAGE MONO
        { "Mini Lead", "Vintage Mono", "Fat two-saw mono lead with ladder drive and late vibrato.",
          "voice_mode=Legato glide=0.08 osc1_wave=Saw osc2_wave=Saw osc2_fine=8 osc2_level=0.7 sub_level=0.3 cutoff=1800 reso=0.35 flt_env=0.45 flt_d=0.6 flt_s=0.4 flt_key=0.6 flt_drive=0.35 lfo_rate=5.5 lfo_pitch=0.2 lfo_delay=0.5 volume=1.7" },
        { "70s Prog Lead", "Vintage Mono", "Saw and square in octaves, singing vibrato, slow glide.",
          "voice_mode=Legato glide=0.1 osc1_wave=Saw osc2_wave=Square osc2_oct=1 osc2_level=0.4 cutoff=2500 reso=0.45 flt_env=0.3 flt_d=0.8 flt_s=0.5 lfo_rate=5.2 lfo_pitch=0.25 lfo_delay=0.6 delay=0.2 reverb=0.25 volume=-3.5" },
        { "G-Funk Whine", "Vintage Mono", "Triangle lead with long portamento and wide vibrato.",
          "voice_mode=Legato glide=0.15 osc1_wave=Triangle osc2_wave=Sine osc2_oct=1 osc2_level=0.3 cutoff=4000 flt_env=0 lfo_rate=5.5 lfo_pitch=0.45 lfo_delay=0.25 reverb=0.2 volume=-3.4" },
        { "Whistle Lead", "Vintage Mono", "Pure sine with breath noise and expressive vibrato.",
          "voice_mode=Legato glide=0.12 osc1_wave=Sine noise=0.05 cutoff=6000 flt_env=0 lfo_rate=5.8 lfo_pitch=0.35 lfo_delay=0.35 reverb=0.3 delay=0.2 delay_time=1/4D volume=-4.5" },
        { "Analog Fat Lead", "Vintage Mono", "Three saws, sub and a driven ladder.",
          "voice_mode=Mono glide=0.04 osc1_wave=Saw osc1_unison=3 osc1_detune=0.15 osc2_wave=Saw osc2_oct=-1 osc2_level=0.6 sub_level=0.3 cutoff=1400 reso=0.3 flt_env=0.35 flt_d=0.4 flt_s=0.5 flt_drive=0.5 volume=1.7" },
        { "Brass Mono", "Vintage Mono", "Two saws with a slow filter attack: analog brass.",
          "voice_mode=Mono osc1_wave=Saw osc1_fine=-5 osc2_wave=Saw osc2_fine=5 osc2_level=0.8 amp_a=0.02 flt_a=0.06 flt_d=0.4 flt_s=0.5 flt_env=0.5 cutoff=700 reso=0.15 reverb=0.2 volume=-4.7" },
        { "Funky Square Mono", "Vintage Mono", "Snappy square with a quick filter blip.",
          "voice_mode=Mono glide=0.02 osc1_wave=Square cutoff=900 reso=0.4 flt_env=0.5 flt_d=0.25 flt_s=0.2 volume=-0.6" },
        { "Thin Pulse Lead", "Vintage Mono", "Narrow pulse with slow PWM and chorus.",
          "voice_mode=Mono osc1_wave=Pulse osc1_shape=0.1 lfo_rate=0.7 lfo_shapemod=0.25 flt_type=LP_12 cutoff=3000 reso=0.2 chorus=0.3 reverb=0.2 volume=-1.5" },
        { "Odyssey Squeal", "Vintage Mono", "Resonant 12 dB pulse lead with glide.",
          "voice_mode=Mono glide=0.06 osc1_wave=Pulse osc1_shape=0.2 flt_type=LP_12 cutoff=2200 reso=0.6 flt_env=0.3 lfo_rate=0.6 lfo_shapemod=0.3 reverb=0.2 volume=-4.2" },
        { "Sync-Style Sweep", "Vintage Mono", "FM sweep that sounds like hard sync.",
          "voice_mode=Mono glide=0.03 osc1_wave=FM osc1_shape=0.5 fm_ratio=2:1 flt_env=0.4 flt_d=0.5 cutoff=2500 lfo_rate=0.8 lfo_shapemod=0.5 drive_type=Soft drive=0.25 volume=0.2" },

        // ------------------------------------------------------------------ SYNTHWAVE & CHIP
        { "Synthwave Lead", "Synthwave & Chip", "Chorused saws, dotted delay, big neon hall.",
          "osc1_wave=Saw osc1_unison=3 osc1_detune=0.25 osc2_wave=Pulse osc2_level=0.5 cutoff=3500 flt_env=0.25 chorus=0.45 delay=0.35 delay_time=1/4D delay_fb=0.4 reverb=0.45 reverb_size=0.85 volume=-7.3" },
        { "Outrun Brass", "Synthwave & Chip", "Wide 80s brass with a filter swell.",
          "osc1_wave=Saw osc2_wave=Saw osc2_fine=9 osc2_level=0.8 amp_a=0.03 flt_a=0.08 flt_env=0.4 cutoff=1200 chorus=0.4 reverb=0.4 volume=-5.7" },
        { "80s Pluck Lead", "Synthwave & Chip", "Chorused pulse pluck straight out of 1984.",
          "osc1_wave=Pulse osc1_shape=0.35 cutoff=2500 flt_env=0.4 flt_d=0.3 amp_d=0.4 amp_s=0.3 chorus=0.5 delay=0.3 reverb=0.3 volume=-3.0" },
        { "Chiptune Square", "Synthwave & Chip", "Game-console square with vibrato.",
          "voice_mode=Mono osc1_wave=Square flt_type=LP_12 cutoff=20000 flt_env=0 amp_s=1 amp_r=0.02 drive_type=Crush drive=0.25 lfo_rate=7 lfo_pitch=0.3 lfo_delay=0.2 volume=-4.3" },
        { "Chip Arp Pulse", "Synthwave & Chip", "Thin crushed pulse for fast arpeggios.",
          "osc1_wave=Pulse osc1_shape=0.15 flt_type=LP_12 cutoff=20000 flt_env=0 amp_d=0.1 amp_s=0.5 amp_r=0.02 drive_type=Crush drive=0.35 volume=4.1" },
        { "Retro Game Lead", "Synthwave & Chip", "Triangle and square octave lead.",
          "voice_mode=Mono glide=0.02 osc1_wave=Triangle osc2_wave=Square osc2_oct=1 osc2_level=0.3 flt_type=LP_12 cutoff=12000 flt_env=0 lfo_rate=6 lfo_pitch=0.25 volume=0.0" },

        // ------------------------------------------------------------------ HARD
        { "Dubstep Growl Lead", "Hard", "FM growl wobbling in 8ths.",
          "voice_mode=Mono osc1_wave=FM osc1_shape=0.7 fm_ratio=1:1 lfo_shape=Triangle lfo_sync=1/8 lfo_shapemod=0.8 lfo_cutoff=0.5 cutoff=1200 reso=0.4 drive_type=Hard drive=0.5 sub_level=0.3 volume=-1.9" },
        { "Hardstyle Screech", "Hard", "Band-pass supersaw screech with fast vibrato.",
          "osc1_wave=Saw osc1_unison=7 osc1_detune=0.6 osc2_wave=Saw osc2_semi=12 osc2_level=0.4 flt_type=Band cutoff=1800 reso=0.6 lfo_rate=9 lfo_pitch=0.2 drive_type=Hard drive=0.6 reverb=0.3 volume=-4.4" },
        { "Reese Lead", "Hard", "Detuned saw pair for DnB leads.",
          "voice_mode=Mono osc1_wave=Saw osc1_unison=2 osc1_detune=0.25 osc2_wave=Saw osc2_fine=12 osc2_level=0.8 cutoff=1500 reso=0.2 flt_env=0.1 chorus=0.2 volume=1.8" },
        { "Distorted Saw", "Hard", "Simple saw lead through heavy soft-clip.",
          "voice_mode=Mono osc1_wave=Saw osc1_unison=3 osc1_detune=0.2 cutoff=5000 drive_type=Soft drive=0.7 reverb=0.2 volume=-5.8" },
        };
        return p;
    }
}
