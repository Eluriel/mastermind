#include <ArduinoSTL.h>

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/atomic.h>

volatile uint32_t seed; // These two variables can be reused in your program after the
volatile int8_t nrot; // function CreateTrulyRandomSeed()executes in the setup()
                     // function.
 
void CreateTrulyRandomSeed()
{
seed = 0;
nrot = 32; // Must be at least 4, but more increased the uniformity of the produced
// seeds entropy.
// The following five lines of code turn on the watch dog timer interrupt to create
// the seed value
cli();
MCUSR = 0;
_WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (1<<WDE);
_WD_CONTROL_REG = (1<<WDIE);
sei();
 
while (nrot > 0); // wait here until seed is created
 
// The following five lines turn off the watch dog timer interrupt
cli();
MCUSR = 0;
_WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (0<<WDE);
_WD_CONTROL_REG = (0<< WDIE);
sei();
}
 
ISR(WDT_vect)
{
nrot--;
seed = seed << 8;
seed = seed ^ TCNT1L;
}

void setupSeed()
{
    CreateTrulyRandomSeed();
    randomSeed(seed);
    // The preceeding two function calls will take approximately 0.5 second to execute if
    // nrot is set to 32 ... the rest of your setup code should FOLLOW from here.
}