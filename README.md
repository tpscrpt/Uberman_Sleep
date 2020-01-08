## Outline

I need a solution for sleeping X number of minutes, as precisely as 
possible.

Based on [research](https://academic.oup.com/sleep/article/42/12/zsz180/5549536) performed by University of Michigan, it seems that a 
Logistic Regression model will be able to give accurate enough 
sleep/wake scoring with heart rate and motion sensors.

There is no suitable consumer application which I believe would do a 
good job for someone who is trying to experiment with their sleep 
schedule. For example, the above research also only involved people who 
slept between 10pm and 8am approximately.

While the research demonstrates that a MLP (Multi-layer perceptron) 
neural net is the most effective in terms of accuracy (scoring sleep), 
the logistic regression model they used is promising enough that it is 
plausible that a MLP would be overkill for this application.
	Also, I would like to fit the entire application on the flash ROM and 
SRAM offerred by a Cortex-M4 based microcontroller. This means I have 
around 1-2MB of application code storage and 640-1000KB of RAM to 
accomplish this task.

## Tech

For all of the application code, including reading and processing data 
from the sensors present on the device, I will write C code due to its 
low memory footprint and overall support for embedded applications.

The code will be first developed and tested on my host machine with data 
gathered from a cheap smartwatch, until I need to further simulate 
interactions between the product's components. Simulation will be done 
using the GNU MCU Eclipse platform, which includes virtual development 
boards for testing and facilities to flash app code onto actual 
development boards.

More likely than not, the above choice will restrict the make of the 
microcontroller I choose; most of the support in GNU MCU Eclipse is for 
STM32 microcontrollers. All the different makes use different pins for 
specialized functions and it would make the most sense to take the 
microcontroller I have used in simulations and plop it onto my physical 
prototype.

When I'll have a sizeable amount of application code written and tested 
with simulation, I'll get myself a development board (looking at 
STM32F4-DISCOVERY for its power supply capabilities and IO 
expandability). The dev board will allow me to wire up other components, 
like the heart rate sensor, manually and test them in a real world 
scenario.

With physical testing, I'll have a better understanding of where to put 
which components and how to interact with them in software. This will 
help me draw the schematic and lay out the PCB for the prototype, which 
I'll do using KiCAD.

At that point, a lot of review and changes will have to be done.

When I've refined the prototype and I'm happy with the functionality, I 
will design an enclosure for it and 3D print it for testing. I'm 
thinking of using FreeCAD for the enclosure, but I could get away with 
using SolidWorks or some similar program.

## If you like lists

Alrighty. Developing System Code for a MCU you have never owned a board 
for is not the easiest.

The best solution I've found goes as follows:
 - Develop application code and test on host machine
 - Load hello_world sample on Eclipse MCU with STM32F4DISCOVERY board emulation
 - Remove hello_world code and insert application code
 - Run simulations, debug
 - Evaluate resource necessities of application code
 - Get STM34F4DISCOVERY board
 - Run and debug basic application code on eval board
 - Order peripherals from digikey (vibmot, piezo, sensors)
 - Practice tickling the eval board's jimmies to get a feel for 'em
 - Receive the board and begin developing peripheral code
 - Notice that it's really hard to manage interrupts at that scale
 - Contemplate learning ins and outs of FreeRTOS
 - Write more peripheral code and begin succeeding at data flow
 - Make sure you've been wearing your aliexpress smartwatch for data
 - Go back in the past and write an Android app to save watch's data
 - Refine machine learning model with Android data
 - Change application code, upgrade peripheral code
 - Test data collection and execution of the watch's data to test memory
 - Develop exotic features of the product
 - Refine the schematic
 - Simulate and fail multiple times cause you suck at electrical engineering
 - Eventually think you're on the right path
 - PCB conversion takes a lot of time, mainly because you're scared
 - Eventually get the guts to order a custom PCB prototype, likely from China
 - You actually have to sodder your components in place
 - Verify that everything works with the prototype, just like eval board
 - Probably won't, so keep debugging and ordering more
 - Meanwhile you've been designing and enclosure for the product
 - Develop a mechanical engineering testing pipeline
 - Use the pipeline to test whether the enclosure does the job
 - Refine the enclosure, add detail, artwork, customizations
 - Put the best version of PCB prototype into the enclosure
 - Test in real life
 - Fail and debug a few more times
 - Succeed
