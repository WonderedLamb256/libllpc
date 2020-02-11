// gdttools.h: Work with the Global Descriptor Table (GDT) Includes "loadgdt" (needs nasm>gas conversion) and "gdtparams".
// Part of the LibLLPC (Low Level Programming in C) library.
#include "hexdefs.h"

void loadgdt() {
	// Please set a GDT manually in assembly with the pointer called gdtp before you use the loadgdt() function. Name your code header CODE
	// and your (continued) boot routine BOOT.
	asm (
	LGDT [GDTP]
	MOV EAX, CR0
	OR EAX,0x1
	MOV CR0, EAX
	JMP CODE:BOOT
	)
void gdtparams(int basecode, int limitcode, int basedata, int limitdata) { // Credits to osdev.org.
	GDT[0] = {.base=0, .limit=0, .type=0}; // Unusable.
	GDT[1] = {.base=basecode, .limit=limitcode, .type=0x9A}; // Code.
	GDT[2] = {.base=basedata, .limit=limitdata, .type=0x92}; // Data.
	// P.S. Follow the OSDev tutorial to program a GDT following these guidelines.
}
