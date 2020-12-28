/*
 * Author Name    : Badrikesh Prusty 
 * Organization   : Emertxe Information Technologies (P) Ltd. 
 * Date           : 18/08/2020
 * Description    : Write an Arduino program to implement Message Marquee that prints "Hello World" across the CLCD
 * Input          : No user input required
 * Output         :
 *                  "Hello World" scrolling across the display(marquee)
 */
 
#include "main.h"
#include "clcd.h"

CLCD clcd(D0, D1, D2, D3, D4, D5, D6, D7, RS, EN);    //creating class object and passing all the PIN numbers LCD is connected to

void setup() {                                        //code in the setup function run only once
    clcd.begin();                                     //initial all the clcd connected pins as output and initialise the CLCD for use
    clcd.print("MESSAGE  MARQUEE", LINE_1(0));        //print the first line of the CLCD
}

void loop() {                                                 //code in the loop function runs infinite number of times
    static char str[] = "Hello World";                        //message to be scrolled across the LCD
    static char i, str_length = strlen(str), j = -str_length; //initial i(for offset to print)

    clcd.print(str, LINE_2(i));                               //print the message string as per the offset i that increments every loop

    if ( (LINE_2(i) + str_length) > LINE_2_SIZE_OVERFLOW )    //if str reaches greater than LINE2 end go to this block
        clcd.print(str, LINE_2(j++));                         //print the string again such that the str char that goes out of the lcd
                                                              //reaches offset 0 of line LINE2(starting address) and shifts as per the cycle
    delay(250);                                               //shift every 250 ms
    clcd.putch(' ', LINE_2(i));                               //remove the starting character as it shifts, using this because it doesn't clear
                                                                                                                               //entire display
    if ( j == 0 ) {
        j = -str_length;                                  //if incremented j becomes 0 revert it back to negative string length
        i = 0;                                            //offset to 0
    }

    else
        i++;
}
