# 9 Line Following

The goal of this exercise is to do LF programming using the Pololu robot to execute a specified task, namely line follwoing, where the robot detects the line and follows the line until it reaches the end of line.

For this lab, you will need a suitable line like the one here:

<!---
TODO(@the-systematic-chaos): Add a picture of a line following track.
-->

## 9.1 Prelab

<!---
NOTE: The prelabs may change according to the ordering of the lab.
-->

1. Review [Section 6.5, Line and bump sensors](https://www.pololu.com/docs/0J86/6.5) of the [Pololu 3pi+ 2040 robot User's Guide](https://www.pololu.com/docs/0J86).

2. Review the section for the motors from the previous lab. This lab will test you how to adjust power to maneuver curves and sharp turns.

3. Review line sensing, the same calibration should be done at the beginning of this excersie as well. However, there is a small difference in how the sensor is calibrated.
   For this lab, you are required to indicate where the robot is going to move as the sensor moves out of the line in order for the robot to realign itself with the track.  

**Checkoff:** Calibrate your line sensors to detect the "out-of-track" area.

## 9.3 Postlab

Write LF code to make your robot follow the designated path. The trick is to make sure the robot's motor is calibrated perfectly to make the turns, adjust the speed of the robot.

**HINT:** 0.1f would be perfect to start, you may increase or decrease the speed eventually. The goal is functionality.

You may build a track at your own home, to test your code. The important thing to keep in mind is that the track must be smooth and the robot should not get stuck somewhere in between. The key thing is that the track and the surroundings must have a significant contrast in terms of the color. You are free to test your code on that track before you submit the code for it. The robot should align itself without any external help, even if it starts out skewered with respect to the track. The robot should stop at the end of the track or keep continuing if the track is a loop. You are free to include any module of your choice to make sure the robot is precise in keeping itself on track, the robot should have enough intelligence or functionality to keep itself on track. If it reaches the end of the track the robot should stop. The robot will be tested on a different track from the one you developed your code with, to ensure uniformity.

**Checkoff:** Show your robot driving to the end of the line, handling the curves smoothly.

## 9.3 Postlab

<!---
TODO(@the-systematic-chaos): Need to finalize solution code, the postlab questions will be based on the final solution.
-->

1. hat were your takeaways from the lab? What did you learn during the lab? Did any results in the lab surprise you?
