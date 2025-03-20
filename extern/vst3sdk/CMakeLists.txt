cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    vst3sdk
    GIT_REPOSITORY https://www.github.com/steinbergmedia/vst3sdk.git
    GIT_TAG v3.7.13_build_42
)

FetchContent_MakeAvailable(vst3sdk)
set(vst3sdk_SOURCE_DIR ${vst3sdk_SOURCE_DIR} CACHE INTERNAL "vst3sdk source dir")
message(STATUS "[DEBUG] vst3sdk source directory: ${vst3sdk_SOURCE_DIR}")