 global loader
 global inb
 global outb
 global blankirq
 global irq1_asm
 global load_gdt
 global load_idt

    MAGIC_NUMBER equ 0x1BADB002   
    FLAGS        equ 0x0            
    CHECKSUM     equ -MAGIC_NUMBER  
                                    

    section .text:                 
    align 4                        
        dd MAGIC_NUMBER             
        dd FLAGS                    
        dd CHECKSUM

	extern v0_emptyirq_vo
		blankirq:
			pusha
			call v0_emptyirq_vo
			popa
			iret

	extern v0_irq1_vo
		irq1_asm:
			pusha
			call v0_irq1_vo
			popa
			iret

	load_gdt:
	   mov eax, [esp+4]
	   lgdt [eax]

	   mov ax, 0x10
	   mov ds, ax
	   mov es, ax
	   mov fs, ax
	   mov gs, ax
	   mov ss, ax
	   jmp 0x08:.flush
	.flush:
	   ret

	load_idt:
		mov edx, [esp + 4]
		lidt [edx]
		sti
		ret

	inb:
		mov dx, [esp + 4]
		in al, dx
		ret

	outb:
		mov dx, [esp + 4]
        mov al, [esp + 8]
        out dx, al
        ret          

    loader:
	extern main                   
        mov esp, kernel_stack + STACK_SIZE
	call main
    .loop:
	hlt
        jmp .loop  

    global GDT_Loc

    STACK_SIZE equ 4096

    section .bss
    align 4
    kernel_stack:
        resb STACK_SIZE
