/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BypassPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    BypassPluginAudioProcessorEditor (BypassPluginAudioProcessor&);
    ~BypassPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BypassPluginAudioProcessor& processor;

	typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

	ToggleButton bypassButton;
	std::unique_ptr<ButtonAttachment> bypassAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BypassPluginAudioProcessorEditor)
};
