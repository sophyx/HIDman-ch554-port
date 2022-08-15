
#ifndef __PS2_H__
#define __PS2_H__
#include <stdbool.h>
#define PORT_KEY 0
#define PORT_MOUSE 1

#define CLOCK 0
#define DATA 1

const extern uint8_t KEYA_MAKE[];
const extern uint8_t KEYA_BREAK[];
const extern uint8_t KEYB_MAKE[];
const extern uint8_t KEYB_BREAK[];
const extern uint8_t KEYC_MAKE[];
const extern uint8_t KEYC_BREAK[];


typedef struct ps2port
{
	uint8_t state;
	uint8_t port;
	uint8_t data;
	uint8_t sendbit;
	uint8_t recvbit;
	uint8_t parity;

	// byte number within current chunk
	uint8_t bytenum;

	// ring buffer (pointers to chunks)
	uint8_t sendBuffStart;
	uint8_t sendBuffEnd;
	uint8_t *sendBuff[64];
	uint8_t recvBuff;
	uint8_t prevhid[8];
} ps2port;

extern __xdata ps2port keyboard;

void SendHIDPS2(unsigned short length, unsigned char type, unsigned char __xdata *msgbuffer);

void OutPort(unsigned char port, unsigned char channel, bool val);

bool GetPort(unsigned char port, unsigned char channel);

void SendPS2(ps2port *port, const uint8_t *chunk);

/*States

IDLE - CLOCK/DATA high

SEND_CLOCK_LOW - Check for host transmission - if not, Write next value to data, drive clock line low, set state to SEND_CLOCK_HIGH
SEND_CLOCK_HIGH - Make clock high, perhaps calculate next value

*/

#define S_INIT 0
#define S_IDLE 1
#define S_SEND_CLOCK_LOW 2
#define S_SEND_CLOCK_HIGH 3
#define S_RECEIVE_CLOCK_LOW 4
#define S_RECEIVE_CLOCK_HIGH 5
#define S_RECEIVE_ACK 6
#define S_INHIBIT 10
#define S_WAIT 11

void PS2ProcessPort(ps2port *port);
#endif