#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/timer.h>

#include "patch421dex.h"
#include "../core.h"
#include "hvcall421dex.h"
#include "fw_table421dex.h"
#include "../htab_payload.h"

int is_firm_421dex(void)
{
    uint64_t addr = lv2peek((SYSCALL_BASE + FS_SYSCALL_RMDIR * 8));
    // check address first
    if(addr < 0x8000000000000000ULL || addr > 0x80000000007FFFFFULL || (addr & 3)!=0)
        return 0;
    addr = lv2peek(addr);

    if(addr == RMDIR_SYSCALL_ADDR) return 1;

    return 0;
}

void patch_htab421dex()
{
    int i,x;
	
	WriteLogInit(0,NULL,"APP: Installing new htab patch...");;
	
	//HTAB _CUSTOM call function, we patch it 25 times because there can be a fail patching in some times
	for (x=0;x<25;x++)
	{
        for (i=0; i< 19;i++)
        {
            lv2poke(0x8000000000700000ULL + (i * 0x8), htab_payload[i]);
        }
        __asm__("sync");
        
        // Htab patch desc
        _poke(0x700098ULL, 0x8000000000700048ULL); // htab _Custom call desc 
        
    }
    
    // Patching it 25 times because fail patching problem
    for (x=0;x<25;x++)
	{
    // @jump hooks: Replace hvsc calls by these jumps to the new functions 0x6FFFE0
    _poke32(patch_htab1, (0x48000001 | (uint32_t)(0x700000 - patch_htab1))); // BL to 0x700000 _CUSTOM CALL TO HTAB
    _poke32(patch_htab2, (0x48000001 | (uint32_t)(0x700000 - patch_htab2))); // BL to 0x700000 _CUSTOM CALL TO HTAB
    _poke32(patch_htab3, (0x48000001 | (uint32_t)(0x700000 - patch_htab3))); // BL to 0x700000 _CUSTOM CALL TO HTAB 
	
    }
    
    WriteLogInit(0,NULL,"done\n");;
    
    
}

int patch_htabfix421dex()
{
	int i, res;
	uint64_t pte0, pte1;
	
	// process entire lv2
	for (i = 0; i < 128; i++)
	{
		// read the old value 
		pte0 = lv2peek(HTAB_BASE | (i << 7));
		pte1 = lv2peek(HTAB_BASE | (i << 7) + 8);
		
		//verify entry is lv2
		if ((pte1 >= HTAB_LV2_START) && (pte1 < HTAB_LV2_END))
		{
			// patch proper htab settings
			res = lv1_write_htab_entry421dex( 0, i << 3, pte0, (pte1 & 0xff0000) | 0x190 );
		}
	}
	
	WriteLogInit(0,NULL,"APP: LV2 HTAB r|w|x parcheado OK!\n");;
	
	return res;

}

void patch_421dex()
{
    int ret;
    
    WriteLogInit(0,NULL,"APP: Patching Lv2 hash on lv1...");;
    // Patch LV2 LV1 HASH
    lv1Poke(HV_HASH_OFFSET, 1);
	lv1Poke(HV_HASH_OFFSET + 8, 0xE0D251B556C59F05ULL);
	lv1Poke(HV_HASH_OFFSET + 16, 0xC232FCAD552C80D7ULL);
	lv1Poke(HV_HASH_OFFSET + 24, 0x65140CD200000000ULL);
	WriteLogInit(0,NULL,"done\n");;	
	
	WriteLogInit(0,NULL,"APP: Patching lv2 htab r|w|x access...\n");;
    ret = patch_htabfix421dex(); // Patch htab rights access
    WriteLogInit(0,NULL,"APP: done with %d ret\n", ret);;
    
    sys_timer_usleep(10000);
    
    patch_htab421dex();
    
    lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6); // BEEP
    
        
}
