


#include "vga.h"
#include "keyboard.h"
#include "isr.h"


void main()
{
    isr_install();
    asm volatile("sti");
    init_keyboard();
}
