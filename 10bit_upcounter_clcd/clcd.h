#ifndef CLCD_H
#define CLCD_H

#define TWO_LINE_5x8_MATRIX_8_BIT   0x38          //instruction for the performing following operations
#define DISP_ON_AND_CURSOR_OFF      0x0C
#define CLEAR_DISP_SCREEN           0x01
#define CURSOR_HOME                 0x02

#define LINE_1(x)                   (0x80 + x)    //1st and 2nd line starting address 
#define LINE_2(x)                   (0xC0 + x)

typedef unsigned char BYTE;           //defining type definition for the following data types
typedef unsigned short UINT2;

class CLCD                            //class definition
{
    BYTE clcd_rs_pin;                 //private data members and member function
    BYTE clcd_en_pin;
    BYTE clcd_data_pin[8];
    void write(BYTE addr, bool rs_bit_val, UINT2 exec_time_us);
    
    public:                           //public member functions prototypes
        CLCD(BYTE d0, BYTE d1, BYTE d2, BYTE d3, BYTE d4, BYTE d5, BYTE d6, BYTE d7, BYTE rs, BYTE en);
                                                                        //constructor prototype
        void begin();                 //begin function to initialize the LCD and PINS of uC
        void print(const char *s, BYTE addr);     //print the character to LCD
};

#endif
