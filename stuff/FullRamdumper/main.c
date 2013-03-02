#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>

#include "core.h"

int main(void)
{
    uint64_t Valor;
	uint64_t x=0,i=0;
	char *buffer;
	
	unsigned char buffer_dump[0x200];
	int fd1;
	
	lv2FsOpen("/dev_hdd0/PS3_RAM.bin", CELL_FS_O_RDWR | CELL_FS_O_CREAT, &fd1, CELL_FS_DEFAULT_CREATE_MODE_6, 0, 0);
	
	for (i=0;i< (256 * 1024 * 1024);i+= 0x200)
	{
		for (x=0; x < 0x200; x+=0x8)
		{
			Valor= lv1Peek(x+i);
			memcpy(buffer_dump+x, &Valor, 8);
		}
		lv2FsWrite(fd1, buffer_dump, 0x200, 0);
	}
	
	lv2FsClose(fd1);
	
	return 0;
}
