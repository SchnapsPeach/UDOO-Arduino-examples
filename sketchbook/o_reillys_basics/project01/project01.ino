/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define ARDUINO_MAIN
#include "Arduino.h"

/*
 * Cortex-M3 Systick IT handler
 */
/*
extern void SysTick_Handler( void )
{
  // Increment tick count each ms
  TimeTick_Increment() ;
}
*/

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{
	init();

	delay(1);

#if defined(USBCON)
	USBDevice.attach();
#endif

	setup();

	for (;;)
	{
		loop();
		if (serialEventRun) serialEventRun();
	}

	return 0;
}

/* choose port 13 */
int ledPin = 13;

void setup() {
	/* configure port as output */
	pinMode(ledPin, OUTPUT);
}

void loop() {
	/* define duty cycle: D = T/P
	 * with:
     * T = time the signal is active
     * P = total period of the signal
     * 
     * in this example:
     * D = 500ms / 1500 ms = 0.3333
     */
	int active = 500;			/* T   */
	int inactive = 1000;		/* P-T */

	digitalWrite(ledPin, HIGH); /* turn the LED on */
	delay(active);				/* let it burn for _active_ seconds */
	digitalWrite(ledPin, LOW);  /* turn the LED off */
	delay(inactive);			/* let it off for _inactive_ seconds */
}
