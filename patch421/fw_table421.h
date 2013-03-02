// DEFINES FOR 4.21 CFW
#define SYSCALL_BASE                0x800000000035BCA8ULL
#define FS_SYSCALL_RMDIR            813 // Just used to check FW ver
#define RMDIR_SYSCALL_ADDR          0x80000000001B65C8ULL   // where above syscall is in lv2

#define patch_htab1			        0x5CCA4ULL
#define patch_htab2				    0x5D6DCULL
#define patch_htab3			        0x5DBA4ULL
#define HV_HASH_OFFSET              0x370A28

// CEX address.
#define HTAB_BASE                   0x800000000f000000ULL
#define HTAB_LV2_START              0x01000000ULL // LV2 START OFFSET on RAM
#define HTAB_LV2_END                0x01800000ULL // LV2 END
