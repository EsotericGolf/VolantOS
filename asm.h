#include "heap.h"

#ifndef VO_ASM
#define VO_ASM

unsigned char inb(unsigned char port);
void outb(unsigned char port, unsigned char data);
void load_idt(unsigned long* ptrdescriptor);
void blankirq();
void irq1_asm();

typedef struct {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char flags;
	unsigned char base_high; 
} IGDT_Entry __attribute__((packed));

typedef struct {
	unsigned short limit;
	unsigned int address;
} __attribute__((packed)) IGDT_Desc;

void load_gdt(IGDT_Desc* descriptor);

IGDT_Entry gdt[3];

void AddGDTEntry(int i, void* ptr) {
	IGDT_Entry ent = *((IGDT_Entry*) ptr);

	gdt[i] = ent;
}

void RefreshGDT() {
	IGDT_Desc desc;

	desc.limit = (sizeof(IGDT_Entry) * 3) - 1;
	desc.address = (unsigned int) &gdt;

	load_gdt(&desc);
}
#endif
