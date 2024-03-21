#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "ch554.h"
#include "usbhost.h"
#include "ps2protocol.h"
#include "ps2.h"
#include "parsedescriptor.h"
#include "pwm.h"

// Default pinouts (HIDman-AXD, HIDman-mini)
SBIT(KEY_CLOCK, 0x90, 5);
SBIT(KEY_DATA, 0x90, 3);

__xdata uint8_t repeatDiv = 0;
uint16_t ResetCounter;

// green LED on by default
uint8_t LEDStatus = 0x02;

void mTimer2Interrupt(void) __interrupt(5);

// timer should run at 48MHz divided by (0xFFFF - (TH0TL0))
// i.e. 60khz
void mTimer0Interrupt(void) __interrupt(1)
{
	// Reload to 60KHz
	PS2ProcessPort(PORT_KEY);

	// now handle keyboard typematic repeat timers
	// divide down to 15KHz to make maths easier
	if (++repeatDiv == 4)
	{
		RepeatTimer();
		repeatDiv = 0;

		// turn current LED on if we've seen no activity in a while
		if (LEDDelay)
			LEDDelay--;
		else {
			if (LEDStatus & 0x01)
				SetPWM1Dat(0x18);
			if (LEDStatus & 0x02)
				SetPWM2Dat(0x30);
			if (LEDStatus & 0x04) {
				T3_FIFO_L = 0xFF; // blue needs to be brighter
				T3_FIFO_H = 0;
			}
		}
	}
}

uint8_t DetectCountdown = 0;
uint8_t PrevRTSState = 0;
uint8_t PrevButtons = 0;

void main()
{

	InitSystem();

	SetPWMClk(12); //Set the clock division factor of PWM1&2 to 12
	InitPWM1(1);   //PWM1 initialization, active low
	InitPWM2(1);   //PWM2 initialization, active high
	InitPWM3(1);
	SetPWMCycle(0xff);
	SetPWM1Dat(0x00);
	SetPWM2Dat(0x00);

	T3_CK_SE_L = 0x20;
	T3_CK_SE_H = 0;
	T3_END_H = 0;
	T3_END_L = 255;
	T3_FIFO_L = 0;
	T3_FIFO_H = 0;

	//port1 setup
	P1_MOD_OC = 0b11101010; // set output mode for output pins to open-drain
	P1_DIR_PU = 0x00;  // no pull-ups and the other pins input
	P1 = 0b11111010;	 // default pin states

	// timer0 setup
	TMOD = (TMOD & 0xf0) | 0x02; // mode 1 (8bit auto reload)
	TH0 = 0xBD;					 // 60khz

	TR0 = 1; // start timer0
	ET0 = 1; //enable timer0 interrupt;
	EA = 1;	 // enable all interrupts

	memset(SendBuffer, 0, 255);
	//SendKeyboardString("We are go\n");

	while (1) {
		ProcessUsbHostPort();
		ProcessKeyboardLed();
		HandleRepeats();
	}
}
