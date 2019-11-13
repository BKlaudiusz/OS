#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "terminal.h"

struct GDT GDT_struct[4];
struct gdt_entry_t GDT_descryptor[4];

void GDT_init(void)
{
    GDT_struct[0] = (struct GDT) {.base=0, .limit=0, .type=0};                      // Selector 0x00 cannot be used
    GDT_struct[1] = (struct GDT){.base=0x04000000, .limit=0x03ffffff, .type=0x9A}; // Selector 0x08 will be our code
    GDT_struct[2] = (struct GDT){.base=0x08000000, .limit=0x03ffffff, .type=0x92}; // Selector 0x10 will be our data
    GDT_struct[3] = (struct GDT){.base=0, .limit=0, .type=0x89};  
    for (size_t i = 0; i < 4; i++)
    {
        encodeGdtEntry(GDT_descryptor + i ,GDT_struct[i]);
    }
    reload_segments();
    set_GDT((uint32_t)GDT_descryptor, sizeof(GDT_descryptor));
    terminal_writestring("GDT!\n");
}
    



void encodeGdtEntry(struct gdt_entry_t * targetstr, struct GDT source)
{
    uint8_t * target = (uint8_t *)(targetstr);
    // Check the limit to make sure that it can be encoded
    if ((source.limit > 65536) && ((source.limit & 0xFFF) != 0xFFF)) {
    }
    if (source.limit > 65536) {
        // Adjust granularity if required
        source.limit = source.limit >> 12;
        target[6] = 0xC0;
    } else {
        target[6] = 0x40;
    }
 
    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] |= (source.limit >> 16) & 0xF;
 
    // Encode the base 
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;
 
    // And... Type
    target[5] = source.type;
}