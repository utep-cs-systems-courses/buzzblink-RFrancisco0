#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

static unsigned int period = 1000;
static signed int rate =250;

#define MIN_PERIOD 1500
#define MAX_PERIOD 5000

void buzzer_init()
{
  timerAUpmode();/*to use speaker */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;/* (P2.6) */

  buzzer_advance_frequency();/* buzzing sound */
}

void buzzer_advance_frequency()
{
  period += rate;
  if ((rate > 0 && (period > MAX_PERIOD)) ||
      (rate < 0 && (period < MIN_PERIOD))) {
    rate = -rate;
    period += (rate << 1);
  }
  buzzer_set_period(period);
}

void buzzer_set_period(short cycles)
{
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}
