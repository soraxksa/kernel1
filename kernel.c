


#include "vga.h"
#include "keyboard.h"
#include "isr.h"


void main()
{
    for(int i = 0; i < 200; i++)
        print_string("HELLO KERNEL ");
    isr_install();
    asm volatile("sti");
    init_keyboard();
}
