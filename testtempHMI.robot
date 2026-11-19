*** Settings ***
Documentation     Operator-assisted verification of the Temperature Monitoring HMI (ATmega328P, LM35, 16x2 LCD, 2 buttons, buzzer).
...               The operator observes the physical LCD and buzzer, then clicks PASS or FAIL in the dialog.
...               Firmware facts used by these tests (from main.ino, buttons.ino, io.ino, adc.ino):
...               - Initial limits: Low = 20, High = 35. LCD row 2 format is "L:<low> H:<high>".
...               - LCD row 1 format is "Temp: <value> C". Display refresh period is about 300 ms.
...               - Temperature = ADC * 500 / 1024 (LM35 on ADC0, 5 V reference).
...               - Buzzer (PB2) is ON when temperature < Low or temperature > High.
...               - High button (PB0) and Low button (PB1) are active-low with debounce, one increment per press.
Library           Dialogs
Suite Setup       Log    Check that the Arduino, LCD, LM35, buttons and buzzer are connected and powered.
Suite Teardown    Log    Test session completed.

*** Test Cases ***
TC01 - Startup Message Is Displayed
    [Documentation]    After power-up, the LCD shows "Temperature HMI" on row 1 and "System Ready" on row 2.
    [Tags]    display    startup
    Execute Manual Step    Reset the board.\nDoes row 1 show "Temperature HMI" and row 2 show "System Ready"?

TC02 - Temperature Reading Is Displayed
    [Documentation]    Verify that row 1 shows a temperature value and the Celsius unit after startup.
    [Tags]    display    temperature
    Execute Manual Step    Look at row 1 of the LCD.\nDoes it show "Temp:" followed by a number and "C"?

TC03 - Initial Limits Are Displayed
    [Documentation]    After a reset, row 2 shows the initial limits "L:20 H:35".
    [Tags]    display    limits
    Execute Manual Step    Reset the board and wait for the startup screen to finish.\nDoes row 2 show "L:20 H:35"?

TC04 - High Limit Button Increments Upper Limit
    [Documentation]    Press the high-limit button (PB0) once and verify H increases by one.
    [Tags]    buttons    limits
    Execute Manual Step    The upper limit (H) should show 35.\nPress and release the HIGH button once.\nDoes H now show 36?

TC05 - Low Limit Button Increments Lower Limit
    [Documentation]    Press the low-limit button (PB1) once and verify L increases by one.
    [Tags]    buttons    limits
    Execute Manual Step    The lower limit (L) should show 20.\nPress and release the LOW button once.\nDoes L now show 21?

TC06 - Buzzer Activates Below Lower Limit
    [Documentation]    Cool the LM35 (or lower the ADC0 input) so temperature < L and verify the buzzer is ON.
    [Tags]    buzzer    alarm
    Execute Manual Step    Cool the sensor so the temperature is below L.\nIs the buzzer ON?

TC07 - Buzzer Activates Above Upper Limit
    [Documentation]    Warm the LM35 (or raise the ADC0 input) so temperature > H and verify the buzzer is ON.
    [Tags]    buzzer    alarm
    Execute Manual Step    Warm the sensor so the temperature is above H.\nIs the buzzer ON?

TC08 - Buzzer Is Off Within Limits
    [Documentation]    Verify the buzzer is off when L <= temperature <= H.
    [Tags]    buzzer    alarm
    Execute Manual Step    Keep the temperature between L and H.\nIs the buzzer OFF?

TC09 - Lower Limit Cannot Reach Upper Limit
    [Documentation]    Press the low-limit button repeatedly. L must always stay strictly below H (it must stop at 34 when H is 35).
    [Tags]    buttons    limits    boundary
    Execute Manual Step    Press the LOW button repeatedly until it stops changing (H is 35).\nDoes L stop at 34 and stay below H?

TC10 - Upper Limit Does Not Exceed 99
    [Documentation]    Press the high button repeatedly and verify the maximum is 99.
    [Tags]    buttons    limits    boundary
    Execute Manual Step    Press the HIGH button repeatedly until it stops changing.\nDoes H stop at 99?

TC11 - Buzzer Is Off Exactly At Limit Values
    [Documentation]    The alarm condition is strictly "< L" or "> H". Verify the buzzer stays OFF when the temperature equals L, and when it equals H.
    [Tags]    buzzer    alarm    boundary
    Execute Manual Step    Adjust the limits or the temperature so that temperature equals L, then equals H.\nIs the buzzer OFF in both cases?


TC12 - Holding A Button Counts As One Press
    [Documentation]    Hold the HIGH button for about 2 seconds, then release. buttons.ino waits for release, so the limit must increase by exactly one.
    [Tags]    buttons    debounce
    Execute Manual Step    Note the upper limit (H), for example 35.\nHold the HIGH button for about 2 seconds, then release it.\nDid H increase by exactly 1 (for example to 36)?
