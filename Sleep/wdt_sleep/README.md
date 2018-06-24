# Sleeping & Saving Power using watchdog timer (wdt)

Some Arduino codes examples using <i>sleep.h</i> and <i>wdt.h</i> libraries

## Technologies used

- ATMEGA328p
- IDE ARDUINO
- LED RGB
- SOME RESISTORS

## Circuit

## What's happening?

The watchdog timer is usually used to prevent unexpected long loops. It's also used for <strong> preset periods interrupt</strong>.

In [this](https://github.com/GabrielMMelo/duino/blob/master/Sleep/wdt_sleep/examples/wdt_sleep_blink.ino) example, we used it for take the atmega328 to sleep while this is waiting for a wdt interrupt.

![alt text](https://github.com/GabrielMMelo/duino/blob/master/Sleep/wdt_sleep/doc/img/blink.gif "Blinking green while it's sleeping")

When MCU <strong>wake up</strong> (including when its boots on first time), the LED blinks RED. So, we delay 2 seconds and reset wdt, configured for 4 seconds timer. While it's <strong>sleeping</strong>, the LED blinks GREEN. When interrupt rises, we disable wdt and repeat all.