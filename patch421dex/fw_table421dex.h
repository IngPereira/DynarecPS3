// DEFINES FOR 4.21 CFW DEX
#define SYSCALL_BASE                0x800000000037A1B0ULL
#define FS_SYSCALL_RMDIR            813 // Just used to check FW ver
#define RMDIR_SYSCALL_ADDR          0x80000000001BC9B8ULL   // where above syscall is in lv2

#define patch_htab1			        0x605BCULL
#define patch_htab2				    0x60FF4ULL
#define patch_htab3			        0x614BCULL
#define HV_HASH_OFFSET              0x370A28

// DEX LV2 START (TESTED ALREADY ON 421 DEX)
#define HTAB_BASE                   0x800000000f000000ULL
#define HTAB_LV2_START              0x08000000ULL // LV2 START OFFSET ON RAM on DEX MACHINE
#define HTAB_LV2_END                0x08800000ULL // LV2 END (Being 0x800000 the size)
