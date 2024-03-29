#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "statemachine.h"

void main(void)
{
  configureClocks();
  buzzer_init();
  switch_init();
  led_init();

  enableWDTInterrupts();


  or_sr(0x18);
}

