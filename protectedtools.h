// protectedtools.h: Close interrupts, simple protected mode setup, etc.
// Part of the LibLLPC (Low Level Programming in C) library.

void close_interrupts() {
	asm (
	CLI
	);
}

void system_halt() {
	asm (
	HLT
	);
}

void hang() {
	asm (
	1:	HLT
		JMP 1b
	);
}
