# RoboCar
My Project to create a robot car with a camera. <b> This is work in progress.</b>

# Basic setup: Raspberry Pi robot car with camera
## Hardware:
* Joy-IT chassis, wheels and electrical motors. You can find an example [https://www.conrad.nl/p/joy-it-arduino-robot-car-kit-01-robot03-robot-chassis-1573542 here] (Dutch website)
* Raspberry Pi and L298N motor bridge.
* a PiCamera with camera ribbon. Preferably a PiCamera holder.
* a powerbank/5V battery to power the raspberry
* a 9V battery for the engines. Connect the 9V battery to the engine with a a cable like [https://www.conrad.nl/p/beltrona-9v-i-clip-batterijclip-1x-9v-blok-drukknopaansluiting-l-x-b-x-h-26-x-13-x-8-mm-624691?searchTerm=9v%20&searchType=suggest&searchSuggest=product] You can also use more Volt. A lower voltage is not recommended.
* jumper wires 
* a laptop or tablet with VNC installed to control the car (see below for VNC)

## Software
In this project the following python modules are used:
* gpiozero - to control the engines. Find the documentation at [https://gpiozero.readthedocs.io/en/stable/api_boards.html#robot]
* Pynput - for keyboard input/commands. Find the documentation at [https://pynput.readthedocs.io/en/latest/keyboard.html]
* use PiCamera - to control the camera. Find the documentation at [https://picamera.readthedocs.io/en/release-1.13/]
* We also use the time.sleep module. 

### VNC
Use this [https://www.raspberrypi.org/documentation/remote-access/vnc/] tutorial to install VNC on both your device and the Pi. Make sure you have an account and are logged in on both devices.

For this project we use VNC because it has a low latency. I've also tried VLC, but with VLC latency was about 2-3s which is too much for our purpose.

## Wiring / set up:

Steps:
* First connect the engines to the LN298 motor shield. 
* Next, connect the camera to the Raspberry.
* Third connect the battery for the engine and the battery for the Raspberry.

Install the python script on your raspberry. Start VNC from your laptop/tablet and make a connection with the raspberry. Run the script. You can use your keyboard (with keys f, b, l,r) to control the car. Have fun! 

# Advanced:

## Line following
We use TCRT5000 sensor for line following. 

## OpenCV on RPi with Haar Transformations to detect a STOP-sign
See my tutorial for OpenCV.
More to follow.
