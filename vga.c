#include "vga.h"
#include "util.h"

unsigned char port_byte_read(unsigned short port)
{
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_write(unsigned short port, unsigned char data)
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
    port_byte_write(VGA_DATA_REG, position >> 8);
}

void write_char_at(char c, int offset)
{
    unsigned char *vid_mem = (unsigned char*) VIDEO_ADDR;
    vid_mem[offset] = c;
    vid_mem[offset + 1] = WHITE_ON_BLACK;
}

static int row_from_position(int position)
{
    // 2*MAX_COLS because offset is a video memory position 
    // and we want a text grid position
    return (position / (2* MAX_COLS));
}

static int get_position(int row, int col)
{
    return 2 * ( row*MAX_COLS + col );
}

static int newline_to_position(int curr_position)
{
    return get_position(row_from_position(curr_position) + 1, 0);
}

int scroll_in(int curr_position)
{
    memcpy(
            (char*) VIDEO_ADDR + get_position(1,0),
            (char*) VIDEO_ADDR + get_position(0,0),
            2 * (MAX_ROWS-1) * MAX_COLS
    );

    for(int c = 0; c < MAX_COLS; c++)
        write_char_at(' ', get_position(MAX_ROWS-1, c)); 

    return curr_position - (2*MAX_COLS);

}

void print_backspace() {
        int new_cursor = get_cursor() - 2;
        write_char_at(' ', new_cursor);
        set_cursor(new_cursor);
}

void print_string(char *string)
{
    int offset = get_cursor();
    int i = 0;
    while(string[i] != 0)
    {
        if(offset >= (MAX_COLS * MAX_ROWS * 2))
        {
            offset = scroll_in(offset);
        }
        if(offset % (2*MAX_COLS) == 0)
            offset += 2;

        if(string[i] == '\n')
        {
            offset = newline_to_position(offset);
        }else{
            write_char_at(string[i], offset);
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
}



