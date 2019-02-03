
Overview
--------------------------------------------
* Name: timer_arduino_two
* Title: Micro-controller Countdown Timer
* Description: Countdown Timer: Range 1-99 minutes. 
Output time (mm:ss) to seven segment display and Audio to Buzzer.
Input: Push button to start.  10K Pot used for time select.
* Author: Gavin Lyons

Software Used
------------------
Arduino 1.8.5

Eagle 9.3.0


Parts List
------------------------------
The schematic drawn in eagle is in documents section. 

You will need following parts.

>
> ATmega328p micro-controller as per schematic or alternatively a Arduino uno/nano module.
>
> Resistors: 20 ohms , 220 ohms, 660 ohms, 10K
>
> 4 digit seven segment module
>
> one 10 k potentiometer 
>
> one pushbutton
>
> One on/off SPST switches
>
> One piezo buzzer
>
> One 16 Mhz crystal
>
> One Lm317 voltage regulator
>
> Capacitors. two x 22pF, three x 100nF , 1uF
>

Features
----------------------
The user selects the countdown time (1-99 minutes) with the potentiometer  then starts with the pushbutton.
Time remaining is displayed on seven segment display. When finished the buzzer is activated and done displayed on 4 digit 7-segment display.
 
![ScreenShot schematic one ](https://github.com/gavinlyonsrepo/timer_arduino_two/blob/master/documentation/eagle/timer_arduino_two.jpg)


 
Copyright
---------
Copyright (C) 2018 Gavin Lyons 
see LICENSE.md in documentation section 
for more details

