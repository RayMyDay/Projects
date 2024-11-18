# README for Arduino Alarm Clock Project

## Overview
This project implements a simple alarm clock using an **Arduino**, a **DS3231 Real-Time Clock (RTC)** module, a **Liquid Crystal Display (LCD)**, and a **buzzer**. The clock displays the current time and date, allows the user to set the time and date, and can trigger an alarm at a specified time.

## Components Required
1. **Arduino Board** (e.g., Arduino Uno, Nano, etc.)
2. **DS3231 RTC Module** - for keeping track of the current time and date.
3. **16x2 LCD Display** - to display time, date, and menu options.
4. **Buzzer** - to sound the alarm.
5. **Push Buttons** - for user input (to set time, date, and alarm).
6. **Breadboard and Jumper Wires** - for connections.

## Pin Connections
### DS3231 RTC Module
- **VCC** to Arduino **5V**
- **GND** to Arduino **GND**
- **SDA** to Arduino **A4** (or the corresponding SDA pin for your board)
- **SCL** to Arduino **A5** (or the corresponding SCL pin for your board)

### 16x2 LCD Display
- **RS** to Arduino **Pin 7**
- **EN** to Arduino **Pin 8**
- **D4** to Arduino **Pin 9**
- **D5** to Arduino **Pin 10**
- **D6** to Arduino **Pin 11**
- **D7** to Arduino **Pin 12**
- **VSS** to Arduino **GND**
- **VDD** to Arduino **5V**
- **V0** (for contrast) to a potentiometer (optional) or directly to **GND**.

### Buzzer
- **Positive Pin** to Arduino **Pin 3**
- **Negative Pin** to Arduino **GND**

### Push Buttons
- **Button 1** (for incrementing values) to Arduino **Pin 6**
- **Button 2** (for decrementing values) to Arduino **Pin 5**
- **Button 3** (for navigating menus) to Arduino **Pin 4**
- Connect each button to **GND** (with a pull-up resistor if necessary).

## Functionality
- The clock displays the current time in **HH:MM:SS** format and the current date in **MM/DD/YY** format.
- The user can navigate through menus to set the current time, date, and alarm.
- When the alarm time matches the current time, the buzzer will sound for **10 seconds**.
- The user can set the alarm hour, minute, month, day, and year.

## Usage Instructions
1. **Power on the Arduino**.
2. The current time and date will be displayed on the LCD.
3. Use the buttons to navigate through the menus:
   - Set Time: Adjust hours, minutes, AM/PM.
   - Set Date: Adjust month, day, year.
   - Set Alarm: Adjust alarm hour, minute, month, day, year.
4. When finished setting the time and alarm, the clock will return to the main display.
5. The buzzer will sound when the alarm triggers.

## Notes
- The RTC module is essential for keeping accurate time even when the Arduino is powered off. Ensure the **DS3231 module** is properly connected and configured.
- The code includes a basic melody (**Jingle Bells**) that can be played using the buzzer, but this feature is not activated in the main loop.
- Debouncing is implemented to prevent multiple readings from a single button press.

## Troubleshooting
- If the display is not showing the correct time, check the connections to the RTC module.
- Ensure that the buttons are correctly connected and functioning.
- If the buzzer does not sound, verify the connection to the buzzer and check the pin configuration in the code.

This README should provide you with a clear understanding of how to set up and use the **Arduino Alarm Clock** project. Enjoy building your project!
