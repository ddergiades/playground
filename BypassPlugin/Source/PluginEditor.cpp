/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BypassPluginAudioProcessorEditor::BypassPluginAudioProcessorEditor (BypassPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	bypassButton.setButtonText ("Bypass");
	addAndMakeVisible(bypassButton);
	bypassAttachment.reset(new ButtonAttachment(p.parameters(), "bypass", bypassButton));
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

BypassPluginAudioProcessorEditor::~BypassPluginAudioProcessorEditor()
{
}

//==============================================================================
void BypassPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void BypassPluginAudioProcessorEditor::resized()
{
	bypassButton.setBounds(getLocalBounds());
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
