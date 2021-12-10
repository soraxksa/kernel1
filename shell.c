#include "shell.h"
#include "vga.h"
#include "string.h"




void execute_command(const char *cmd)
{
    if(strcmp(cmd, "EXIT") == 0)
    {
        print_string("stopping the cpu, bye :D\n");
        asm volatile("hlt");
    }

    print_string("Unknown command: ");
    print_string(cmd);
    print_string("\n>>>");
}
