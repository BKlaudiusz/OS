#if !defined gdt_h
#define gdt_h

#include <stddef.h>
#include <stdint.h>
struct GDT
{
    uint32_t base;
    uint32_t limit;
    uint16_t type;
};
struct gdt_entry_t
{	//Bity w strukturze
    uint16_t limit_low; 	//0:15
    uint16_t base_low; 		//16:31
    uint8_t base_middle; 	//32:39
    uint8_t access;			//40:47
    uint8_t limit_high : 4; //48:51
    uint8_t flags : 4; 		//52:55
    uint8_t base_high; 		//56:63
};

void GDT_init(void);
extern void set_GDT(uint32_t a, uint16_t b);
extern void reload_segments(void);
void encodeGdtEntry(struct gdt_entry_t *targetstr, struct GDT source);
void GDT_create(void);
#endif 

