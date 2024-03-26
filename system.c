#include "system.h"
#include "type.h"
#include "ch554.h"


void CfgFsys()	
{
	SAFE_MOD = 0x55;
	SAFE_MOD = 0xAA;

	CLOCK_CFG &= ~MASK_SYS_CK_SEL;
	CLOCK_CFG |= FSYS_CFG;
	
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

