#include <exec/types.h>
#include <devices/timer.h>
#include <proto/timer.h>
int main(void){struct EClockVal v;return ReadEClock(&v)==0;}
