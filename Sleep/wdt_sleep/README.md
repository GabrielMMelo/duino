# Sleeping & Saving Power using watchdog timer

Some Arduino codes examples using `sleep.h` and `wdt.h` libraries

## Technologies used

- ATMEGA328p
- IDE ARDUINO
- LED RGB
- SOME RESISTORS

## Circuit

![alt text](https://github.com/GabrielMMelo/duino/blob/master/Sleep/wdt_sleep/doc/img/circuit.png "Circuit!")

## What's happening?

The watchdog timer is usually used to prevent unexpected long loops. It's also used for <strong> preset periods interrupt</strong>.

In [this](https://github.com/GabrielMMelo/duino/blob/master/Sleep/wdt_sleep/examples/wdt_sleep_blink.ino) example, we used it for take the atmega328 to sleep while this is waiting for a wdt interrupt.

![alt text](https://github.com/GabrielMMelo/duino/blob/master/Sleep/wdt_sleep/doc/img/blink.gif "Blinking green while it's sleeping")

### Program flow

1. When MCU <strong>wake up</strong> (including when its boots on first time), the LED blinks RED.
2. So, we delay 2 seconds and reset wdt, configured for 4 seconds timer. While it's <strong>sleeping</strong>, the LED blinks GREEN.
3. Finally, when interrupt rises, we disable wdt and repeat all.

### WDTCSR 

| Bit | Name | Description |
| --- | --- |--- |
| 7 | WDIF  | Sets an interrupt flag |
| 6 | WDIE | Enables Interrupts |
| 5 | WDP3 | Determines how long the timer will count (*MSB*) |
| 4 | WDCE | Needed to set it and WDE to HIGH before change another bits |
| 3 | WDE | Needed to set it and WDCE to HIGH before change another bits |
| 2 | WDP2 | Determines how long the timer will count |
| 1 | WDP1 | Determines how long the timer will count |
| 0 | WDP0 | Determines how long the timer will count (*LSB*) |


#### WDP count
| WDP3 | WDP2 | WDP1 | WDP0 | Time-out (_ms_) |
| --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 16 |
| 0 | 0 | 0 | 1 | 32 |
| 0 | 0 | 1 | 0 | 64 |
| 0 | 0 | 1 | 1 | 125 |
| 0 | 1 | 0 | 0 | 250 |
| 0 | 1 | 0 | 1 | 500 |
| 0 | 1 | 1 | 0 | 1000 |
| 0 | 1 | 1 | 1 | 2000 |
| 1 | 0 | 0 | 0 | 4000 |
| 1 | 0 | 0 | 1 | 8000 |

