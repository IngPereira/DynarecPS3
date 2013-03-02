
#define PEEKLV1 8
#define POKELV1 9

#define CELL_FS_SEEK_SET SEEK_SET
#define CELL_FS_SEEK_CUR SEEK_CUR
#define CELL_FS_SEEK_END SEEK_END

#define REBOOT 0x200
#define SHUTDOWN 0x100

#define S_IFMT 00170000
#define CELL_FS_O_RDONLY 0
#define CELL_OK 0
#define CELL_FS_O_RDWR   2
#define CELL_FS_O_WRONLY    1
#define CELL_FS_O_ACCMODE   3
#define CELL_FS_O_CREAT     100
#define CELL_FS_O_EXCL      200
#define CELL_FS_O_TRUNC     1000
#define CELL_FS_O_APPEND    2000
#define CELL_FS_O_MSELF     10000
#define CELL_FS_DEFAULT_CREATE_MODE_6 0x186

#define FILE_SYSTEM_OPEN  801
#define FILE_SYSTEM_READ  802
#define FILE_SYSTEM_WRITE 803
#define FILE_SYSTEM_CLOSE 804
#define FILE_SYSTEM_OPENDIR 805
#define FILE_SYSTEM_READDIR 806
#define FILE_SYSTEM_CLOSEDIR 807
#define FILE_SYSTEM_STAT 808
#define FILE_SYSTEM_MKDIR 811
#define FILE_SYSTEM_FSTAT 809
#define FILE_SYSTEM_UNLINK 814
#define FILE_SYSTEM_LSEEK 818
#define FILE_SYSTEM_FSYNC 820
#define FILE_SYSTEM_MOUNT 837
#define FILE_SYSTEM_UNMOUNT 838
#define FILE_SYSTEM_CHMOD 834

#define ERROR_KERNEL_509 0x80010509
#define ERROR_KERNEL_CANT_ALLOC_MEMORY 0x80010004
#define ERROR_KERNEL_INVALID_ARGUMENT 0x80010002
#define ERROR_KERNEL_IOERROR 0x8001002B
#define ERROR_KERNEL_NO_RESOURCE 0x80010005
#define ERROR_KERNEL_INVALID_MEMORY 0x8001000D
#define ID_NOR 0x100000200000004

int RebootShutdownMachine(int command);
int lv2FsChMode(char* path, int mode);
int lv2FsOpen(const char* path, uint64_t flags, int* fd, uint64_t special, const void* arg, uint64_t size);
int lv2FsRead(int fd, char* buffer, uint64_t size, uint64_t* bytes);
int lv2FsWrite(int fd, void* buffer, uint64_t size, uint64_t* bytes);
int lv2FsClose(int fd);
int lv2FsOpenDir(const char* path, int* fd);
int lv2FsCloseDir(int fd);
int lv2FsUnLink(const char* path);
int lv2FsLseek(int fd, int64_t offset, int whence, uint64_t *pos);
int lv2FsFSync(int fd);
void WriteLogInit(uint32_t close, const char* unit, const char *fmt, ...);
int lv2_sm_ring_buzzer(uint64_t unknown1, uint8_t unknown2, uint32_t unknown3);
uint64_t lv1Peek(uint64_t addr);
void lv1Poke(uint64_t addr, uint64_t opcode);
uint64_t lv2peek(uint64_t addr);
void lv2poke(uint64_t addr, uint64_t val);
void pokeq32(uint64_t addr, uint32_t val);
void _poke(uint64_t addr, uint64_t val);
void _poke32(uint64_t addr, uint32_t val);
void lv2memcpy( uint64_t to, const uint64_t from, size_t sz);
void lv2memset( uint64_t dst, const uint64_t val, size_t sz);
void lv1_poke_8(uint64_t addr, uint8_t val);
void lv1_memcpy_to(uint64_t addr, const void *data, unsigned int size);
