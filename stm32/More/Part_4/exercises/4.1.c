/*
EX-4.1 [E] — Flash and Verify
1. Copy the blink from section 4.1 exactly into src/main.c.
Build and flash. Verify: LED blinks at 1 Hz.
2. Change the timing so the LED blinks at 2 Hz.
(2 blinks per second = 250 ms ON, 250 ms OFF)
Flash. Verify with a clock.
3. Change to: 50 ms ON, 1000 ms OFF.
Describe what this looks like visually.
4. Add the UART code from section 4.3.
Wire PA9 to your USB-serial adapter.
Open serial monitor at 115200.
Verify: "LED ON" and "LED OFF" messages appear at the right times.
5. What is the value of HAL_GetTick() one minute after startup?
How did you determine this without a calculator?
*/

