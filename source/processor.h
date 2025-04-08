//------------------------------------------------------------------------
// Copyright(c) 2025 MaxDev0101.
//------------------------------------------------------------------------

#pragma once

#include "maxdev0101/plugin-core/circularbuffer.h"
#include "public.sdk/source/vst/vstaudioeffect.h"

namespace MaxDev0101 {
static constexpr Steinberg::int32 defaultSampleRate = 44100;
//------------------------------------------------------------------------
//  PitchControlDelayProcessor
//------------------------------------------------------------------------
class PitchControlDelayProcessor : public Steinberg::Vst::AudioEffect
{
public:
    PitchControlDelayProcessor();
    ~PitchControlDelayProcessor() SMTG_OVERRIDE;

    // Create function
    static Steinberg::FUnknown* createInstance(void* /*context*/)
    {
        return (Steinberg::Vst::IAudioProcessor*)new PitchControlDelayProcessor;
    }

    //--- ---------------------------------------------------------------------
    // AudioEffect overrides:
    //--- ---------------------------------------------------------------------
    /** Called at first after constructor */
    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context)
        SMTG_OVERRIDE;

    /** Called at the end before destructor */
    Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE;

    /** Switch the Plug-in on/off */
    Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state)
        SMTG_OVERRIDE;

    /** Will be called before any process call */
    Steinberg::tresult PLUGIN_API
    setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;

    /** Asks if a given sample size is supported see SymbolicSampleSizes. */
    Steinberg::tresult PLUGIN_API
    canProcessSampleSize(Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

    /** Here we go...the process call */
    Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data)
        SMTG_OVERRIDE;

    /** For persistence */
    Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state)
        SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state)
        SMTG_OVERRIDE;

    //------------------------------------------------------------------------
protected:
    void
    updateDelaySamplesFromParameter(Steinberg::Vst::ParamValue normalizedValue);

    using ChannelBuffers = std::vector<MaxDev0101::Plugin_core::CircularBuffer>;
    ChannelBuffers channelBuffers;
    Steinberg::int32 sampleRate{defaultSampleRate};
    Steinberg::Vst::ParamValue currentNormalizedDelay = 0.5;
};

//------------------------------------------------------------------------
} // namespace MaxDev0101
