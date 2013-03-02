#include <cell/error.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/paths.h>
#include <sys/timer.h>

#include "patch421dex/patch421dex.h"
#include "patch421/patch421.h"
#include "core.h"

//SYS_PROCESS_PARAM(1001, 0x10000);

int main(void)
{
	int firmware;
	char unitdbg[]={"/dev_hdd0"};
	
	WriteLogInit(0,unitdbg,"APP: Running main base!\n");;
	
	// Here check fw's, so need to add other ones, right now just 4.21 DEX
	if(is_firm_421dex()) {
        firmware = 421646578; // 421dex
    } else if(is_firm_421()) {
        firmware = 421; // 421 CEX
    }
    
    switch(firmware) {
        
        case 421646578: //4.21 dex
            patch_421dex();
            break;
        case 421:
            patch_421();
            break;
        default:
            break;
        }
	
	WriteLogInit(1,NULL,"APP: Finished, OK\n");;
	
    return 0;
	
}
