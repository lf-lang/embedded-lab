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

## 6.2. Interrupt Service Routine

1. The [`gpio_set_irq_enabled_with_callback`](https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#ga6165f07f4b619dd08ea6dc97d069e78a) function of the Pico SDK provides a convenient "one-stop shop" for specifying a callback function to invoke upon a voltage event on a GPIO pin. Create a simple program that prints the arguments to the callback function each time you press button A on the robot.

    **Hint:** To define a C function as part of a Lingua Franca program, use a [preamble](https://www.lf-lang.org/docs/handbook/preambles?target=c) within you reactor definition.

    **Hint:** By default, a Lingua Franca program will exit if there are no pending events. Since nothing will be happening until you push button A, the program will exit immediately. You can prevent this either by including a timer and a reaction to that timer or by setting the `keepalive` target property. So your target specification should look like this:
    
    ```
    target C {
      platform: "RP2040",
      threading: false,
      keepalive: true
    }
    ```

2. In the Lingua Franca C target, to create a timestamped event in response to an external event such as an interrupt, you call the the `lf_schedule` function, passing it a pointer to a a [physical action](https://www.lf-lang.org/docs/handbook/actions?target=c).  Modify your previous program so that a reaction is invoked each time you press the button.  In your reaction, print the time elapsed since the last button push in milliseconds.

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

## 6.3. Debouncing