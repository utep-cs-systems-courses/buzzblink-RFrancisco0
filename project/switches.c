#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "statemachine.h"

char switch_state_down, switch_state_up, switch_state, switch_btn;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}

void switch_init()
{
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_update();
}


void switch_up_interrupt(char p2val)
{
  if (p2val & switch_btn)
    {
      switch_state_up = 1;
    }
}


void switch_down_interrupt(char p2val)
{
  if ((p2val & SW1) == 0)
    {
      switch_btn = SW1;
    }
  if ((p2val & SW2) == 0)
    {
      switch_btn = SW2;
    }
  if ((p2val & SW3) == 0)
    {
      switch_btn = SW3;
    }
  if ((p2val & SW4) == 0)
    {
      switch_btn = SW4;
    }

  if (switch_btn)
    {
      switch_state_down = 1;
    }
}


void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  if (switch_state_down)
    {
      switch_up_interrupt(p2val);
      led_state_update();
    }
  else
    {
      switch_down_interrupt(p2val);
    }
}
