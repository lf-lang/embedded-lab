# Testing

the repo exposes a set of different mock drivers for the pico that are used to test the robot driver library. these robot drivers are platform agnostic and can be used with various different hals. based on the platform the testing procedure for the 3pi+ robot drivers varies.

## Overview
Use both a node based emulator and the pico-sdk host mock drivers to build native c tests for timing tests. All will be used in the test environment.
### Host Mode
Build apps using host mode -DPICO_PLATFORM=host. Will use a set of mock platform libraries that do not interact with hardware useful for most single-threaded
pico tests. 
### Emulator
For hardware peripheral integration tests, physical actions and multicore.
Create a nix based test environment.
Use rp2040js to create an emulator and compile basic
timing based tests. 
TODO: think about how to extract code coverage
using this method. 
Or, manually think of different scenarios that can be used as basic regression.
Capture emulator output and compare trace against successful run.
TODO: write test runner as a lingua franca program. sim environment that
interacts with the various pins on the controller to produce outputs
in the robot fashion.
- input to pins
- output checker
a ts reactor program with dependency on rp2040js
generic spi reader probe, i2c reader probe, gpio?
#### PIO Emulator
https://github.com/soundpaint/rp2040pio specific pio operations

