# Temperature Monitoring HMI

## 1. Introduction

This project implements a temperature-monitoring Human Machine Interface using an ATmega328P-based Arduino UNO board. An LM35 temperature sensor provides an analogue voltage that is converted into a digital value by the microcontroller's ADC. A 16×2 LCD displays the measured temperature and the configured lower and upper limits. Two push buttons allow the user to increase the limits, and an active buzzer provides a warning if the temperature goes outside the allowed range.

The software is divided into small modules for ADC, LCD, buttons, and buzzer I/O.

## 2. Project Code

The project source code and header files are available in the repository's main directory.

**Main Program**
- [Main Program](main.ino)

**ADC Files**
- [ADC Source File](adc.ino)
- [ADC Header File](adc.h)

**LCD Files**
- [LCD Source File](lcd_.ino)
- [LCD Header File](lcd.h)

**Buttons Files**
- [Buttons Source File](buttons.ino)
- [Buttons Header File](buttons.h)

**I/O Files**
- [I/O Source File](io.ino)
- [I/O Header File](io.h)

**GitHub repository:** [HMI_TEMP](https://github.com/alielwan52006/HMI_TEMP)

**Local source directory:** `./`

> Coursework requirement: Use native C and direct AVR register access. The implementation files currently use the `.ino` extension. For a strict native-C submission, confirm the coursework build requirements and compile the source as C files with AVR-GCC rather than as an Arduino sketch. Do not add Arduino libraries if the assignment prohibits them.

## 3. Test Cases

The Robot Framework test procedure is available here:

[Test Cases](testtempHMI.robot)

The tests are operator-assisted. The demonstrator observes the physical LCD and buzzer and records whether each test passes or fails. They are not automatic electrical measurements. Run them with Robot Framework and its Dialogs library available.

## 4. Bill of Materials

- [Bill of Materials](BOM%20hmi.csv)
- [Optimized Bill of Materials](OBOM%20hmi.csv)

Prices and supplier details should reflect the parts and quotations actually used by the group.

## 5. Video Demonstration

The following video demonstrates the operation of the Temperature Monitoring HMI project.

[Watch Project Demonstration](video.mp4)

## 6. Detailed Design

See the [Detailed Design Document](project_design_tpl.md).

## Hardware pin mapping

| Function | Arduino UNO pin | ATmega328P signal |
|---|---:|---|
| LM35 output | A0 | ADC0 / PC0 |
| LCD RS | D2 | PD2 |
| LCD Enable | D3 | PD3 |
| LCD D4–D7 | D4–D7 | PD4–PD7 |
| Increase upper limit | D8 | PB0 |
| Increase lower limit | D9 | PB1 |
| Active buzzer control | D10 | PB2 |

The LCD uses 4-bit parallel mode. Its RW pin is connected to GND. The buttons are wired between their input pins and GND and use the ATmega328P internal pull-up resistors.

## Important implementation notes

- The temperature conversion assumes a 5.0 V ADC reference and an LM35 sensitivity of 10 mV/°C.
- The default limits in the uploaded main program are 20°C and 35°C.
- The active buzzer is switched on when the temperature is below the lower limit or above the upper limit.
- The uploaded main program allows the lower limit to increase up to the upper limit. Check this behaviour against the coursework requirement and update the test procedure if the lower limit must remain strictly below the upper limit.
- Verify the current requirement of the buzzer. Use a transistor driver if it exceeds what a microcontroller pin can safely drive.
- Connect the LCD backlight according to the module's resistor arrangement and datasheet.
