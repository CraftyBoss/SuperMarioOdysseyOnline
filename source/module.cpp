#define MODULE_NAME "Starlight"
#define MODULE_NAME_LEN 9

// rtld working object
__attribute__((section(".bss"))) char __nx_module_runtime[0xD0];

struct ModuleName {
    int unknown;
    int name_lengh;
    char name[MODULE_NAME_LEN + 1];
};

__attribute__((section(".rodata.module_name")))
ModuleName module_name = {.unknown = 0, .name_lengh = MODULE_NAME_LEN, .name = MODULE_NAME};
