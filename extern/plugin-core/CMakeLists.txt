cmake_minimum_required(VERSION 3.20.0)

include(FetchContent)
FetchContent_Declare(
    plugin-core
	GIT_REPOSITORY https://github.com/MaxDev0101/plugin-core.git
	GIT_TAG main
)

FetchContent_MakeAvailable(plugin-core)