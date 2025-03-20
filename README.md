# HalfSpin VST 3 Plug-In

HalfSpin is an VST 3 / AU (macOS) plug-in. 
A sample delay which matches the samplerate for the process of vinyl cutting.

## Getting Started

To clone and create the project, open a command prompt and proceed as follows:

### Windows

```sh
git clone https://github.com/maxdev0101/halfspin-plugin.git
mkdir build
cd build
cmake ../halfspin-plugin
cmake --build .
```

### macOS

```sh
git clone https://github.com/maxdev0101/halfspin-plugin.git
mkdir build
cd build
cmake -GXcode ../halfspin-plugin
cmake --build .
```

### Linux

```sh
git clone https://github.com/maxdev0101/halfspin-plugin.git
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../halfspin-plugin
cmake --build .
```

As soon as the project has been successfully built, you will find the plugin bundle in the build folder: ```VST3/Debug/halfspin.vst3``` and on macOS also ```VST3/Debug/halfspin.component``` for the AU plug-in

> See also: https://github.com/steinbergmedia/vst3sdk