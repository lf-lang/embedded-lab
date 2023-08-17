# 7. Robot

<style type="text/css">
    ol ol { list-style-type: lower-alpha; }
</style>

The purpose of this exercise is to write software that uses sensor data to maneuver the Pololu robot.  You will gain experience with additional sensors.

## 7.1 Prelab

1. For this lab, we will be detecting and maneuvering around obstacles using the Pololu robot. What sensor(s) on the robot will be most useful for detecting obstacles?

2. For this lab, we will be using a gyroscope to sense turns made by the robot. 
The [ST LMS6DSO inertial module](https://www.pololu.com/file/0J1899/lsm6dso.pdf), which you encountered in the [Sensors lab](./Sensors.md), includes a gyroscope as well as the accelerometer you used in that lab.
The gyroscope senses *angular velocity* and reports it in units of degrees per second (<sup>o</sup>/s).

    There is a Lingua Franca reactor called `Gyro` available to you in `src/lib/IMU.lf` that outputs gyroscope measurements in units of degrees per second when triggered.
    Suppose that what you want is not angular velocity but rather a measurement of the
    *current angle* of the device relative to some starting angle.
    Explain how you can convert an angular velocity measurement into an angle measurement.
    Specifically, given the *i* <sup>th</sup> measurement *v*<sub><i>i</i></sub> of an angular velocity that is taken at time *t*<sub><i>i</i></sub>,
how can you construct an estimate of the angle *a*<sub><i>i</i></sub> at time *t*<sub><i>i</i></sub>?

3. The speed of motors can be controlled using a technique called **pulse width modulation** (**PWM**).  The RP2040 chip includes hardware for controlling up to 16 motors using PWM, as explained in Section 4.5 of the [RP2040 datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf).  For this purpose, each PWM hardware block can be connected to a GPIO pin, and then you can use the GPIO pin to control the motors.  Which GPIO pins are used to control the motors on the Pololu robot?

    **Hint:** The [Pololu 3pi+ 2040 Robot User's Guide](https://www.pololu.com/docs/0J86) might be helpful.
    
    **Note:** The GPIO pins cannot drive a motor directly because they cannot source enough power without damaging the chip.  The Pololu robot includes a [Texas Instruments DRV8838 motor driver](https://www.ti.com/lit/ds/symlink/drv8838.pdf) which takes as input the PWM signal and provides power to the motors.


4. Using the notation from the textbook for state machines, sketch a state machine
for a robot controller that makes the robot move in a square. That is, when the program is run,
the robot should move forward some distance *D*,
turn 90 degrees, move forward a distance *D* again, and repeat these actions.

## 7.2 Motors

Your first task is to drive the motors on the Pololu robot. For your convenience, a library reactor called `Motors` is provided in `src/lib/Motors.lf`.  You should start with the provided LF program `src/RobotTemplate.lf`.  Start by verifying that this template works for you:

```
    lfc src/RobotTemplate.lf
    picotool load -x bin/RobotTemplate.elf
```

The robot should start by displaying `INIT`, then switch between `DRIVING` and `STOPPED`.

1. Examine the `Motors` reactor. How does it work?  Find the `motors_set_power` function that it uses. (**Hint:** the search function in VS Code is very useful for this.) Explain how the implementation of this function conforms with the answer you gave in question (3) of the prelab.

2. Use the `Motors` reactor to make robot move forward while it is the `DRIVING` mode and stops while in the `STOPPED` mode.  You can experiment with the power to provide, but a good starting point is 0.1f.

    **Hint:** The motors will not run if the only source of power to the robot is the USB cable.  To get the motors to run, you must insert batteries and push the power button so that the blue power indicator LED is illuminated.

    **Checkoff:** Show that you understand the implementation of the `motors_set_power` function and that your robot moves forward and stops.

## 7.3 Encoders

Encoders measure wheel rotation and can be used to estimate the distance traveled.
A technique known as [dead reckoning](https://en.wikipedia.org/wiki/Dead_reckoning) uses such measurements to help to know where the robot is located relative to some starting point.
Our goal here is to create a reactor that takes as input an encoder reading and outputs
an estimate of the distance traveled since the program has started for each wheel.

The output from the encoders is in degrees given as a 32-bit integer.
Examine and run the `src/EncoderDisplay.lf` LF program.
You will convert these numbers to distance.

1. The diameter of the wheels on the robot is approximately 3.175 cm.
Find a formula that converts a change in angle in degrees to distance traveled in meters.

2. The encoder outputs increase as the wheels rotate forward. Given that the values are 32-bit signed integers, how far does a wheel need to travel before the numbers will overflow?  Do you think you need to worry about overflow for these labs?

3. Write a reactor to convert a change in encoder value to distance.
Then create a variant of `src/EncoderDisplay.lf` that displays distance traveled for each wheel rather than angle in degrees.

**Checkoff:** Show that your distance measurement is reasonably accurate.

## 7.4 Navigation with a Gyroscope

As you (hopefully) determined in problem (2) of the prelab, the gyroscope output can be integrated to get a measure of the current angle of the robot relative to some starting point.
You are provided with a reactor `GyroAngle` in `src/lib/IMU.lf` that uses the trapezoidal method to calculate the angle.  Use this reactor to create modal Lingua Franca program that drives for approximately half a meter, turns 90 degrees, drives another half meter, and then repeats, so that the robot moves roughly in a square.  What factors contribute to the imperfection of the square?

**Checkoff:** Show your robot moving in a square and show the diagram of the modal Lingua Franca program.

## 7.5 Obstacle Avoidance

Examine the [src/BumpDisplay.lf](https://github.com/lf-lang/lf-3pi-template/blob/main/src/BumpDisplay.lf) example program provided by your template repository.
How does it work?
What does the Bump reactor class do?

Your task now is to use the [Bump](https://github.com/lf-lang/lf-3pi-template/blob/main/src/lib/Bump.lf) reactor class to modify your previous solution so that when the robot bumps into an obstacle as it navigates around the square, it backs off in such a way as to avoid the obstacle.

**Checkoff:** Show your robot evading obstacles.  Show your modal model.

## 7.6 Postlab

1. If the bump sensors fail to detect an obstacle that has stopped your robot, the robot will stop making progress because it will fail to cover the requisite distance to switch to the next mode.  How might you change your program to ensure that the robot continues to make progress?

2. Instead of setting the power level of the motors, a better strategy might be to set a desired robot speed.  How might you use the encoders to measure the speed?  How might you use the speed measurement to control the speed?  **Hint:** Section 2.4, Feedback Control, of [Lee and Seshia](https://leeseshia.org) might be useful.

3. What were your takeaways from the lab? What did you learn during the lab? Did any results in the lab surprise you?
