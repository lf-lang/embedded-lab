# 9 Track and Line Following

The goal of this exercise is to program the Pololu robot in LF to perform track and line following, where the robot detects a line or track and follows it until it reaches the end.

For this lab, you will need a suitable line like the ones below, made using black poster chart paper (cut in the shape of the track) or black ducktape on white foam boards:

<table>
<tr>
<td><img src="img/Track_1.jpg"  alt="1" width = 360px ></td>
<td><img src="img/Track_2.jpg" alt="2" width = 360px></td>
</tr> 
<tr>
<td><img src="img/Track_3_4.jpg" alt="3" width = 360px></td>
<td><img src="img/Track_Example.jpg" alt="4" width = 360px>
</td>
</tr>
</table>

## 9.1 Prelab

<!---
NOTE: The prelabs may change according to the ordering of the lab.
-->

- Review [Section 6.5, Line and bump sensors](https://www.pololu.com/docs/0J86/6.5) of the [Pololu 3pi+ 2040 robot User's Guide](https://www.pololu.com/docs/0J86).

- Review the section for the motors from the previous lab. This lab will test you on how to adjust power to maneuver curves and sharp turns.

- Review [Line Sensing](./Hill.md#82-line-sensing). The same calibration should be done at the beginning of this exercise, however, with a small difference, explained below.
 
  For this lab, you are required to indicate where the robot is planning or programmed to move when the sensor detects an out-of-track area in order for the robot to realign itself with the track (For instance, if the right-hand-side sensors of the robot detect an out-of-track area the print on display should read "left" and vice-versa).  

**Questions**

1. Can we use the gyroscope to make the robot navigate the curves?
2. Can we use the line sensors on the edges, i.e., sensors 1 and 5, to detect angles and curves? 

## 9.2 Track Following

**Checkoff:** Calibrate your line sensors to detect the "out-of-track" area.

Write LF code to make your robot follow the designated path. The trick is to make sure the speed of the robot's motor enables it to maneuver the turns and adjust the speed of the robot if necessary.

**HINT:** 0.1f would be a reasonable starting point for the speed. You may increase or decrease the speed eventually. The goal is functionality.

You may build a track at your own home to test your code. The important thing to keep in mind is that the track must be smooth, and the robot should not get stuck somewhere in between. The key thing is that the track and the surroundings must have a significant contrast in terms of color. You are free to test your code on that track before you submit the code for it. The robot should align itself without any external help, even if it starts out skewed with respect to the track. The robot should stop at the end of the track or keep continuing if the track is a loop. You are free to include any module of your choice to make sure the robot is precise in keeping itself on track, and the robot should have enough intelligence or functionality to keep itself on track. The robot will be tested on a different track from the one you developed your code with to ensure uniformity. Please put your solution in a file called `TrackFollowSolution.lf`.

**Checkoff:** Show your robot driving to the end of the track and handling the curves smoothly.

<!---
TODO: Add a Line follower exercise too, after completing the Track follower solution.
-->

## 9.3 Postlab

<!---
TODO(@the-systematic-chaos): Need to finalize solution code, the postlab questions will be based on the final solution.
-->

1. What were your takeaways from the lab? What did you learn during the lab? Did any results in the lab surprise you?
2. What method or logic did you use to tackle curves and sharp angles during the experiment?
3. Justify or explain the logic behind choosing that particular method.
