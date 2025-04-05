//------------------------------------------------------------------------
// Copyright(c) 2025 MaxDev0101.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"
#include "maxdev0101/plugin-core/circularbuffer.h"

namespace MaxDev0101 {

static constexpr Steinberg::int32 defaultSampleRate = 44100;

//------------------------------------------------------------------------
//  PitchControlDelayController
//------------------------------------------------------------------------
class PitchControlDelayController : public Steinberg::Vst::EditControllerEx1
{
public:
//------------------------------------------------------------------------
    PitchControlDelayController () : circularBuffer (defaultSampleRate) {};
	~PitchControlDelayController () SMTG_OVERRIDE = default;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/)
	{
		return (Steinberg::Vst::IEditController*)new PitchControlDelayController;
	}

	//--- from IPluginBase -----------------------------------------------
	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;

	//--- from EditController --------------------------------------------
	Steinberg::tresult PLUGIN_API setComponentState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::IPlugView* PLUGIN_API createView (Steinberg::FIDString name) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

 	//---Interface---------
	DEFINE_INTERFACES
		// Here you can add more supported VST3 interfaces
		// DEF_INTERFACE (Vst::IXXX)
	END_DEFINE_INTERFACES (EditController)
    DELEGATE_REFCOUNT (EditController)

//------------------------------------------------------------------------
protected:
    Maxdev0101::Plugin_core::CircularBuffer circularBuffer;
    Steinberg::int32 sampleRate {defaultSampleRate};
    //float delaySamples {22050};
    Steinberg::Vst::ParamValue currentNormalizedDelay = 0;
    
};

//------------------------------------------------------------------------
} // namespace MaxDev0101
