cmake_minimum_required(VERSION 3.14.0)

include (FetchContent)

FetchContent_Declare(
    coreaudiosdk
    URL https://developer.apple.com/library/archive/samplecode/CoreAudioUtilityClasses/CoreAudioUtilityClasses.zip
)

FetchContent_MakeAvailable(coreaudiosdk)
set(SMTG_COREAUDIO_SDK_PATH ${coreaudiosdk_SOURCE_DIR}/CoreAudio CACHE INTERNAL STRING FORCE)
message(STATUS "[DEBUG] coreaudiosdk source directory: ${coreaudiosdk_SOURCE_DIR}")