//------------------------------------------------------------------------
// Copyright(c) 2025 MaxDev0101.
//------------------------------------------------------------------------

#include "controller.h"
#include "cids.h"
#include "pluginterfaces/base/ustring.h"
#include "vstgui/plugin-bindings/vst3editor.h"

#include <vector>

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace MaxDev0101 {

//------------------------------------------------------------------------
// PitchControlDelayController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayController::initialize(FUnknown* context)
{
    // Here the Plug-in will be instantiated

    //---do not forget to call parent ------
    tresult result = EditControllerEx1::initialize(context);
    if (result != kResultOk)
    {
        return result;
    }

    if (result == kResultTrue)
    {
        parameters.addParameter(STR16("Delay"), STR16("samples"), 0, 0.5,
                                ParameterInfo::kCanAutomate,
                                PitchControlParamIds::kDelayId);
    }

    return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayController::terminate()
{
    // Here the Plug-in will be de-instantiated, last possibility to remove some
    // memory!

    //---do not forget to call parent ------
    return EditControllerEx1::terminate();
}

//------------------------------------------------------------------------
tresult PLUGIN_API
PitchControlDelayController::setComponentState(IBStream* state)
{
    // Here you get the state of the component (Processor part)
    if (!state)
        return kResultFalse;

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayController::setState(IBStream* state)
{
    // Here you get the state of the controller

    return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayController::getState(IBStream* state)
{
    // Here you are asked to deliver the state of the controller (if needed)
    // Note: the real state of your plug-in is saved in the processor

    return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API PitchControlDelayController::createView(FIDString name)
{
    // Here the Host wants to open your editor (if you have one)
    if (FIDStringsEqual(name, Vst::ViewType::kEditor))
    {
        // create your editor here and return a IPlugView ptr of it
        auto* view = new VSTGUI::VST3Editor(this, "view", "editor.uidesc");
        return view;
    }
    return nullptr;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayController::getParamStringByValue(
    ParamID tag, ParamValue valueNormalized, String128 string)
{
    if (tag == kDelayId)
    {
        int32 delaySamples = static_cast<int32>(valueNormalized * 2000.0);
        Steinberg::UString(string, 128).printInt(delaySamples);
        return kResultTrue;
    }

    return EditControllerEx1::getParamStringByValue(tag, valueNormalized,
                                                    string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayController::getParamValueByString(
    ParamID tag, TChar* string, ParamValue& valueNormalized)
{
    if (tag == kDelayId)
    {
        Steinberg::UString128 tempString(string);
        int64 samples = 0;
        if (tempString.scanInt(samples) == kResultTrue)
        {
            samples = std::min(std::max(0, static_cast<int>(samples)), 2000);
            valueNormalized = static_cast<ParamValue>(samples) / 2000.0f;
            return kResultTrue;
        }
    }

    return EditControllerEx1::getParamValueByString(tag, string,
                                                    valueNormalized);
}

//------------------------------------------------------------------------
} // namespace MaxDev0101
