#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "led_dim_statemachine.h"
#include "statemachine.h"


void __interrupt_vec(WDT_VECTOR) WDT(){
  if(switch_btn == SW2 || switch_btn == SW4){
    static char blink_count = 0;
    if (++blink_count == 125) {
      led_dim_slow_clock();
      blink_count = 0;
    }
    led_dim_fast_clock();
    led_state_update();
  }
}

