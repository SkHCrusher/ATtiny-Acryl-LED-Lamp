# LED Acrylic Lamp Project
Welcome to the LED Acrylic Lamp project repository! This project features Arduino code optimized for an Attiny412 microcontroller along with a WS2812 LED strip, creating a mesmerizing LED acrylic lamp.

[BILD]

## Features
- **Attiny412 Optimization**: The Arduino code is tailored specifically for the Attiny412 microcontroller, ensuring efficient performance.
- **WS2812 LED Strip Integration**: The project incorporates a WS2812 LED strip for vibrant and customizable lighting effects.
- **Custom 3D Printed Base**: The lamp's base is 3D printed, with files available here
- **Custom PCB Design**: We've designed a dedicated PCB for this project, featuring the Attiny412 microcontroller, LED strip connector, two buttons for mode and color/animation speed selection, and three pins for UPDI programming.

## Preparation
Before you can get started, make sure that you have organized or completed all of the following points.

### Order the custom PCB
I created the board with the Easy EDA Editor and released the whole project:
https://oshwlab.com/crusher/led-acryl-lightning-board-v3-attiny412-sk

Here you can find all plans, a list of required components etc. 
You can also use the editor to order the board directly from JLCPCB in just a few clicks.

**Alternative:**
You can also rebuild the circuit without the PCB. In this case, only the 3D printed housing will no longer fit. 

### LED light strips
I used a WS2812B LED strip with 60 LEDs / meter, SMD5050 LEDs and with protection class IP30 for the project.

The number of LEDs was optimal for me, so that the lamp is bright enough, but not too bright.
IP30 is sufficient, as we are indoors here.

### Print base using 3D printing
I have published the 3D print files on Printables.com. In the current version there is a base for an 8cm and a 15cm wide acrylic disk.
Download the files and print them out on your printer. I used the Galaxy Black PLA material from Prusa here.

### Acrylic pane lasering
Choose a motif for your acrylic pane and laser it.
I have attached two example files to the project. One for the 8cm and one for the 15cm version

### Development environment
The Arduino project was created with Platform.io. Install the Visual Studio code editor together with Platform.io so that you can compile the code and upload it easily.

Here is an official guide for the installation: https://platformio.org/install

### Build UDPI programmer
There are several ways to load the code onto the ATtiny412 via UDPI. I got along well with the following instructions; https://mp1993.de/diy-updi-programmer-for-mega-4808/

### Miscellaneous
The following items are also required:

- 1 x M2 6mm screw
- USB-C cable 

## Getting started
Now you can transfer the code to the circuit board and assemble the lamp.

### Upload code
1. Clone this repository to your local machine.
2. Open the project folder in PlatformIO IDE.
3. Connect your computer to the UDPI programmer
4. Connect the UDPI programmer to your custom PCB
5. adjust the COM port under “[env:Upload_UPDI]”
6. Upload the code via the “env:Upload_UDPI” environment

### Assembling
After the circuit board has been recorded, you can assemble your lamp in the following steps:

#### Gluing in LED strips
The LED strip is glued onto the mounting plate in the desired length.
The 8cm version has 5 LEDs, the 15cm version has 9 LEDs.

[Bild]

#### Connect circuit board and LED strip via cable
The LED strip must be connected to the circuit board so that it can also receive power and data. I have used a 3-pole LED cable for this.
The cable length for the 8cm version is 9cm and for the 15cm version 16cm.
Pay attention to the correct polarity when soldering.

[BILD]

#### Secure the circuit board
To prevent the circuit board from flying around loosely in the housing, it is fixed in place with a 3D printed part. 
The 3D printed part also supports and secures the buttons before they are pressed into the housing.
Fitted the block with an M2 screw with a length of 6mm.
[Bild]

#### Plug the housing together
At the end, the housing can simply be plugged together in the correct order. 
Thanks to the lugs in the 3D print, the lid holds securely to the base and does not slip away easily.

#### Insert the acrylic panel
Finally, the acrylic panel can be carefully inserted into the slot at the top.
If the disk cannot be inserted, simply grind away some material on the sides and try again.

## Usage
As soon as you connect the Lample via USB-C cable, it lights up immediately.
You can set the mode with the first button. Use the second button to set the color or animation speed.

The following modes are currently included:
- Solid color
- Rainbow 
