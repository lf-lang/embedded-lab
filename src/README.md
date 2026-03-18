# Introduction
This series of labs exposes students to introductory embedded systems concepts.
The labs focus on cyber-physical systems modeling and design.
They use the [Lingua Franca coordination language](https://lf-lang.org) to provide timing, concurrency, and state-machine modeling (via its modal models),
and low-level programming is in C.
The labs are designed to be companion exercises for a course based on [Lee and Seshia, *Introduction to Embedded Systems: A Cyber-Physical Systems Approach*](https://leeseshia.org), MIT Press, 2017.
The C code runs on a [Raspberry Pi RP2040](https://en.wikipedia.org/wiki/RP2040)
on the [Pololu 3pi+ 2040 robot](https://www.pololu.com/docs/0J86). 
The same RP2040 microprocessor is also available on the low-cost [Raspberry Pi Pico board](https://en.wikipedia.org/wiki/Raspberry_Pi#Raspberry_Pi_Pico), but this board does not have the sensors and actuators of the Pololu robot, so you will need the robot to be able to complete all the exercises.

## Institutions Using the Labs

The embedded systems labs with Lingua Franca have been used by various courses at institutions around the world, including the following (listed alphabetically):

- **Arizona State University** — *CSE 522: Real-Time Embedded Systems*
- **Southern Illinois University** — *ECE 424/540: Design of Embedded Systems*
- **University of California, Berkeley** — *EECS 149/249A: Introduction to Embedded and Cyber Physical Systems*
- **University of Maryland** — *ENEB452: Advanced Software for Connected Embedded Systems*
- **University of Michigan-Dearborn** — *ME 472: Principles and Applications of Mechatronic Systems, ECE 566 / ME 565: Mechatronics*

If your institution is using the embedded systems labs but is not listed here, please email Hokeun Kim ([hokeun@asu.edu](mailto:hokeun@asu.edu)) with your course information, or submit a [pull request](https://github.com/lf-lang/embedded-lab/pulls) to add your course information.

## Contributing
You can find the Markdown sources of these labs on [GitHub](https://github.com/lf-lang/embedded-lab). If you discover any problems, please consider creating an [issue](https://github.com/lf-lang/embedded-lab/issues) or submitting a [pull request](https://github.com/lf-lang/embedded-lab/pulls).

## Acknowledgments

The main authors of this version of the labs are:

- Abhi Gundrala
- Hokeun Kim
- Aditya Krishnan 
- Edward A. Lee
- Marten Lohstroh

These labs are derived from several generations of lab exercises for the Berkeley EECS 149/249A course, Introduction to embedded systems. Contributors to the lab design include:

- Joshua Adkins
- Prabal Dutta
- Branden Ghena
- Shromona Ghosh
- Abhi Gudrala
- Jeff C. Jensen
- Eric S. Kim
- Hokeun Kim
- Edward A. Lee
- Shaokai Lin
- Sanjit Seshia
- Trung Tran
- Matthew Weber
