/* 
 * AUTHOR: GABRIEL MELO  
 * DATE: 23/06/2018
 *
 * EXAMPLE CODE OF SLEEPING / SAVING POWER USING WATCHDOG TIMER
 * 
 * NOTE: Watchdog timer isn't accurate. Be carefull to use it on precision projects needed
*/

/* 
 * Library for power Management and Sleep Modes 
 */
#include <avr/sleep.h>

/* 
 * Library to access watchdog timer functions and register into your code 
 */
#include <avr/wdt.h>

/* 
 * 'Debug' LEDS 
 */
#define LED_GREEN 11
#define LED_RED 10

/* 
 * Set timer interval 
 */
#define INTERVAL_WDP 0b100000 // 2 second

/* 
 * Watchdog timer interrupt handler.
 */
ISR(WDT_vect){
  // Disable timer to avoid unexpected resets
  wdt_disable(); 
}

void goSleep(int minutes);

void setSleep(const byte interval);

int convertStrToInt(char* time);
