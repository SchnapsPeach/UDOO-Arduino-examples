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
#include <Bounce.h>

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

/* define pin for LED  */
int ledPin = 8;
/* define pin for button */
int buttonPin = 2;
/* button state to be saved in */
int buttonState = 0; 
/* previous button state */
int prevButtonState;
/* counter, counts the button pushes */
int counter = 0;
/* time to wait 10ms */
int ttw = 10;
/* Bounce Object
 * alternate code with bounce librarie
Bounce bounce = Bounce();
*/

void setup() {
	/* configure ledPin as  output */
	pinMode(ledPin, OUTPUT);
	/* configure buttonPin as input */
	pinMode(buttonPin, INPUT);
	/* activate the internal pull up resistor */
	digitalWrite(buttonPin, HIGH);
	
	/*
 	 * alternate code with bounce librarie
	bounce.attach(buttonPin);
	bounce.interval(ttw);
	 */
}

void loop() {
	/* read the button state */
	buttonState = digitalRead(buttonPin);

	/* if button state changed */
	if (prevButtonState != buttonState) {
		/* and if button is pushed */
		if (LOW == buttonState) {
			/* increment counter */
			counter++;
		}
	}
	/* remember previous state */
	prevButtonState = buttonState;
	

	/* if the counter is even turn the LED on */
	if (0 == (counter % 2)) {
		digitalWrite(ledPin, HIGH);
	} else {
		digitalWrite(ledPin, LOW);
	}
	/* wait 10ms */
	delay(10);

	/*
 	 * alternate code with bounce librarie
	bounce.update();
	buttonState = bounce.read();

	if (LOW == buttonState) {
		digitalWrite(ledPin, HIGH);
	} else {
		digitalWrite(ledPin, LOW);
	}	
	*/
}

