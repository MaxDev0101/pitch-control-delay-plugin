#!/bin/sh

# Exit immediately if any command fails
set -e  

# Display help function
function display_help {
    echo "Usage: $0 [option] arg1 arg2 arg3"
    echo
    echo "This script clones the repository, creates and builds the project, signs the binary, creates and signs the installer and runs Apples notary services."
    echo
    echo "Options:"
    echo "  -h, --help      Show this help message"
    echo
    echo "Arguments:"
    echo "  arg1            The first argument, Developer ID Application as string"
    echo "  arg2            The second argument, Git tag as string (Optional)"
    echo
    echo "Example:"
    echo "  $0 'Developer ID Application: My Company (E53ZE5AABB)' v2025.02"
    echo
    exit 0
}

# Check if -h or --help is passed
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    display_help
fi

# If no arguments are provided, show error and help
if [[ $# -le 1 ]]; then
    echo "[MAM] MacOS_Build_Release_sh: Error, insufficient arguments provided."
    display_help
fi

# Clone project
echo "[MAM] MacOS_Build_Release_sh: Clone Project"
git clone https://github.com/MaxDev0101/pitch-control-delay-plugin.git

echo "[MAM] MacOS_Build_Release_sh: Checkout Project with tag" 
if [ -n "$2" ]; then
    cd pitch-control-delay-plugin
    git checkout -b checkout-at-"$2" "$2"
    cd ..
fi

# Cmake project
mkdir build
cd build
echo "[MAM] MacOS_Build_Release_sh: CMake project"
cmake -GXcode ../pitch-control-delay-plugin
# AU only for now
cmake --build . --target PitchControlDelay_AU --config Release

# Copy vst3 plugin in place
rm ./VST3/Release/pitch-control-delay.component/Contents/Resources/plugin.vst3
cp -R ./VST3/Release/PitchControlDelay.vst3 ./VST3/Release/pitch-control-delay.component/Contents/Resources/plugin.vst3

# Sign the binaries
echo "[MAM] MacOS_Build_Release_sh: Sign the binaries"
codesign --sign "$1" -f -o runtime --timestamp -v ./VST3/Release/pitch-control-delay.component/Contents/Resources/plugin.vst3/Contents/MacOS/PitchControlDelay
codesign --sign "$1" -f -o runtime --timestamp -v ./VST3/Release/pitch-control-delay.component

# Check binary signing
echo "[MAM] MacOS_Build_Release_sh: Check binary signing:"
codesign --display -vv ./VST3/Release/pitch-control-delay.component

# Run the packager
echo "MacOS_Build_Release_sh: Run the packager:"
ditto -c -k --sequesterRsrc --keepParent ./VST3/Release/pitch-control-delay.component ./pitch-control.zip                                    

# Find the generated installer 
installer_name=$(ls *.zip)

# Check if a .pkg file exists
if [ -z "$installer_name" ]; then
    echo "No .zip file found"
    exit 1
fi

# Handle multiple .pkg files
if [ $(echo "$installer_name" | wc -l) -ne 1 ]; then
    echo "Multiple .zip files found:"
    echo "$installer_name"
    echo "Please make sure only one package exists."
    exit 1
fi

## Run the notary service
echo "[MAM] MacOS_Build_Release_sh: Run the notary service:"
xcrun notarytool submit "./pitch-control.zip" --keychain-profile NOTARYTOOL_PASSWORD --wait                                                  

## Run Stapler
echo "[MAM] MacOS_Build_Release_sh: Staple the result:"
xcrun stapler staple ./VST3/Release/pitch-control-delay.component