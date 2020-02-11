// multiboottools.h: Tools to comply with the Multiboot Standard. Includes header() and more.
void header() {
	asm (
	.SET ALIGN, 1<<0
	.SET MEMINFO, 1<<1
	.SET FLAGS, ALIGN | MEMINFO
	.SET MAGIC, 0x1BADB002
	.SET CHECKSUM, -(MAGIC + FLAGS)
	
	/* Constants are set, multiboot header in place here */
	
	.SECTION .MULTIBOOT
	.ALIGN 4
	.LONG MAGIC
	.LONG FLAGS
	.LONG CHECKSUM

	);
}

void setstack-base() { // Run before setstack-8/16/32/64kib
	asm (
	.SECTION .BSS
	.ALIGN 16
	);
}

void setstack-8() { // 8 kibibyte
	asm (
	STACK_BOTTOM:
	.SKIP 8192
	STACK_TOP:
	
	);
}

void setstack-16() { // 16 kibibyte
	asm (
	STACK_BOTTOM:
	.SKIP 16384
	STACK_TOP:
	
	);
}

void setstack-32() { // 32 kibibyte
	asm (
	STACK_BOTTOM:
	.SKIP 32678
	STACK_TOP:
	
	);
}

void setstack-64() { // 64 kibibyte
	asm (
	STACK_BOTTOM:
	.SKIP 65536
	STACK_TOP:
	
	);
}

void generate-linker() { // Generates a .ln file for all sections
	system("touch linker-${date '+%Y-%m-%d'}.ld");
	system("linker=linker-${date '+%Y-%m-%d'}.ld");
	system("echo 'ENTRY(_bootbegin)
	SECTIONS {
		. = 1M;
		.text BLOCK(4K) : ALIGN(4K)
		{
			*(.multiboot)
			*(.text)
		}
		.rodata BLOCK(4K) : ALIGN(4K)
		{
			*(.rodata)
		}
		.data BLOCK(4K) : ALIGN(4K)
		{
			*(.data)
		}
		.bss BLOCK(4K) : ALIGN(4K)
		{
			*(COMMON)
			*(.bss)
		}
	}' >> $linker"); // Create a linker file. May not be compatible with gdttools.h.
}

void beginbootroutine() { // Only works if your start is "_bootbegin" as in the linker.
	asm (
	.SECTION .TEXT
	.GLOBAL _bootbegin
	.TYPE _bootbegin, @FUNCTION
	_bootbegin:
		
	);		
}

void initstack() { // Finalize stack setup. Make sure you have already defined your stack size.
	asm (
		MOV $STACK_TOP, %ESP
		
	);
}

// Place initstack() directly after beginbootroutine().

void linkerend() { // Helps linker.
	asm (
	.SIZE _bootbegin, . - _bootbegin
	);
}
