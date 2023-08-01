# Lingua Franca Embedded Lab
This repository provides documentation and lab exercises for using [Lingua Franca](https://www.lf-lang.org/) (LF) to program the [Pololu 3pi+ 2040 robot](https://www.pololu.com/docs/0J86).
You can build LF programs and flash them directly onto the robot or use a secondary [Pico board](https://www.raspberrypi.com/products/raspberry-pi-pico/) as a debugger using the [picoprobe](https://github.com/raspberrypi/picoprobe) application.

## Read the docs
To read the docs, go to [lf-lang.org/lf-embedded-lab](https://www.lf-lang.org/lf-embedded-lab/). 

## Edit the docs
To contribute to this documentation, fork of this repo and file a pull request.
For documentation on the mdBook framework that we use to render the docs, see [mdbook](https://github.com/rust-lang/mdBook/).

### Build and run locally
The book can also be built and served locally after installing mdbook and running.
Simply run the follow command in the root of this repository:
```
mdbook serve docs/
```

## Other Resources
* [Getting Started with the Raspberry Pi Pico C/C++ development](https://rptl.io/pico-get-started)
* [README file in pico-sdk](https://github.com/raspberrypi/pico-sdk)
* [Pico extras](https://github.com/raspberrypi/pico-extras)
* [Pololu 3pi+ robot documentation](https://www.pololu.com/docs/0J86)
