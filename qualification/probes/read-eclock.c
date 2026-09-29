#include <exec/types.h>
#include <exec/libraries.h>
#include <devices/timer.h>
#include <proto/timer.h>
struct Library *TimerBase;
int main(void){struct EClockVal v;return ReadEClock(&v)==0;}
