// DS1302:  RST pin    -> Arduino Digital 2
//          DATA pin   -> Arduino Digital 3
//          CLK pin  -> Arduino Digital 4

#include <DS1302.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include "wdt.hpp"

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Valor (em horas) que define os horários para o arduino acordar/dormir
uint8_t hora_dormir = 8;
uint8_t hora_acordar = 20;
boolean flag = false;

DS1302 rtc(2, 3, 4);


void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  
  // Setup LCD to 16x2 characters
  lcd.begin(16, 2);

  // The following lines can be commented out to use the values already stored in the DS1302
//rtc.setDOW(THURSDAY);        // Set Day-of-Week to FRIDAY
//rtc.setTime(9, 4, 0);     // Set the time to 12:00:00 (24hr format)
//rtc.setDate(6, 9, 2018);   // Set the date to August 6th, 2010
}

void loop()
{
  char* time = rtc.getTimeStr();
  int hora_atual = convertStrToInt(time);
  // Display time centered on the upper line
  lcd.setCursor(4, 0);
  lcd.print(time);
  
  // Display abbreviated Day-of-Week in the lower left corner
  lcd.setCursor(0, 1);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  
  // Display date in the lower right corner
  lcd.setCursor(6, 1);
  lcd.print(rtc.getDateStr());

  // Wait one second before repeating :)
  delay (1000);
  
  // Estratégia: converter o valor (string) retornado por rtc.getTimeStr() para um int(hora) 
  if (flag){
    // vai estar acordado, realizando as suas tarefas
    // ...
    // SUAS COISAS
    // ...
    if (hora_atual == hora_dormir) {
      flag = false;
    }
  } 

  // Compara se hora_acordar - hora_atual > 1 
  else if(hora_acordar - hora_atual > 1){
    // dorme 30 minutos (ou algo próximo a isso)
    goSleep(30);
  }
  
  // Se hora_acordar - hora_atual == 1
  else if(hora_acordar - hora_atual == 1){
    // dorme 5 minutos (ou algo próximo a isso)
    goSleep(5);
  }
 
  else {
    flag = true;
  }
}
