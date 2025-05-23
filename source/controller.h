//------------------------------------------------------------------------
// Copyright(c) 2025 MaxDev0101.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

namespace MaxDev0101 {

//------------------------------------------------------------------------
//  PitchControlDelayController
//------------------------------------------------------------------------
class PitchControlDelayController : public Steinberg::Vst::EditControllerEx1
{
public:
    //------------------------------------------------------------------------
    PitchControlDelayController()                = default;
    ~PitchControlDelayController() SMTG_OVERRIDE = default;

    // Create function
    static Steinberg::FUnknown* createInstance(void* /*context*/)
    {
        return (
            Steinberg::Vst::IEditController*)new PitchControlDelayController;
    }

    //--- from IPluginBase -----------------------------------------------
    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context)
        SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE;

    //--- from EditController --------------------------------------------
    Steinberg::tresult PLUGIN_API setComponentState(Steinberg::IBStream* state)
        SMTG_OVERRIDE;
    Steinberg::IPlugView* PLUGIN_API createView(Steinberg::FIDString name)
        SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state)
        SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state)
        SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API
    getParamStringByValue(Steinberg::Vst::ParamID tag,
                          Steinberg::Vst::ParamValue valueNormalized,
                          Steinberg::Vst::String128 string) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API getParamValueByString(
        Steinberg::Vst::ParamID tag,
        Steinberg::Vst::TChar* string,
        Steinberg::Vst::ParamValue& valueNormalized) SMTG_OVERRIDE;
    //---Interface---------
    DEFINE_INTERFACES
    // Here you can add more supported VST3 interfaces
    // DEF_INTERFACE (Vst::IXXX)
    END_DEFINE_INTERFACES(EditController)
    DELEGATE_REFCOUNT(EditController)

    //------------------------------------------------------------------------
protected:
};

//------------------------------------------------------------------------
} // namespace MaxDev0101
