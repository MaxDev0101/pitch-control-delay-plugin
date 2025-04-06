# PitchControlDelay VST 3 Plug-In

[![CMake (Linux, macOS, Windows)](https://github.com/maxdev0101/pitch-control-delay-plugin/actions/workflows/cmake.yml/badge.svg)](https://github.com/maxdev0101/pitch-control-delay-plugin/actions/workflows/cmake.yml)

## Introduction

PitchControlDelay is an VST 3 / AU (macOS) plug-in. 
A sample delay which matches the samplerate for the process of vinyl cutting.

## Getting Started

Do you have **CMake** installed? If not please check the Prerequisites section.

To clone and create the project, open a command prompt and proceed as follows:

### Windows

```sh
git clone https://github.com/maxdev0101/pitch-control-delay-plugin.git
mkdir build
cd build
cmake ../pitch-control-delay-plugin
cmake --build .
```

### macOS

```sh
git clone https://github.com/maxdev0101/pitch-control-delay-plugin.git
mkdir build
cd build
cmake -GXcode ../pitch-control-delay-plugin
cmake --build .
```

### Linux

```sh
git clone https://github.com/maxdev0101/pitch-control-delay-plugin.git
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../pitch-control-delay-plugin
cmake --build .
```

As soon as the project has been successfully built, you will find the plugin bundle in the build folder: ```VST3/Debug/pitch-control-delay.vst3``` and on macOS also ```VST3/Debug/pitch-control-delay.component``` for the AU plug-in

## Prerequisites

Make sure you have **CMake** installed before building this project.

### Install CMake:
- **Windows**: Download and install from [CMake Official Site](https://cmake.org/download/).  
- **Linux (Debian/Ubuntu)**:  
  ```sh
  sudo apt update && sudo apt install cmake

- **macOS (Homebrew)**:
  ```sh
  brew install cmake

Check if CMake is Installed:
Run the following command to verify the installation:
    ```sh
cmake --version

## Further Infos
>See also: https://github.com/steinbergmedia/vst3sdk