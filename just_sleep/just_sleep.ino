#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

void setup() {
  // put your setup code here, to run once:
  ADCSRA &= ~(1 << ADEN);
}

void loop() {
  // put your main code here, to run repeatedly:

 noInterrupts();  // to disable interrupts

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // PowerDown - самый экономный режим
  sleep_mode();    
}
