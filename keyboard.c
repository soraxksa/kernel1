#include "keyboard.h"


#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256] = {0};

#define SC_MAX 57

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};


bool can_backspace(char *buffer)
{
    uint32_t len = strlen(buffer);
    if(len > 0)
    {
        buffer[len-1] = 0x00;
        return true;
    }
    return false;
}


static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_read(0x60);

    if (scancode > SC_MAX) return;

    if (scancode == BACKSPACE)
    {
        if (can_backspace(key_buffer))
        {
            print_backspace();
        }
    }else if (scancode == ENTER)
    {
        print_string("\n");
        execute_command(key_buffer);
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int) scancode];
        uint32_t len = strlen(key_buffer);
        if(len >= 256)
            return;
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        print_string(str);
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}

