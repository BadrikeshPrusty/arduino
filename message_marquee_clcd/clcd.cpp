#include "clcd.h"
#include "Arduino.h"

CLCD :: CLCD(BYTE d0, BYTE d1, BYTE d2, BYTE d3, BYTE d4, BYTE d5, BYTE d6, BYTE d7, BYTE rs, BYTE en)
{                                                    //class constructor definition
    clcd_rs_pin = rs;
    clcd_en_pin = en;

    clcd_data_pin[0] = d0;
    clcd_data_pin[1] = d1;              //assigning pin numbers
    clcd_data_pin[2] = d2;
    clcd_data_pin[3] = d3;
    clcd_data_pin[4] = d4;
    clcd_data_pin[5] = d5;
    clcd_data_pin[6] = d6;
    clcd_data_pin[7] = d7;
}

void CLCD :: begin()
{
    pinMode(clcd_rs_pin, OUTPUT);
    pinMode(clcd_en_pin, OUTPUT);
    pinMode(clcd_data_pin[0], OUTPUT);      //defining all the pins connected to LCD as OUTPUT
    pinMode(clcd_data_pin[1], OUTPUT);
    pinMode(clcd_data_pin[2], OUTPUT);
    pinMode(clcd_data_pin[3], OUTPUT);
    pinMode(clcd_data_pin[4], OUTPUT);
    pinMode(clcd_data_pin[5], OUTPUT);
    pinMode(clcd_data_pin[6], OUTPUT);
    pinMode(clcd_data_pin[7], OUTPUT);

    digitalWrite(clcd_en_pin, LOW);          //initializing the LCD

    delay(50);

    write(0x30, 0, 4120);
    write(0x30, 0, 120);                    //initialising function set
    write(0x30, 0, 10);

    write(TWO_LINE_5x8_MATRIX_8_BIT, 0, 37);    //initializing LED to 8 bit mode
    write(CURSOR_HOME, 0, 1520);
    write(DISP_ON_AND_CURSOR_OFF, 0, 37);
    write(CLEAR_DISP_SCREEN, 0, 37);
}

void CLCD :: write(BYTE data, bool rs_bit_val, UINT2 exec_time_us)    //function def to write data to LCD
{   
    digitalWrite(clcd_rs_pin, rs_bit_val);                      //rs 0 for instruction, 1 for data read/write register

    digitalWrite(clcd_data_pin[0], (data >> 0) & 0x01);
    digitalWrite(clcd_data_pin[1], (data >> 1) & 0x01);
    digitalWrite(clcd_data_pin[2], (data >> 2) & 0x01);
    digitalWrite(clcd_data_pin[3], (data >> 3) & 0x01);         //put each bits of data in array
    digitalWrite(clcd_data_pin[4], (data >> 4) & 0x01);
    digitalWrite(clcd_data_pin[5], (data >> 5) & 0x01);
    digitalWrite(clcd_data_pin[6], (data >> 6) & 0x01);
    digitalWrite(clcd_data_pin[7], (data >> 7) & 0x01);
    
    digitalWrite(clcd_en_pin, HIGH);
    delayMicroseconds(1);
    digitalWrite(clcd_en_pin, LOW);

    delayMicroseconds(exec_time_us);
}

void CLCD :: print(const char *s, BYTE addr)                      //for string printing
{
    write(addr, 0, 37);

    while ( *s )
        write(*s++, 1, 37);
}

void CLCD :: putch(char data, BYTE addr)  {                       //for character printing
    write(addr, 0, 37);
    write(data, 1, 37);
}
