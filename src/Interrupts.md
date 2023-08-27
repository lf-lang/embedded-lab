# 6. Interrupts and Modal Behavior

<style type="text/css">
    ol ol { list-style-type: lower-alpha; }
</style>

The purpose of this lab exercise is to understand how interrupts work and to use them to asynchronously change modes in a modal Lingua Franca program.
You will also learn to debounce switches.
We recommend Section 10.2 of [Lee and Seshia](https://leeseshia.org).
For the Pico SDK functions that support interrupts on GPIO pins, refer to [hardware_gpio section of the SDK documentation](https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#hardware_gpio).
Other useful resources include Chapter 5, Nested Vectored Interrupt Controller (NVIC), of the [ARM Cortex-M0+ Technical Reference Manual](https://developer.arm.com/documentation/ddi0484/latest/) and
Section B3.4 of the [Armv6-M Architecture Reference Manual](https://developer.arm.com/documentation/ddi0419/latest/).

## 6.1 Prelab

1. In this lab, you will write an interrupt service routine (ISR) that responds when you push button A on the Pololu robot.  The NVIC on the RP2040 can be set to request an interrupt when a voltage level on a GPIO pin is high, when it is low, when it transitions from high to low (falling edge), or when it transitions from low to high (rising edge).  If you would like your ISR to respond exactly once to pressing the B button, and you would like it to respond as quickly as possible, which of these four options should you choose?  What do you think will happen if you choose the other options?

    **Hint:** Refer to the schematic in the previous lab showing GPIO pin 25 and button A.

2. What is it called when one interrupt preempts another interrupt? 
What is one condition that must be met for this to occur?

3. A processor is executing and receives a low-priority external interrupt. What
factors may impact the latency of handling this interrupt?

4. One issue with nested interrupts is that an ISR may have to be carefully designed to be **reentrant**.  A function is reentrant if it can be safely called again while it is in the middle of an execution. You are given the following function:

```
    void send_to_radio(char* data) {
        static char data_to_send[10];
        memcpy(data_to_send, data, 10)
        
        // Assume that this function is reentrant
        radio_send(data_to_send);
    }
```

1. Is the function `send_to_radio` reentrant? Why or why not? **Hint:** Make
sure to understand static variables in C.

2. What is one simple way to make the function reentrant?

## 6.2. Interrupt Service Routine

1. The [`gpio_set_irq_enabled_with_callback`](https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#ga6165f07f4b619dd08ea6dc97d069e78a) function of the Pico SDK provides a convenient "one-stop shop" for specifying a callback function to invoke upon a voltage event on a GPIO pin. Create a simple program `InterruptCallbackSolution.lf` that prints the arguments to the callback function each time you press button A on the robot.

    **Hint:** To define a C function as part of a Lingua Franca program, use a [preamble](https://www.lf-lang.org/docs/handbook/preambles?target=c) within you reactor definition.

    **Hint:** By default, a Lingua Franca program will exit if there are no pending events. Since nothing will be happening until you push button A, the program will exit immediately. You can prevent this either by including a timer and a reaction to that timer or by setting the `keepalive` target property. So your target specification should look like this:
    
    ```
    target C {
      platform: {
        name: "rp2040",
        board: "pololu_3pi_2040_robot"
      },
      threading: false,
      keepalive: true
    }
    ```

2. In the Lingua Franca C target, to create a timestamped event in response to an external event such as an interrupt, you call the the `lf_schedule` function, passing it a pointer to a a [physical action](https://www.lf-lang.org/docs/handbook/actions?target=c).  Modify your previous program so that a reaction is invoked each time you press the button.  In your reaction, print the logical time elapsed since the last button push in milliseconds. Please call your modified program `InterruptActionSolution.lf`.

    **Hint:** In the C target of LF, [logical time](https://www.lf-lang.org/docs/handbook/time-and-timers?target=c) is accessed within a reaction using the function `lf_time_logical` or `lf_time_logical_elapsed()`.

    **Hint:** To accomplish this, you will need to make a pointer to your physical action available within your callback function.  A simple pattern to accomplish this is to use a static global variable of type `void*`, as follows:
    
    ```
    reactor {
      preamble {=
        static void* action;
        ...
      =}
      physical action a
      reaction(startup) -> a {=
        action = a;
        ...
      =}
      ...
    }
    ```
    
    The reaction to `startup` includes the effect `-> a`, which results in a C variable `a` being available within the reaction body. That variable is a pointer to the physical action and can be used as the first argument to the `lf_schedule` function.
    
**Checkoff:** Show your printf output in reaction to button pushes.

## 6.3. Debouncing

You will likely notice that every once in a while, a single push of the A button results in more than one printed output, usually with a rather small time interval between them. The reason for this is that mechanical switches tend to bounce. When you press the button, a metal contact hits another contact, then briefly bounces off and hits again. This results in a voltage signal that transitions more than once for each button press.
Correcting for this is called "**debouncing**".
A simple technique is to ignore events that are too closely spaced.

Modify your previous program so that the physical action is scheduled only if the physical time elapsed between detected events is greater than 200ms.
Please call your modified program `InterruptDebouncedSolution.lf`.

**Hint:** In your callback function, which is invoked outside the scope of any reaction, logical time has no reliable meaning.  Access [physical time](https://www.lf-lang.org/docs/handbook/time-and-timers?target=c) instead, using either `lf_time_physical()` or `lf_time_physical_elapsed()`.

**Checkoff:** Show your printf output in reaction to button pushes.

## 6.4. Modal Programs

Lingua Franca provides syntax for specifying [**modal reactors**](https://www.lf-lang.org/docs/handbook/modal-models?target=c), where a finite state machine (FSM) governs the mode of operation of a reactor.

Create a Lingua Franca program `InterruptModalSolution.lf` that displays a sequence of increasing counting numbers on the LCD display until you push button A, and then starts counting down instead of up.  Make your program switch between counting up and counting down on each button push.  Make your program count down at half the rate that it counts up.

**Checkoff:** Show your LCD display responding to button pushes and your LF diagram.

## 6.5. Postlab

1. A physical action in Lingua Franca, when scheduled, creates an event with a timestamp drawn from the processor's physical clock.  This event, once created, has a logical time equal to this timestamp, and any reactions to this event execute at that logical time. Give at least one significant difference here between physical time and logical time in Lingua Franca.

2. Suppose you are attempting to debug your interrupt handler code, but it is crashing and causing a processor hard fault before exiting the handler. To debug this, you decide to print debug information using `printf` and monitor it on the host computer using `screen`.  But you find that printf does not seem to be working.

    1. What is one reason why `printf` may not work when called from within an ISR?  **Hint:**  The implementation of `printf` is itself using a peripheral device, specifically a device called a UART, and very likely is using interrupts to interact with the device.

    2. How could you modify either your code or the SDK library code to make `printf` work as expected?

    3. What are some possible consequences to your modification that could actually make it more difficult to debug the handler code?

    4. If you decide you do not want to use `printf`, what is one other method by which you could debug your handler? Could this new method have consequences that make it more difficult to debug the handler code?

3. What were your takeaways from the lab? What did you learn during the lab? Did any results in the lab surprise you?
