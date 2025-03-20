cmake_minimum_required(VERSION 3.14.0)

include (FetchContent)

FetchContent_Declare(
    AudioUnitSDK
    GIT_REPOSITORY https://github.com/apple/AudioUnitSDK.git
    GIT_TAG        AudioUnitSDK-1.3.0
)
FetchContent_MakeAvailable(AudioUnitSDK)
message(STATUS "[DEBUG] AudioUnitSDK source directory: ${AudioUnitSDK_SOURCE_DIR}")
