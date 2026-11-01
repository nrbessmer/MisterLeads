# Mister Leads

Lead synthesizer by **Tully EDM Vibe** — AU, VST3 and standalone app for macOS 12+ (Apple Silicon and Intel).

- 2 oscillators × up to 7 unison voices: Saw, Square, Pulse, Triangle, Sine, SuperSaw, FM, Fold — plus sub and noise
- Poly (8 voices), Mono and Legato modes with glide, pitch bend and mod-wheel vibrato
- Filter: 24 dB ladder, 12 dB low-pass, band-pass, high-pass, with drive, envelope, key tracking and LFO
- LFO with 5 shapes, tempo sync and fade-in delay (vibrato that arrives late, like a singer)
- FX: drive (Soft/Hard/Fold/Crush), chorus, ping-pong delay, reverb, stereo width
- 61 presets: Trance, Psy & Acid, EDM, FM & Bells, Plucks, Vintage Mono, Synthwave & Chip, Hard — all level-matched
- Tooltips on every control, on-screen keyboard, scope

## Build
    cmake -S . -B build-release -G Xcode -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"
    cmake --build build-release --config Release
JUCE 8.0.7 is expected at `../JUCE` (or pass `-DJUCE_PATH=...`).

## Self-test
    cmake -S . -B build-test -DML_TESTS=ON && cmake --build build-test --config Release --target MLTest
Renders every preset (no NaN, no clipping, level-matched), checks poly/mono/legato voice handling, stealing,
44.1/48/96 kHz at several block sizes, CPU, state save/restore and the editor.

(c)(p) 2026 Tully EDM Vibe — info@tullyedmvibe.com — www.tullyedmvibe.com
