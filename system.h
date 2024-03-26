
#ifndef	__DEBUG_H__
#define __DEBUG_H__

#ifdef	FREQ_SYS
#if		FREQ_SYS == 3000000
#define FSYS_CFG 2
#endif
#if		FREQ_SYS == 6000000
#define	FSYS_CFG 3
#endif
#if		FREQ_SYS == 12000000
#define	FSYS_CFG 4
#endif
#if		FREQ_SYS == 16000000
#define	FSYS_CFG 5
#endif
#if		FREQ_SYS == 24000000
#define	FSYS_CFG 6
#endif
#endif

//���庯������ֵ
#ifndef  SUCCESS
#define  SUCCESS  1
#endif
#ifndef  FAIL
#define  FAIL    0
#endif

//���嶨ʱ����ʼ
#ifndef  START
#define  START  1
#endif
#ifndef  STOP
#define  STOP    0
#endif

//#define	 FREQ_SYS	48000000ul	  //ϵͳ��Ƶ48MHz

#ifndef  BUAD_RATE
#ifdef DEBUG
#define  BUAD_RATE  115200ul
#else
#define  BUAD_RATE  115200ul
#endif
#endif

void CfgFsys(void);                        //CH559ʱ��ѡ�������
void mDelayuS(UINT16 n);              // ��uSΪ��λ��ʱ
void mDelaymS(UINT16 n);              // ��mSΪ��λ��ʱ

#endif

