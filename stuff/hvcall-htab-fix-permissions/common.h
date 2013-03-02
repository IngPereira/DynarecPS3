
#define HVSC_SYSCALL			811                  	// which syscall to overwrite with hvsc redirect
#define HVSC_SYSCALL_ADDR		0x80000000001BC490ULL   // 4.21 dex

#define SYSCALL_TABLE       0x800000000037A1B0ULL    //4.21 dex
#define SYSCALL_PTR(n)		(SYSCALL_TABLE + 8 * (n))
