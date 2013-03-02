#include <stdio.h>
#include <inttypes.h>
#include <sys/timer.h>

#include "hvcall.h"
#include "core.h"

void hvsc_redirect(uint8_t hvcall, uint8_t opt)
{
    int x;
    
    uint64_t original_syscall_code_1 = lv2peek(HVSC_SYSCALL_ADDR);
	uint64_t original_syscall_code_2 = lv2peek(HVSC_SYSCALL_ADDR + 8);
	uint64_t original_syscall_code_3 = lv2peek(HVSC_SYSCALL_ADDR + 16);
	uint64_t original_syscall_code_4 = lv2peek(HVSC_SYSCALL_ADDR + 24);
    
    // Install redirect
    if(opt == 0)
	{
        for (x=0;x<25;x++)
        {
            lv2poke(HVSC_SYSCALL_ADDR, 0x7C0802A6F8010010ULL);
            lv2poke(HVSC_SYSCALL_ADDR + 8, 0x3960000044000022ULL | (uint64_t)hvcall << 32);
            lv2poke(HVSC_SYSCALL_ADDR + 16, 0xE80100107C0803A6ULL);
            lv2poke(HVSC_SYSCALL_ADDR + 24, 0x4e80002060000000ULL);
            __asm__("sync");
        }
    }
    if(opt == 1) // Remove redirections
    {
        for (x=0;x<25;x++)
        {
            lv2poke(HVSC_SYSCALL_ADDR, original_syscall_code_1);
            lv2poke(HVSC_SYSCALL_ADDR + 8, original_syscall_code_2);
            lv2poke(HVSC_SYSCALL_ADDR + 16, original_syscall_code_3);
            lv2poke(HVSC_SYSCALL_ADDR + 24, original_syscall_code_4);
            __asm__("sync");
        }
    }
    
}

int lv1_write_htab_entry(uint64_t vas_id, uint64_t slot, uint64_t va, uint64_t pa)
{    
    hvsc_redirect(1,1);	// redirect to hvcall 1
        
    // call lv1_write_htab_entry
	uint64_t ret = 0;
	
	__asm__ __volatile__("mr %%r3, %1;" "mr %%r4, %2;" "mr %%r5, %3;"
			     "mr %%r6, %4;"
			     SYSCALL(HVSC_SYSCALL) "mr %0, %%r3;":"=r"(ret)
			     :"r"(vas_id), "r"(slot), "r"(va),
			     "r"(pa)
			     :"r0", "r2", "r3", "r4", "r5", "r6", "r7", "r8",
			     "r9", "r10", "r11", "r12", "lr", "ctr", "xer",
			     "cr0", "cr1", "cr5", "cr6", "cr7", "memory");

	hvsc_redirect(1, 0); // Now remove hvsc redirections
	
	WriteLogInit(0,NULL,"APP: call lv1_write_htab_entry OK!\n");;
    
    // Just one return r3
    return (int)ret;
}

int patch_htabfix()
{
	int i, res;
	uint64_t pte0, pte1;
	
	// process entire lv2
	for (i = 0; i < 128; i++)
	{
		// read the old value 
		pte0 = lv2peek(HTAB_BASE | (i << 7));
		pte1 = lv2peek(HTAB_BASE | (i << 7) + 8);
		
		WriteLogInit(0,NULL,"APP: %d loop\n",i);;
		
		WriteLogInit(0,NULL,"APP: pte0: 0x%016llx\n", pte0);;
		
		WriteLogInit(0,NULL,"APP: pte1: 0x%016llx\n", pte1);;
		
		//verify entry is lv2
		if ((pte1 >= HTAB_LV2_START) && (pte1 < HTAB_LV2_END))
		{
			// patch proper htab settings
			res = lv1_write_htab_entry( 0, i << 3, pte0, (pte1 & 0xff0000) | 0x190 );
		}
	}
	
	WriteLogInit(0,NULL,"APP: Htab parcheado OK!\n");;
	
	return res;

}
