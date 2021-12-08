#include "vga.h"

static unsigned char port_byte_read(unsigned short port)
{
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

static void port_byte_write(unsigned short port, unsigned char data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}


int get_cursor()
{
    int position = 0;
    port_byte_write(VGA_CTRL_REG, VGA_LOW);
    position = port_byte_read(VGA_DATA_REG);
    port_byte_write(VGA_CTRL_REG, VGA_HIGH);
    position |= port_byte_read(VGA_DATA_REG) << 8;
    return position * 2;
}

void set_cursor(int position)
{
    position /= 2;
    port_byte_write(VGA_CTRL_REG, VGA_LOW);
    port_byte_write(VGA_DATA_REG, position & 0xFF);
    port_byte_write(VGA_CTRL_REG, VGA_HIGH);
    port_byte_write(VGA_CTRL_REG, position >> 8);
}

void write_char_at(char c, int offset)
{
    unsigned char *vid_mem = (unsigned char*) VIDEO_ADDR;
    vid_mem[offset] = c;
    vid_mem[offset + 1] = WHITE_ON_BLACK;
}


void print_string(char *string)
{
    int offset = get_cursor();
    int i = 0;
    while(string[i] != 0x00)
    {
        write_char_at(string[i], offset);
        i++;
        offset += 2;
    }
    set_cursor(offset);
}



