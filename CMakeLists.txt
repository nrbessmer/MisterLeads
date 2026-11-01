cmake_minimum_required(VERSION 3.22)
project(MisterLeads VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "" FORCE)

# JUCE 8.0.7 - defaults to the shared copy next to this project (Projects/JUCE)
if(NOT DEFINED JUCE_PATH)
  set(JUCE_PATH "${CMAKE_SOURCE_DIR}/../JUCE" CACHE PATH "Path to JUCE")
endif()
if(NOT EXISTS "${JUCE_PATH}/CMakeLists.txt")
  message(FATAL_ERROR "JUCE not found at ${JUCE_PATH} (git clone https://github.com/juce-framework/JUCE.git --branch 8.0.7)")
endif()
add_subdirectory("${JUCE_PATH}" juce_build)

juce_add_plugin(MisterLeads
    COMPANY_NAME             "Tully EDM Vibe"
    COMPANY_COPYRIGHT        "(c)(p) 2026 Tully EDM Vibe"
    COMPANY_EMAIL            "info@tullyedmvibe.com"
    COMPANY_WEBSITE          "https://www.tullyedmvibe.com"
    BUNDLE_ID                com.TullyEDMVibe.MisterLeads
    PLUGIN_MANUFACTURER_CODE Tull
    PLUGIN_CODE              Mlds
    FORMATS                  AU VST3 Standalone
    PRODUCT_NAME             "Mister Leads"
    IS_SYNTH                 TRUE
    NEEDS_MIDI_INPUT         TRUE
    NEEDS_MIDI_OUTPUT        FALSE
    IS_MIDI_EFFECT           FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    VST3_CATEGORIES          "Instrument|Synth"
    AU_MAIN_TYPE             kAudioUnitType_MusicDevice
)

juce_add_binary_data(MisterLeadsData SOURCES Resources/TullyLogo.png)

target_sources(MisterLeads PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_compile_definitions(MisterLeads PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
)

target_link_libraries(MisterLeads
    PRIVATE
        MisterLeadsData
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# Optional self-test + demo-video renderer (cmake -DML_TESTS=ON)
option(ML_TESTS "Build the self-test and video console apps" OFF)
if(ML_TESTS)
  foreach(t MLTest MLVideo)
    juce_add_console_app(${t} PRODUCT_NAME "${t}")
    target_compile_definitions(${t} PRIVATE JucePlugin_Name="Mister Leads" JucePlugin_VersionString="1.0.0" JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)
    target_link_libraries(${t} PRIVATE MisterLeadsData juce::juce_audio_utils juce::juce_dsp PUBLIC juce::juce_recommended_config_flags)
  endforeach()
  target_sources(MLTest PRIVATE Tests/LeadsTest.cpp Source/PluginProcessor.cpp Source/PluginEditor.cpp)
  target_sources(MLVideo PRIVATE Tests/VideoRender.cpp Source/PluginProcessor.cpp Source/PluginEditor.cpp)
endif()
