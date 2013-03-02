#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>

#include "core.h"

#define HTAB_BASE 0x800000000f000000ULL // works as is on 3.55m, 3.56 but something is wrong in 4.21

int main(void)
{
    int fd;    
    
    lv2FsOpen("/dev_hdd0/PS3_HTAB.bin", CELL_FS_O_RDWR | CELL_FS_O_CREAT | LV2_O_APPEND, &fd, 0x186, 0, 0);
    
	uint64_t result_lv2;
	char* tmp = (char*)malloc(0x80000);
	
	if(tmp && fd != -1)
	{
		uint64_t i;
		for(i = 0; i < 0x80000; i+=8)
		{
			result_lv2 = lv2peek(HTAB_BASE + i);
			memcpy(tmp + i, &result_lv2, 8);
		}	
		
		lv2FsWrite(fd, tmp, 0x80000, NULL);
		lv2FsClose(fd);
		fd = -1;

		free(tmp);
	}
	
	return 0;
}
