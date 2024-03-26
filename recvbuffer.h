#ifndef _RECVBUFFER_H_
#define _RECVBUFFER_H_

//buffer struct
typedef struct _BUFFER_STRUCT
{
	UINT8 *pBufferIn;
	UINT8 *pBufferOut;
	UINT8 *pBufferStart;
	UINT8 *pBufferEnd;

	UINT8 BlockSize;
} BUFFER_STRUCT;

//receive struct
typedef struct _RECV_STRUCT
{
	BUFFER_STRUCT  RecvBuffer;
	UINT8          RPtr;
	UINT8          TimerCounter;
} RECV_STRUCT;

#define BUFFER_BLOCK_SIZE   4
#define BUFFER_BLOCK_COUNT  4

typedef enum _RECV_STATE
{
	RECV_STATE_IDLE = 0,
	RECV_STATE_PACKET
} RECV_STATE;

//max interval
#define BYTE_INTERVAL    3

extern void InitRecvBuffer(void);

extern BOOL IsRecvBufferEmpty(void);

extern UINT8 *GetOutputBuffer(void);

extern void RecvBufferOneByte(UINT8 ch);

extern void RecvBufferTimerout(void);

#endif

