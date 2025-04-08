//------------------------------------------------------------------------
// Copyright(c) 2025 MaxDev0101.
//------------------------------------------------------------------------

#include "processor.h"
#include "cids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"

using namespace Steinberg;

namespace MaxDev0101 {
//------------------------------------------------------------------------
// PitchControlDelayProcessor
//------------------------------------------------------------------------
PitchControlDelayProcessor::PitchControlDelayProcessor()
{
    //--- set the wanted controller for our processor
    setControllerClass(kPitchControlDelayControllerUID);
}

//------------------------------------------------------------------------
PitchControlDelayProcessor::~PitchControlDelayProcessor() {}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::initialize(FUnknown* context)
{
    // Here the Plug-in will be instantiated

    //---always initialize the parent-------
    tresult result = AudioEffect::initialize(context);
    // if everything Ok, continue
    if (result != kResultOk)
    {
        return result;
    }

    //--- create Audio IO ------
    addAudioInput(STR16("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
    addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

    channelBuffers.resize(2);

    /* If you don't need an event bus, you can remove the next line */
    addEventInput(STR16("Event In"), 1);

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::terminate()
{
    // Here the Plug-in will be de-instantiated, last possibility to remove some
    // memory!

    //---do not forget to call parent ------
    return AudioEffect::terminate();
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::setActive(TBool state)
{
    //--- called when the Plug-in is enable/disable (On/Off) -----
    return AudioEffect::setActive(state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::process(Vst::ProcessData& data)
{
    if (data.numInputs == 0 || data.numOutputs == 0)
    {
        return kResultOk;
    }

    if (data.inputParameterChanges)
    {
        int32 numParamsChanged =
            data.inputParameterChanges->getParameterCount();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            Vst::IParamValueQueue* paramQueue =
                data.inputParameterChanges->getParameterData(index);
            if (paramQueue)
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount();
                switch (paramQueue->getParameterId())
                {
                    case PitchControlParamIds::kDelayId: {
                        paramQueue->getPoint(numPoints - 1, sampleOffset,
                                             currentNormalizedDelay);
                        for (auto& channelBuffer : channelBuffers)
                        {
                            channelBuffer.setDelayNormalized(
                                currentNormalizedDelay);
                        }
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < data.numSamples; ++i)
    {
        for (int channel = 0; channel < data.inputs[0].numChannels; ++channel)
        {
            float* in  = data.inputs[0].channelBuffers32[channel];
            float* out = data.outputs[0].channelBuffers32[channel];

            out[i] = channelBuffers[channel].process(in[i]);
        }
    }
    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API
PitchControlDelayProcessor::setupProcessing(Vst::ProcessSetup& newSetup)
{
    sampleRate = newSetup.sampleRate;

    for (auto& channelBuffer : channelBuffers)
    {
        channelBuffer.setup(sampleRate);
        channelBuffer.setDelayNormalized(0.5f);
    }

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API
PitchControlDelayProcessor::canProcessSampleSize(int32 symbolicSampleSize)
{
    // by default kSample32 is supported
    if (symbolicSampleSize == Vst::kSample32)
        return kResultTrue;

    // disable the following comment if your processing support kSample64
    /* if (symbolicSampleSize == Vst::kSample64)
            return kResultTrue; */

    return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::setState(IBStream* state)
{
    // called when we load a preset, the model has to be reloaded
    IBStreamer streamer(state, kLittleEndian);

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::getState(IBStream* state)
{
    // here we need to save the model
    IBStreamer streamer(state, kLittleEndian);

    return kResultOk;
}

} // namespace MaxDev0101
