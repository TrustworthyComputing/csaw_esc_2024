## Hardware Test Files

These programs can be used to test the hardware. 
A short video with assembly instructions for the ESC hardware is available [here](https://drive.google.com/file/d/1DRpB7Qy6YpE_sjXaRERW-EI_ULjzWqRX/view?usp=drive_link).

> Please note: It is important to **never** connect the 12 Volt power supply to the Arduino board while it is connected to a computer via USB -- this will damage the computer port!
> 
> Instead, the stripped wires of the power supply should only be connected to power port of motor shield (with the jumper removed) as shown in the video tutorial.

### Motor Test

In this test, the servo and stepper motors will move back and forth 40 times, while the DC motor will pulse on and off. After the 40 iterations, the motors will turn off. 
The servo motor is connected to Servo2 for this test. 

The Serial port, with a baud rate of 115200, will print out messages at the beginning and end of the motor test.
