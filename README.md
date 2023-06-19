# lf-pico
This repository provides support for Lingua Franca (LF) programs on the Raspberry Pi Pico (RPi-Pico) using the Pico software development kit (pico-sdk). More specifically, it provides support for programming the RPi-Pico on the [Pololu 3pi+ 2040 robot](https://www.pololu.com/docs/0J86). 
You can build LF programs and flash them directly onto the RPi-Pico or using a secondary Pico board as a debugger using the [picoprobe](https://github.com/raspberrypi/picoprobe) application.

## Instructions

The repository includes a [mdbook](https://github.com/rust-lang/mdBook) in /docs that serves as documentation for the repo. 
The book is currently hosted [here](https://www.lf-lang.org/lf-pico/). 
The book can also be built and served locally after installing mdbook and running.
```
mdbook serve docs/
```

* [Install lf-pico](docs/InstallLFPico.md)
* [Using lf-pico](docs/UsingLFPico.md)

## Other Resources:

* [Getting Started with the Raspberry Pi Pico C/C++ development](https://rptl.io/pico-get-started)
* [README file in pico-sdk](https://github.com/raspberrypi/pico-sdk)
* [Pico extras](https://github.com/raspberrypi/pico-extras)
* [Pololu 3pi+ robot documentation](https://www.pololu.com/docs/0J86)
