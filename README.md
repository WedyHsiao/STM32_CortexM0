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
- V03
  - Modified the HID descriptor to complient-vendor defined device
  - Modified the PID/VID
  - Add the print log via UART function (115200)
- V04
  - Add the program to receive the out put data sent from PC
  - Modified UX_DEVICE_CLASS_HID_EVENT_BUFFER_LENGTH from 32 to 256
  - Modified UX_SLAVE_REQUEST_DATA_MAX_LENGTH from 64 to 256
  - Could receive the output report but just could print data_len [31] each time, wait for investigate
- V05
  - Add USBX_DEVICE_HID_CUSTOMER_Task()
  - Add USBD_HID_Keyboard_SendReport
- V06
  - Set up the flash erase and write data
    - https://youtu.be/BKgh896Bj8Q?si=VTTekKFrIjBoG6fc
  - Modified the Output report length in hid descriptor
  - USB FS packets are max 64 bytes in length. I assume the 32-byte packet size is some subset of those 64 bytes, probably HID-specific.
    - https://community.st.com/t5/stm32-mcus-embedded-software/the-maxium-length-of-buffer-for-usb-hid-setreport/m-p/801757#M63342
- V07
  - Modified the length of output report size
    - The STM32U083 typically programs 64 bits (8 bytes) at a time, using “double-word” programming.
    - You can’t write 100 bytes directly in a single command — you must program it in 8-byte “double-word” chunks.
  - Revised the usage flash address based on program size and usage data length
  - Add the read flash data function  