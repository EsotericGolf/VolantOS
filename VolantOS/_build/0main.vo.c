#include "internal/default.h"
#include "1heap.vo.h"
;
typedef struct {
	u16 p_offset_lower;
	u16 p_selector;
	u8 p_zero;
	u8 p_type_attr;
	u16 p_offset_higher;
} v0_IDT_Entry __attribute__((packed));
v0_IDT_Entry d0_IDT_Entry = (v0_IDT_Entry){};


typedef struct {
	u16 p_limit_low;
	u16 p_base_low;
	u8 p_base_middle;
	u8 p_access;
	u8 p_flags;
	u8 p_base_high;
} v0_GDT_Entry __attribute__((packed));
v0_GDT_Entry d0_GDT_Entry = (v0_GDT_Entry){};


;
u8 (*v0_framebuffer) = (u8*)(0x000B8000);
i32 v0_WriteAt(u8 v0_c, i32 v0_i){
	v0_framebuffer[2*v0_i] = v0_c;
	v0_framebuffer[(2*v0_i)+1] = 0x15;
}
void v0_Clear(void){
	{
		i32 v0_i = 0;
		while(v0_i<=(80*25)){
			v0_WriteAt(32, v0_i);
			v0_i++;
		}
	}
}




v0_IDT_Entry v0_IDT[256];
v0_GDT_Entry* v0_MakeSegmentEntry(u32 v0_base, u32 v0_limit, u8 v0_access){
	v0_GDT_Entry (*v0_ent) = (v0_GDT_Entry*)(v1_malloc(8));
	v0_ent->p_base_low = v0_base&0xFFFF;
	v0_ent->p_base_middle = (v0_base>>16)&0xFF;
	v0_ent->p_base_high = (v0_base>>24)&0xFF;
	v0_ent->p_limit_low = v0_limit&0xFFFF;
	v0_ent->p_flags = (v0_limit>>16)&0x0F;
	v0_ent->p_flags = (v0_ent->p_flags)|0xC0;
	v0_ent->p_access = v0_access;
	return v0_ent;
}
void v0_irq1_vo(void){
	v0_Clear();
	inb(0x60);
	outb(0x20, 0x20);
}
void v0_emptyirq_vo(void){
	outb(0x20, 0x20);
}
v0_IDT_Entry v0_MakeInterruptEntry(u32 v0_addr){
	v0_IDT_Entry v0_ent = (v0_IDT_Entry){.p_offset_lower = d0_IDT_Entry.p_offset_lower, .p_selector = d0_IDT_Entry.p_selector, .p_zero = d0_IDT_Entry.p_zero, .p_type_attr = d0_IDT_Entry.p_type_attr, .p_offset_higher = d0_IDT_Entry.p_offset_higher, };
	v0_ent.p_offset_lower = v0_addr&0xFFFF;
	v0_ent.p_selector = 0x08;
	v0_ent.p_zero = 0;
	v0_ent.p_type_attr = 0x8e;
	v0_ent.p_offset_higher = (v0_addr&0xFFFF0000)>>16;
	return v0_ent;
}
i32 v0_main(void){
	u8 (*v0_str);
	v0_str[0] = 72;
	v0_str[1] = 101;
	v0_str[2] = 108;
	v0_str[3] = 108;
	v0_str[4] = 111;
	v0_str[5] = 32;
	v0_str[6] = 87;
	v0_str[7] = 111;
	v0_str[8] = 114;
	v0_str[9] = 108;
	v0_str[10] = 100;
	v0_str[11] = 33;
	{
		i32 v0_i = 0;
		while(v0_i<12){
			v0_WriteAt(v0_str[v0_i], v0_i);
			v0_i++;
		}
	}
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 40);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
	v0_IDT[32] = v0_MakeInterruptEntry((u32)(blankirq));
	v0_IDT[33] = v0_MakeInterruptEntry((u32)(irq1_asm));
	u64 v0_idtptr[2];
	v0_idtptr[0] = (64*256)+((((u32)(v0_IDT))&0xffff)<<16);
	v0_idtptr[1] = ((u32)(v0_IDT))>>16;
	AddGDTEntry(1, v0_MakeSegmentEntry(0, 0xFFFFFFFF, 0x9A));
	AddGDTEntry(2, v0_MakeSegmentEntry(0, 0xFFFFFFFF, 0x92));
	RefreshGDT();
	load_idt(v0_idtptr);
	return 0;
}

int main() {
	return v0_main();
}
