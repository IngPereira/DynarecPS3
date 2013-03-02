#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>

#include "core.h"

int log = -1;

int RebootShutdownMachine(int command) 
{
     system_call_3(379, command, 0, 0); 
     return_to_user_prog(uint64_t); 
}

int lv2FsChMode(char* path, int mode)
{
	system_call_2(FILE_SYSTEM_CHMOD, (uint64_t)path, (uint64_t)mode);
	return_to_user_prog(uint64_t);
}

int lv2FsOpen(const char* path, uint64_t flags, int* fd, uint64_t special, const void* arg, uint64_t size)
{
	system_call_6(FILE_SYSTEM_OPEN, (uint64_t)path, flags, (uint64_t)fd, special, (uint64_t)arg, size);
	return_to_user_prog(uint64_t);
}

int lv2FsRead(int fd, char* buffer, uint64_t size, uint64_t* bytes)
{
	uint64_t temp_bytes;
	
	system_call_4(FILE_SYSTEM_READ, (uint64_t)fd, (uint64_t)buffer, size, !bytes ? (uint64_t)&temp_bytes : (uint64_t)bytes);
	return_to_user_prog(uint64_t);
}

int lv2FsWrite(int fd, void* buffer, uint64_t size, uint64_t* bytes)
{
	uint64_t temp_bytes;
	
	system_call_4(FILE_SYSTEM_WRITE, (uint64_t)fd, (uint64_t)buffer, size, !bytes ? (uint64_t)&temp_bytes : (uint64_t)bytes);
	return_to_user_prog(uint64_t);
}

int lv2FsClose(int fd)
{
	system_call_1(FILE_SYSTEM_CLOSE, (uint64_t)fd);
	return_to_user_prog(uint64_t);
}

int lv2FsOpenDir(const char* path, int* fd)
{
	int result = ERROR_KERNEL_INVALID_MEMORY;
	if(path && fd)
	{
		system_call_2(FILE_SYSTEM_OPENDIR, (uint64_t)path, (uint64_t)fd);
		return_to_user_prog(uint64_t);
	}

	return result;
}

int lv2FsCloseDir(int fd)
{
	system_call_1(FILE_SYSTEM_CLOSEDIR, (uint64_t)fd);
	return_to_user_prog(uint64_t);
}

int lv2FsUnLink(const char* path)
{
	system_call_1(FILE_SYSTEM_UNLINK, (uint64_t)path);
	return_to_user_prog(uint64_t);
}

int lv2FsLseek(int fd, int64_t offset, int whence, uint64_t *pos)
{
	if(pos)
	{
		system_call_4(FILE_SYSTEM_LSEEK, (uint64_t)fd, (uint64_t)offset, (uint64_t)whence, (uint64_t)pos);
		return_to_user_prog(uint64_t);
	}
	
	return ERROR_KERNEL_INVALID_MEMORY;
}

int lv2FsFSync(int fd)
{
	system_call_1(FILE_SYSTEM_FSYNC, (uint64_t)fd);
	return_to_user_prog(uint64_t);
}

void WriteLogInit(uint32_t close, const char* unit, const char *fmt, ...)
{
	int err;
	va_list list;
	char msg[256];

	if(log == -1 && unit)
	{
		sprintf(msg, "%s/APP.log", unit);
		lv2FsUnLink(msg);
		err = lv2FsOpen(msg,CELL_FS_O_RDWR | CELL_FS_O_CREAT | CELL_FS_O_APPEND, &log, CELL_FS_DEFAULT_CREATE_MODE_6, 0, 0);
		lv2FsChMode(msg, S_IFMT | 0777);
		if(err != CELL_OK)
		{
			log = -1;
			return;
		}
	}

	va_start(list, fmt);
	vsprintf(msg, fmt, list);
	va_end(list);

	if(log != -1)
	{
		lv2FsWrite(log, msg, strlen(msg), NULL);
		lv2FsFSync(log);
		if(close)
		{
			lv2FsClose(log);
			log = -1;
		}
	}
}

int lv2_sm_ring_buzzer(uint64_t unknown1, uint8_t unknown2, uint32_t unknown3)
{
	system_call_3(392, unknown1, unknown2, unknown3);
	return_to_user_prog(uint64_t);
}

uint64_t lv1Peek(uint64_t addr)
{
	system_call_1(PEEKLV1, addr);
	return_to_user_prog(uint64_t);
}

void lv1Poke(uint64_t addr, uint64_t opcode)
{
	system_call_2(POKELV1, addr, opcode);
}

uint64_t lv2peek(uint64_t addr)
{
	system_call_1(6, addr);
	return_to_user_prog(uint64_t);
}

void lv2poke(uint64_t addr, uint64_t val)
{
	system_call_2(7, addr, val);
}

void pokeq32(uint64_t addr, uint32_t val)
{
    uint32_t next = lv2peek(addr) & 0xffffffff;
    lv2poke(addr, (uint64_t) val << 32 | next);
}

void _poke(uint64_t addr, uint64_t val)
{
    lv2poke(0x8000000000000000ULL + addr, val);
}

void _poke32(uint64_t addr, uint32_t val)
{
    pokeq32(0x8000000000000000ULL + addr, val);
}

void lv2memcpy( uint64_t to, const uint64_t from, size_t sz)
{
    system_call_3(15, to, from, sz);
}

void lv2memset( uint64_t dst, const uint64_t val, size_t sz)
{
    system_call_3(16, dst, val, sz);
}
