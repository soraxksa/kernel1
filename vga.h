#ifndef VGA_H_
#define VGA_H_


#define VGA_CTRL_REG 0x3D4
#define VGA_DATA_REG 0x3D5
#define VGA_LOW 0x0F
#define VGA_HIGH 0x0E


#define VIDEO_ADDR 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

unsigned char port_byte_read(unsigned short port);
void port_byte_write(unsigned short port, unsigned char data);

int get_cursor();
void set_cursor(int position);
void print_string(char *string);

void print_backspace();




#endif
