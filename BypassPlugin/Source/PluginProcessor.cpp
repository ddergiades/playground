/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BypassPluginAudioProcessor::BypassPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
	params{ *this, nullptr, Identifier{"BypassParams"}, {
		std::make_unique<AudioParameterBool>("bypass", "Bypass audio", false)
	}},
	bypassParam { nullptr }
#endif
{
	bypassParam = params.getRawParameterValue ("bypass");
}

BypassPluginAudioProcessor::~BypassPluginAudioProcessor()
{
}

//==============================================================================
const String BypassPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BypassPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BypassPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BypassPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BypassPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BypassPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BypassPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BypassPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String BypassPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void BypassPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BypassPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BypassPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BypassPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BypassPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
	if (*bypassParam < 0.5)
	{
		auto totalNumInputChannels = getTotalNumInputChannels();
		auto totalNumOutputChannels = getTotalNumOutputChannels();
		for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
			buffer.clear(i, 0, buffer.getNumSamples());
	}
	else {
		buffer.clear();
	}
}

//==============================================================================
bool BypassPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BypassPluginAudioProcessor::createEditor()
{
    return new BypassPluginAudioProcessorEditor (*this);
}

//==============================================================================
void BypassPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = params.copyState();
	ScopedXmlPtr xml_ptr (state.createXml());
	copyXmlToBinary (*xml_ptr, destData);
}

void BypassPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	ScopedXmlPtr state (getXmlFromBinary (data, sizeInBytes));
	if (state.get() != nullptr && state->hasTagName (params.state.getType())) 
	{
		params.replaceState (ValueTree::fromXml (*state));
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BypassPluginAudioProcessor();
}

AudioProcessorValueTreeState& BypassPluginAudioProcessor::parameters()
{
	return params;
}
