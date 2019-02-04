
Overview
--------------------------------------------
* Name: timer_arduino_two
* Title: Micro-controller Countdown Timer
* Description: Countdown Timer: Range 1-99 minutes. 
Output time (mm:ss) to seven segment display and Audio to Buzzer.
Input: Push button to start.  Potentiometer  used for time select.
* Author: Gavin Lyons


libraries 
--------------------

None


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
> 4 digit seven segment module  (SMA420564)
>
> one 50 k potentiometer 
>
> one pushbutton
>
> One on/off SPST switches
>
> One piezo buzzer passive
>
> One 16 Mhz crystal
>
> One Lm317 voltage regulator
>
> Capacitors. two x 22pF, three x 100nF , 1uF
>

Features
------------------------
The user selects the countdown time (1-99 minutes) with the potentiometer then starts with the pushbutton.
Time remaining is displayed on seven segment display. When finished the buzzer is activated and Zero displayed on 4 digit 7-segment display for a few minutes, The unit then shuts off  display and buzzer.
 

LED Array Pin Layout

| Pin Uno | Pin Atmega  | 7 Segment pin  |   
| --- | --- | --- | --- |
|  D2 |  PD2 | a  |  
|  D3 |  PD3 | b  |   
|  D4  | PD4  | c  |    
|  D5 |  PD5 |  d |   
| D6  |  PD6 |  e |     
|  D7 |  PD7 | f  |  
| D8  | PB0  |  g |     
|  n/c |  n/c | p |       
| D10  | PB2  |  d4 |   
| D11  | PB3  |  d3 |   
| D12  | PB4  |  d2 |  
| D13  | PB5  |  d1 |     
 

The 4-digit seven segment display (SMA420564 or SM420564) is a common-cathode display.  
4 Digit 7 Segment Cathode Red LED Display 0.56" SM420564. 

![ScreenShot seven segment ](https://github.com/gavinlyonsrepo/timer_arduino_two/blob/master/documentation/image/7segpinout.png)
 
 
Schematic
---------------- 

![ScreenShot schematic one ](https://github.com/gavinlyonsrepo/timer_arduino_two/blob/master/documentation/eagle/timer_two_arduino.png)


Copyright
---------
Copyright (C) 2018 Gavin Lyons 
see LICENSE.md in documentation section 
for more details

