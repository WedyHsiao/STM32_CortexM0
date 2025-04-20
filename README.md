# STM32_CortexM0 #
Playground for STM32 U083

### What is this repository for? ###

- V00
  - Set up project for STM32U083HCY
- V01
  - Set up GPIO Output and Input
  - Monitor the Input pin status to control the Output pin status
- V02
  - Set up USB Device be detected
	- Reference from the website https://youtu.be/KTI1nCrSEYg?si=9t70TrZCRBbHARh5
  - Change the system Clock setting
	- CRC SYNC set to use USB as source
	- Change the system Clock MUX to MSI with SYSCLK 48MHz
	- USB CLOCK MUX set to use HSI48
  - Monitor the Input pin status to enable the USB device process
	- When PA15 or PA12 has input signal the LED8 and LED5 would be turn on and start the USBX device process