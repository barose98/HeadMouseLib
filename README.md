# HeadMouseLib
An Arduino library that defines a wearable computer mouse that translates head movements to mouse movements. Originally implemented as an accessible device for disabled people who have control of their heads but for whatever reason cannot use a standard computer mouse. 
## Dependencies for Running Locally

 -  ### An Arduino-compatible microcontroller that has USB functionality built in to the hardware. 
 Currently, I use a [Trinket M0 by Adafruit](https://www.adafruit.com/product/3500) It has an ARM Cortex M0 chip, a Microchip ATSAMD21. The documentation for the Adafruit Trinket M0 can be found [here](https://learn.adafruit.com/adafruit-trinket-m0-circuitpython-arduino/overview)
 Years ago, when I first started using this device, the device I used was an 8-bit AVR. Specifically, an Atmel ATMEGA32u4 (Arduino Leonardo)  
- ### [MPU6050 breakout board](https://smile.amazon.com/dp/B07H2WHQSL/ref=cm_sw_em_r_mt_dp_U_-iO2EbJBV9KDH)

- ### [I2cDevLib](https://github.com/jrowberg/i2cdevlib) by Jeff Rowberg
For a while, my hand could point the mouse but not push the button down. I was using a [Makey Makey](https://makeymakey.com/) to perform clicks with just a light touch. 
When I lost the ability to even point the mouse. I used an assistive piece of software that used the webcam and computer vision to track head movements and move the cursor. That software took up a lot of system resources, and the computer had to have the software installed. 

I discovered [I2cDevLib](https://github.com/jrowberg/i2cdevlib)  and started to implement the HeadMouse. [I2cDevLib](https://github.com/jrowberg/i2cdevlib)  handles all the I2C communication between the microcontroller and MPU6050, as well as all the calculations to convert raw gyro and accelerometer readings into easy-to-use YawPitchRoll array of floating point values, angles in radians. 

