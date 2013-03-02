/*   SCE CONFIDENTIAL                                       */
/*   PlayStation(R)3 Programmer Tool Runtime Library 370.001                                              */
/*   Copyright (C) 2007 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>
#include <sys/timer.h>

//SYS_PROCESS_PARAM(1001, 0x10000);

#include "core.h"

#define HV_HASH_OFFSET              0x370A28

int main(void)
{
    int result;
	char unitdbg[]={"/dev_hdd0"};
	
    WriteLogInit(0,unitdbg,"APP: Running main base!\n");;
	
	// Patch LV2 LV1 HASH
    lv1Poke(HV_HASH_OFFSET, 1);
	lv1Poke(HV_HASH_OFFSET + 8, 0xE0D251B556C59F05ULL);
	lv1Poke(HV_HASH_OFFSET + 16, 0xC232FCAD552C80D7ULL);
	lv1Poke(HV_HASH_OFFSET + 24, 0x65140CD200000000ULL);
    
    result = patch_htabfix();
    
    WriteLogInit(1,NULL,"APP: hv_call Result: %d!\n", result);;
    
    lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);
    
    return 0;
}
