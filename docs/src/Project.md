# Project Ideas

There are many possible projects using the [Pololu 3pi+ 2040 robot](https://www.pololu.com/docs/0J86).  Several of these will require access to the expansion ports (see [Tools and Environments](./Tools.md)).

1. **Low power robot.**  The ARMv6 processor in the RP2040 has a specialized instruction for putting the processor to sleep until an interrupt occurs.  The goal of this project is to use this instruction to reduce the energy consumption of Lingua Franca programs running on the processor.  A significant part of the project is to design the experiments that measure energy use and to determine when the sleep instruction should be used and when it should not be used.  A demonstration should include an LF application that lie quiescent for an indefinite period of time while nothing is happening and yet remain reactive to external events, e.g., shake the robot to wake it up.  The accelerometer on the Pololu robot has a low power event detection mode that could be used for this purpose.

2. **Interactive debugging.** The RP2040 processor has a debugging interface that can be connected to a secondary Raspberry Pi Pico running a monitoring program called FIXME.  The secondary RP Pico can in turn be connected to a host computer running gdb, lldb, or the debugger in VS Code to achieve interactive debugging.  The goal of this project is to develop the hardware, software, and engineering processes for conveniently performing interactive debugging of Lingua Franca programs running on the Pololu robot. This includes designing and manufacturing a printed circuit board that bridges a header on the robot with the secondary RP Pico. It also includes investigating the VS Code debugging API to determine whether it is possible to debug directly from the LF source code (vs. the generated C code, which certainly should be possible). 

3. **Bare metal multithreading.**  The RP2040 has two cores, only one of which is used by Lingua Franca when the threading target parameter is set to false.  It should be possible to enable multi threading and limit the number of threads to two, one running on each core.  This project will redesign the LF platform support to accomplish this.  This will require learning how the two cores interact through memory and peripherals as well as how LF uses multi threading.  The project should include designing experiments to measure the efficiency of the approach and the benefits compared to the unthreaded implementation that uses only a single core.

4. **Bluetooth connected robot.**  The Pololu robot has no network connectivity, but it has two UARTs, one of which could be dedicated to providing a serial connection over bluetooth. The goal of this project is to identify a serial bluetooth device that can be connected to the one of the UARTs and then to develop demonstrations of robot control over bluetooth.

5. **AI robot.**  According to its [wikipedia page](https://en.wikipedia.org/wiki/RP2040), the RP2040 is sufficiently powerful to run [TensorFlow Lite](https://en.wikipedia.org/wiki/TensorFlow#TensorFlow_Lite). The goal of this project is to test this claim and develop some meaningful application running on the robot and using machine learning.
