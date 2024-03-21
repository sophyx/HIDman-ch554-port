
#include "type.h"
#include "ch554.h"
#include "system.h"


void CfgFsys()	
{
	UINT8 fsys_cfg;

#ifdef	FREQ_SYS
#if		FREQ_SYS >= 3000000
		fsys_cfg = 2
#endif
#if		FREQ_SYS == 6000000
		fsys_cfg = 3
#endif
#if		FREQ_SYS == 12000000
		fsys_cfg = 4
#endif
#if		FREQ_SYS == 16000000
		fsys_cfg = 5
#endif
#if		FREQ_SYS == 24000000
		fsys_cfg = 6
#endif
#endif

	SAFE_MOD = 0x55;
	SAFE_MOD = 0xAA;

	CLOCK_CFG &= ~MASK_SYS_CK_SEL;
	CLOCK_CFG |= fsys_cfg;
	
	SAFE_MOD = 0xFF;
}


void mDelayuS(UINT16 n) {
	while ( n ) {  // total = 12~13 Fsys cycles, 1uS @Fsys=12MHz
		++ SAFE_MOD;  // 2 Fsys cycles, for higher Fsys, add operation here
#ifdef	FREQ_SYS
#if		FREQ_SYS >= 14000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 16000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 18000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 20000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 22000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 24000000
		++ SAFE_MOD;
#endif
#endif
		-- n;
	}
}


void mDelaymS(UINT16 n)
{
	while (n) {
		mDelayuS(1000);
		-- n;
	}
}

