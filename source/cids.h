//------------------------------------------------------------------------
// Copyright(c) 2025 MaxDev0101.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MaxDev0101 {

// parameter tags
enum {
    kDelayId = 100
};

//------------------------------------------------------------------------
static const Steinberg::FUID kPitchControlDelayProcessorUID (0xFC11F948, 0xE80950E2, 0x848EC351, 0xF2C3D161);
static const Steinberg::FUID kPitchControlDelayControllerUID (0x522C797A, 0xB61654ED, 0x8A24F96C, 0x311D8E72);

#define PitchControlDelayVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace MaxDev0101
