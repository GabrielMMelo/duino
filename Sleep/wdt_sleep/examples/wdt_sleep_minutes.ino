/* 
 * AUTHOR: GABRIEL MELO  
 * DATE: 23/06/2018
 *
 * EXAMPLE CODE OF SLEEPING/SAVING POWER USING WATCHDOG TIMER FOR MINUTES
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
#define INTERVAL 8 // seconds
#define INTERVAL_WDP 0b100001 // 8 second

/* 
 * Watchdog timer interrupt handler.
 */
ISR(WDT_vect){
  // Disable timer to avoid unexpected resets
  wdt_disable(); 
}

/*  
 *   Watchdog timer register (WDTCSR)
 *   
 *  Bit | Name | Description
 *    7 | WDIF | Sets an interrupt flag
 *    6 | WDIE | Enables Interrupts
 *    5 | WDP3 | Determines how long the timer will count (MSB) 
 *    4 | WDCE | Needed to set it and WDE to HIGH before change another bits
 *    3 | WDE  | Needed to set it and WDCE to HIGH before change another bits
 *    2 | WDP2 | Determines how long the timer will count
 *    1 | WDP1 | Determines how long the timer will count
 *    0 | WDP0 | Determines how long the timer will count (LSB)
 *     
 *    By default every bit is set to 0
 *    
 *    WDP range is 16ms to 8000ms
 */ 
void setSleep(const byte interval){

  // Set 0 for all MCU status register
  MCUSR = 0;                          
  
  WDTCSR |= (1<<WDCE) | (1<<WDE); 
  WDTCSR =  (1<<WDIE) | interval;    

  wdt_reset();
  set_sleep_mode (SLEEP_MODE_PWR_DOWN); 
  
  // Go to sleep and wait for watchdog timer interrupt
  sleep_mode();            
}

void goSleep(int minutes){
  // 60-4 considering ~4 seconds/per minute delay 
  int cycles = (minutes*56)/((int)INTERVAL); 
  for (int i=0; i<cycles; i++){
    setSleep(INTERVAL_WDP);
  }
}

void setup(){
  pinMode (LED_GREEN, OUTPUT);
  pinMode (LED_RED, OUTPUT);
}

void loop(){
  // Waking up...
  digitalWrite (LED_GREEN, LOW);
  digitalWrite (LED_RED, HIGH);
  delay (2000);
  digitalWrite (LED_RED, LOW);
  digitalWrite (LED_GREEN, HIGH);
  
  // Sleeping... Time is set in minutes
  goSleep(1);
}
