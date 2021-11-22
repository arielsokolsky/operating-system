extern gp
global _gdt_flush     ; Allows the C code to link to this
           ; Says that 'gp' is in another file
_gdt_flush:
    lgdt [gp]        ; Load the GDT with our '_gp' which is a special pointer 

	mov	ax, 0x10	; 0x10 is the offset in the GDT to our data segment
	mov	ds, ax		; Load all data segment selectors
	mov	es, ax
	mov	fs, ax
	mov	gs, ax
	mov	ss, ax
	jmp	0x08:.flush	; 0x08 is the offset to our code segment: Far jump!
    
.flush:
	ret