//------------------------------------------------------------------------
// Copyright(c) 2025 MaxDev0101.
//------------------------------------------------------------------------

#include "processor.h"
#include "cids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

using namespace Steinberg;

namespace MaxDev0101 {
//------------------------------------------------------------------------
// PitchControlDelayProcessor
//------------------------------------------------------------------------
PitchControlDelayProcessor::PitchControlDelayProcessor()
    : circularBuffer(44100) {
  //--- set the wanted controller for our processor
  setControllerClass(kPitchControlDelayControllerUID);
}

//------------------------------------------------------------------------
PitchControlDelayProcessor::~PitchControlDelayProcessor() {}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::initialize(FUnknown *context) {
  // Here the Plug-in will be instantiated

  //---always initialize the parent-------
  tresult result = AudioEffect::initialize(context);
  // if everything Ok, continue
  if (result != kResultOk) {
    return result;
  }

  //--- create Audio IO ------
  addAudioInput(STR16("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
  addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

  /* If you don't need an event bus, you can remove the next line */
  addEventInput(STR16("Event In"), 1);

  return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::terminate() {
  // Here the Plug-in will be de-instantiated, last possibility to remove some
  // memory!

  //---do not forget to call parent ------
  return AudioEffect::terminate();
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::setActive(TBool state) {
  //--- called when the Plug-in is enable/disable (On/Off) -----
  return AudioEffect::setActive(state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::process(Vst::ProcessData &data) {
  if (data.numInputs == 0 || data.numOutputs == 0) {
    return kResultOk;
  }

  for (int channel = 0; channel < data.inputs[0].numChannels; ++channel) {
    float *in = data.inputs[0].channelBuffers32[channel];
    float *out = data.outputs[0].channelBuffers32[channel];

    for (int i = 0; i < data.numSamples; ++i) {
      circularBuffer.write(in[i]);
      out[i] = circularBuffer.readInterpolated(delaySamples);
    }
  }
  return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API
PitchControlDelayProcessor::setupProcessing(Vst::ProcessSetup &newSetup) {

  sampleRate = newSetup.sampleRate;
  circularBuffer.resizeBufferOnSampleRateChange(
      sampleRate); // always sampleRate*2 buffer size
  // updateDelaySamplesFromParameter(currentNormalizedDelay);
  return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API
PitchControlDelayProcessor::canProcessSampleSize(int32 symbolicSampleSize) {
  // by default kSample32 is supported
  if (symbolicSampleSize == Vst::kSample32)
    return kResultTrue;

  // disable the following comment if your processing support kSample64
  /* if (symbolicSampleSize == Vst::kSample64)
          return kResultTrue; */

  return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::setState(IBStream *state) {
  // called when we load a preset, the model has to be reloaded
  IBStreamer streamer(state, kLittleEndian);

  return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PitchControlDelayProcessor::getState(IBStream *state) {
  // here we need to save the model
  IBStreamer streamer(state, kLittleEndian);

  return kResultOk;
}

//------------------------------------------------------------------------
void PitchControlDelayProcessor::updateDelaySamplesFromParameter(
    Vst::ParamValue normalizedValue) {
  // The maximum delay is sampleRate * 2 samples.
  delaySamples = normalizedValue * (sampleRate * 2);
}
} // namespace MaxDev0101
