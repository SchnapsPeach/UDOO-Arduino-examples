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

/* define pin for LED, which blinks  */
int ledPinBlink = 13;
/* define pin for LED, which is controlled by the button */
int ledPinButton = 10;
/* define pin for button */
int buttonPin = 8;
/* button state to be saved in */
int buttonState; 
/* interval 2 sec */
int interval = 2000;
/* time of previous toggle */
int prev;
/* status of the blinking LED */
int ledBlinkState = LOW;
/* status of the button LED */
int ledButtonState = LOW;

void setup() {
	/* configure ledPinBlink as  output */
	pinMode(ledPinBlink, OUTPUT);
	/* configure ledPinButton as  output */
	pinMode(ledPinButton, OUTPUT);
	/* configure buttonPin as input */
	pinMode(buttonPin, INPUT);
	/* activate the internal pull up resistor */
	digitalWrite(buttonPin, HIGH);
	/* initialize last time toggelt */
}

void loop() {
	/* compare the time, which has passed since the last toggle
	 * with the interval time. If the interval was reached...
	 */
	if ((millis() - prev) > interval) {
		/* ... reset the time since the last interval to now */
		prev = millis();
		/* invert the actual LED status */
		ledBlinkState = !ledBlinkState;
		/* and write the new status */
		digitalWrite(ledPinBlink, ledBlinkState);
	}

	/* read the button state */
	buttonState = digitalRead(buttonPin);

	/* if the button is pressed ... */
	if (LOW == buttonState) {
		/* ... toggle the LED */
		ledButtonState = !ledButtonState;
		digitalWrite(ledPinButton, ledButtonState);
	}
}

