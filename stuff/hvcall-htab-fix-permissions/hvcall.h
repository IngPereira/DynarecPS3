
/* 3.55 | 3.56 CEX
    #define HTAB_BASE                   0x800000000f000000ULL
    #define HTAB_LV2_START              0x01000000ULL // LV2 START OFFSET on RAM
    #define HTAB_LV2_END                0x01800000ULL // LV2 END
*/

// 4.21 DEX (TESTED)
#define HTAB_BASE                   0x800000000f000000ULL
#define HTAB_LV2_START              0x08000000ULL // LV2 START OFFSET ON RAM
#define HTAB_LV2_END                0x08800000ULL // LV2 END (Being 0x800000 the size)

#define HVSC_SYSCALL		811                  	// which syscall to overwrite with hvsc redirect
#define HVSC_SYSCALL_ADDR	0x80000000001BC490ULL   // 4.21 dex -- replaces sys_fs_mkdir, later we remove it.
#define SC_QUOTE_(x) #x
#define SYSCALL(num) "li %%r11, " SC_QUOTE_(num) "; sc;"

void hvsc_redirect(uint8_t hvcall, uint8_t opt);
int lv1_write_htab_entry(uint64_t vas_id, uint64_t slot, uint64_t va, uint64_t pa);
int patch_htabfix(void);
