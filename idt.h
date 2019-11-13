#include <stddef.h>
#include <stdint.h>

#if !defined idt_h
#define idt_h


struct IDT_entr
{
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};
 
struct IDT_entry IDT[256];
void idt_init(void);
#endif