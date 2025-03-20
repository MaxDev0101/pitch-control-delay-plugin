cmake_minimum_required(VERSION 3.14.0)

option(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES "Enable VST 3 Plug-in Examples" OFF)
option(SMTG_ENABLE_VST3_HOSTING_EXAMPLES "Enable VST 3 Hosting Examples" OFF)

option(SMTG_ENABLE_AUV2_BUILDS "Enable building of AUv2 plugin" ON)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

project(HalfSpin
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "HalfSpin VST 3 Plug-in"
)

add_subdirectory(extern)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

smtg_enable_vst3_sdk()

smtg_add_vst3plugin(HalfSpin
    source/version.h
    source/cids.h
    source/processor.h
    source/processor.cpp
    source/controller.h
    source/controller.cpp
    source/entry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ENABLE_VSTGUI_SUPPORT)
    target_sources(HalfSpin
        PRIVATE
            resource/editor.uidesc
    )
    target_link_libraries(HalfSpin
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(HalfSpin
        RESOURCES
            "resource/editor.uidesc"
    )
endif(SMTG_ENABLE_VSTGUI_SUPPORT)
# -------------------

smtg_target_add_plugin_snapshots (HalfSpin
    RESOURCES
        resource/FC11F948E80950E2848EC351F2C3D161_snapshot.png
        resource/FC11F948E80950E2848EC351F2C3D161_snapshot_2.0x.png
)

target_link_libraries(HalfSpin
    PRIVATE
        sdk
)

smtg_target_configure_version_file(HalfSpin)

if(SMTG_MAC)
    smtg_target_set_bundle(HalfSpin
        BUNDLE_IDENTIFIER org.maxdev0101.halfspin
        COMPANY_NAME "MaxDev0101"
    )
    smtg_target_set_debug_executable(HalfSpin
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(HalfSpin PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HalfSpin)

        smtg_target_set_debug_executable(HalfSpin
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)

# -- Add the AUv2 target
if (SMTG_MAC AND XCODE AND SMTG_ENABLE_AUV2_BUILDS)
    message(STATUS "CMAKE_MODULE_PATH is located at: ${vst3sdk_SOURCE_DIR}/cmake/modules")
    list(APPEND CMAKE_MODULE_PATH "${vst3sdk_SOURCE_DIR}/cmake/modules")
    include(SMTG_AddVST3AuV2)
    smtg_target_add_auv2(HalfSpin_AU
        BUNDLE_NAME halfspin
        BUNDLE_IDENTIFIER org.maxdev0101.halfspin.audiounit
        INFO_PLIST_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/resource/au-info.plist
        VST3_PLUGIN_TARGET HalfSpin)
    smtg_target_set_debug_executable(HalfSpin_AU "/Applications/Studio One 6.app")
endif(SMTG_MAC AND XCODE AND SMTG_ENABLE_AUV2_BUILDS)
