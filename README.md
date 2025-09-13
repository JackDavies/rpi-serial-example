# rpi-pico-template
---
Template for Raspberry Pi Pico projects

#### Dependencies
This template uses the official [C/C++ SDK](https://github.com/raspberrypi/pico-sdk). 
By default the Pico SDK needs to be cloned to the same directory as the template project, to change this modify the `-DPICO_SDK_PATH` cmake option in `src/build.sh` 

This template also includes [rpi-pico-utils](https://github.com/JackDavies/rpi-pico-utils) as a sub-module

#### Build
To build the project, run `src/build.sh` by default the target directory for the build is in `src/build`